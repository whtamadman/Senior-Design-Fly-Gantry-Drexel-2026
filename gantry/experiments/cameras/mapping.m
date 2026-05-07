%% Projector-Camera Calibration
% Loads captured frames, parses projector (DMD) and camera coordinates
% directly from filenames, estimates background, binarizes each frame,
% and assembles matched coordinate pairs for transform fitting.
%
% Filename format: mapping_bottom_Cx%d_Cy%d&Px%d_Py%d[_anything].png
%   Cx, Cy : camera grid coordinates (pixels, 0-indexed)
%   Px, Py : DMD pixel coordinates   (pixels, 0-indexed)
%
% Projector DMD resolution : 912 x 1140
% Camera resolution        : 800 x 600

clear; clc; close all;

%% --- Parameters -----------------------------------------------------------

IMAGE_DIR          = 'frames';        % folder containing captured frames

% DMD resolution (from C++ constants)
DMD_WIDTH          = 912;
DMD_HEIGHT         = 1140;

% Camera resolution
CAM_WIDTH          = 800;
CAM_HEIGHT         = 600;

% Binarization threshold — fraction of peak intensity after background sub.
% Raise if noise blobs appear; lower if the dot is being missed.
BINARIZE_THRESHOLD = 0.15;

% Minimum blob area in camera pixels — filters out noise specks
MIN_BLOB_AREA      = 3;

% If true, show each frame with the estimated centroid and allow manual edits.
% Controls per-frame prompt:
%   [Enter] accept estimate, c click a corrected center, s skip frame
INTERACTIVE_CENTER_REVIEW = true;

%% --- Step 1: Scan and parse filenames ------------------------------------

fprintf('Scanning for frames in: %s\n', IMAGE_DIR);

all_files = dir(fullfile(IMAGE_DIR, 'mapping_bottom_Cx*_Cy*&Px*_Py*.png'));
num_files  = numel(all_files);
fprintf('Found %d frame(s).\n', num_files);

if num_files == 0
    error('No matching frames found in "%s". Check IMAGE_DIR and filename format.', IMAGE_DIR);
end

% Parse coordinates from every filename up front
cam_x_all  = zeros(num_files, 1);
cam_y_all  = zeros(num_files, 1);
dmd_x_all  = zeros(num_files, 1);
dmd_y_all  = zeros(num_files, 1);

for k = 1:num_files
    tokens = regexp(all_files(k).name, ...
        '^mapping_bottom_Cx(\d+)_Cy(\d+)&Px(\d+)_Py(\d+)(?:_.*)?\.png$', ...
        'tokens', 'once');

    if isempty(tokens)
        error('Filename did not match expected format:\n  %s', all_files(k).name);
    end

    cam_x_all(k) = str2double(tokens{1});
    cam_y_all(k) = str2double(tokens{2});
    dmd_x_all(k) = str2double(tokens{3});
    dmd_y_all(k) = str2double(tokens{4});
end

fprintf('Coordinate parsing complete.\n');

%% --- Step 2: Estimate background via median stack ------------------------
% Sample up to 100 frames randomly. The dot is at a different position in
% every frame, so the pixel-wise median converges to the static background.

MAX_BG_FRAMES = min(num_files, 100);
bg_indices    = randperm(num_files, MAX_BG_FRAMES);

fprintf('Estimating background from %d randomly sampled frames...\n', MAX_BG_FRAMES);

% Get image dimensions from first sample
sample = imread(fullfile(IMAGE_DIR, all_files(bg_indices(1)).name));
if size(sample, 3) == 3
    sample = rgb2gray(sample);
end
[img_h, img_w] = size(sample);

% Build median stack
bg_stack = zeros(img_h, img_w, MAX_BG_FRAMES, 'double');
for k = 1:MAX_BG_FRAMES
    img = imread(fullfile(IMAGE_DIR, all_files(bg_indices(k)).name));
    if size(img, 3) == 3
        img = rgb2gray(img);
    end
    bg_stack(:, :, k) = double(img);
end

background = median(bg_stack, 3);
fprintf('Background estimation complete.\n');

%% --- Step 3: Binarize each frame and validate blob location --------------
% Since coordinates are already known from the filename, binarization here
% serves two purposes:
%   1. Confirm the dot is actually visible at the expected camera location
%   2. Refine the camera coordinate to the true blob centroid if desired

fprintf('Processing %d frames...\n', num_files);
if INTERACTIVE_CENTER_REVIEW
    fprintf('Interactive center review enabled.\n');
    fprintf('For each frame: [Enter]=accept, c=click correction, s=skip frame.\n');
end

% Preallocate output arrays
%   camera_coords    : [N x 2]  (Cx, Cy) parsed from filename
%   dmd_coords       : [N x 2]  (Px, Py) parsed from filename
%   centroid_coords  : [N x 2]  (x, y) detected blob centroid in camera image
%   detection_flag   : [N x 1]  1 = blob found, 0 = blob missing
camera_coords   = [cam_x_all, cam_y_all];
dmd_coords      = [dmd_x_all, dmd_y_all];
centroid_coords = nan(num_files, 2);
detection_flag  = zeros(num_files, 1);

for k = 1:num_files

    img = imread(fullfile(IMAGE_DIR, all_files(k).name));
    if size(img, 3) == 3
        img = rgb2gray(img);
    end
    img_d = double(img);

    % Background subtraction + clamp
    img_sub  = max(img_d - background, 0);

    % Normalize and threshold
    img_norm = img_sub / (max(img_sub(:)) + eps);
    img_bin  = img_norm > BINARIZE_THRESHOLD;

    % Remove noise specks
    img_bin  = bwareaopen(img_bin, MIN_BLOB_AREA);

    % Find blobs
    stats = regionprops(img_bin, 'Centroid', 'Area');

    if isempty(stats)
        % Dot not detected — dim frame or threshold too high.
        % Optional manual fallback: click center or skip.
        if INTERACTIVE_CENTER_REVIEW
            figure('Name', 'Center Review', 'NumberTitle', 'off');
            imshow(img, []); hold on;
            title(sprintf('Frame %d/%d: no blob found. c=click center, s=skip', k, num_files));
            drawnow;

            resp = lower(strtrim(input('No blob found. [c=click center, s=skip] (default s): ', 's')));
            if strcmp(resp, 'c')
                [x_new, y_new, btn] = ginput(1);
                if ~isempty(btn)
                    centroid_coords(k, :) = [x_new, y_new];
                    detection_flag(k)     = 1;
                end
            end

            close(gcf);
        end
        continue;
    end

    % Use the largest blob
    [~, largest_idx]       = max([stats.Area]);
    centroid_coords(k, :)  = stats(largest_idx).Centroid;
    detection_flag(k)      = 1;

    if INTERACTIVE_CENTER_REVIEW
        figure('Name', 'Center Review', 'NumberTitle', 'off');
        imshow(img, []); hold on;
        plot(centroid_coords(k,1), centroid_coords(k,2), 'r+', 'MarkerSize', 12, 'LineWidth', 2);
        title(sprintf('Frame %d/%d: red + is estimated center', k, num_files));
        drawnow;

        resp = lower(strtrim(input('Center review [Enter=accept, c=click new center, s=skip]: ', 's')));

        if strcmp(resp, 'c')
            [x_new, y_new, btn] = ginput(1);
            if ~isempty(btn)
                centroid_coords(k, :) = [x_new, y_new];
            end
        elseif strcmp(resp, 's')
            centroid_coords(k, :) = [nan, nan];
            detection_flag(k)     = 0;
        end

        close(gcf);
    end

end

num_detected = sum(detection_flag);
fprintf('Detection complete.\n');
fprintf('  Blobs detected  : %d / %d\n', num_detected, num_files);
fprintf('  Missed          : %d\n', num_files - num_detected);

% Filter to only successfully detected frames for downstream use
valid             = detection_flag == 1;
camera_coords_v   = camera_coords(valid, :);
dmd_coords_v      = dmd_coords(valid, :);
centroid_coords_v = centroid_coords(valid, :);

%% --- Step 4: Compute centroid vs filename coordinate error ---------------
% The filename already contains the intended camera coordinate (Cx, Cy).
% Comparing it to the detected centroid gives a per-point reprojection error
% that tells you how accurately the camera coordinate in the filename
% reflects the true dot position in the image.

delta     = centroid_coords_v - camera_coords_v;
errors    = sqrt(sum(delta .^ 2, 2));   % Euclidean distance in camera pixels

fprintf('\nCentroid vs filename camera coordinate error:\n');
fprintf('  Mean  : %.2f px\n', mean(errors));
fprintf('  Median: %.2f px\n', median(errors));
fprintf('  Max   : %.2f px\n', max(errors));

%% --- Step 5: Sanity-check plots ------------------------------------------

figure('Name', 'DMD Coordinates (from filenames)');
scatter(dmd_coords_v(:,1), dmd_coords_v(:,2), 4, 'b', 'filled');
xlabel('DMD X (px)');
ylabel('DMD Y (px)');
title('DMD pixel positions from filenames');
xlim([0 DMD_WIDTH]);
ylim([0 DMD_HEIGHT]);
set(gca, 'YDir', 'reverse');
axis equal tight; grid on;

figure('Name', 'Camera Coordinates — Filename vs Detected Centroid');
subplot(1,2,1);
scatter(camera_coords_v(:,1), camera_coords_v(:,2), 4, 'b', 'filled');
title('From filename (Cx, Cy)');
xlabel('Camera X (px)'); ylabel('Camera Y (px)');
xlim([0 CAM_WIDTH]); ylim([0 CAM_HEIGHT]);
set(gca, 'YDir', 'reverse'); axis equal tight; grid on;

subplot(1,2,2);
scatter(centroid_coords_v(:,1), centroid_coords_v(:,2), 4, 'r', 'filled');
title('Detected blob centroid');
xlabel('Camera X (px)'); ylabel('Camera Y (px)');
xlim([0 CAM_WIDTH]); ylim([0 CAM_HEIGHT]);
set(gca, 'YDir', 'reverse'); axis equal tight; grid on;

figure('Name', 'Per-point Centroid Error (px)');
scatter(camera_coords_v(:,1), camera_coords_v(:,2), 20, errors, 'filled');
colormap(hot); colorbar;
xlabel('Camera X (px)'); ylabel('Camera Y (px)');
title('Euclidean error: detected centroid vs filename camera coord (px)');
set(gca, 'YDir', 'reverse');
xlim([0 CAM_WIDTH]); ylim([0 CAM_HEIGHT]);
axis equal tight; grid on;

%% --- Step 6: Save results ------------------------------------------------

save('calibration_points.mat', ...
    'camera_coords_v', ...    % [N x 2] Cx, Cy from filename
    'dmd_coords_v', ...       % [N x 2] Px, Py from filename
    'centroid_coords_v', ...  % [N x 2] detected blob centroids
    'errors');                % [N x 1] per-point centroid error

fprintf('\nSaved to calibration_points.mat\n');
fprintf('Variables exported:\n');
fprintf('  camera_coords_v   : filename camera coordinates  [N x 2]\n');
fprintf('  dmd_coords_v      : DMD pixel coordinates        [N x 2]\n');
fprintf('  centroid_coords_v : detected blob centroids      [N x 2]\n');
fprintf('  errors            : centroid vs filename error   [N x 1]\n');
fprintf('\nNext step: run projector_camera_mapping.m to fit the coordinate transform.\n');