%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% dlt_computeCoefficients
function  [c, rmse, X, camPts, Muv] = dlt_computeCoefficients(frame, camPts)

% function  [c,rmse] = dlt_computeCoefficients(frame,camPts)
%
% A basic implementation of 11 parameter DLT
%
% Inputs:
%  frame - an array of x,y,z calibration point coordinates
%  camPts - an array of u,v pixel coordinates from the camera
%
% Outputs:
%  c - the 11 DLT coefficients
%  rmse - root mean square error for the reconstruction; units = pixels
%
% Notes - frame and camPts must have the same number of rows.  A minimum of
% 6 rows are required to compute the coefficients.  The frame points must
% not all lie within a single plane
%
% Ty Hedrick

% check for any NaN rows (missing data) in the frame or camPts
ndx = find(sum(isnan([frame, camPts]), 2) > 0);

% remove any missing data rows
frame(ndx, :) = [];
camPts(ndx, :) = [];

%% Edits: Incorporate R, W, etc into the matrix X
numPoints = size(frame, 1); % The number of calibration points aka control points
R = ones(numPoints * 2, 1); % Initially R(i) = 1 but will be updated after the first iteration
W = eye(numPoints * 2); % Initially the weight matrix is the identity matrix
counter = 1;

while true % while the iteration has not converged
    %% Before the second and subsequent iterations, update R and W
    %if counter > 1
    %    R = sum(frame(:, 1:3) .* [c(9) c(10) c(11)], 2) + 1; % See Eq. 4 http://www.kwon3d.com/theory/dlt/lsq.html
        %principalPoint;
        %weights;
        %W = eye(numPoints * 2) .* repelem([weights], 2);
    %end
    %% Resume the function
    % re-arrange the frame matrix and the camPts array to facilitate the linear least squares solution
    X = zeros(numPoints * 2, 11);
    Y = zeros(numPoints * 2, 1);
    for i = 1:numPoints
        X(2 * i - 1, 1:3) = frame(i, 1:3) / R(i);
        X(2 * i, 5:7) = frame(i, 1:3) / R(i);
        X(2 * i - 1, 4) = 1 / R(i);
        X(2 * i, 8) = 1 / R(i);
        X(2 * i - 1, 9:11) = frame(i, 1:3) .* -camPts(i, 1) / R(i);
        X(2 * i, 9:11) = frame(i, 1:3) .* -camPts(i, 2) / R(i);
        
        Y(2 * i - 1) = camPts(i, 1) / R(i);
        Y(2 * i) =  camPts(i, 2) / R(i);
    end

    % re-arrange the camPts array for the linear solution
    % Y = reshape(flipud(rot90(camPts)), numel(camPts), 1);

    % get the linear solution to the 11 parameters using the weights matrix
    c = linsolve(W * X, W * Y);

    % compute the position of the frame in u,v coordinates given the linear solution from the previous line
    Muv = dlt_inverse(c, frame);

    % Compute the root mean square error in pixels between the model's estimated frame u,v and the measured frame u,v
    % See Eq. 35 at http://www.kwon3d.com/theory/dlt/dlt.html#error 
    rmse = sum(sqrt(sum((Muv - camPts).^2, 2))) / numPoints;
    
    % Display feedback on the iteration
    % fprintf('Iteration %d, rmse %.1f pixels\n', counter, rmse);
    
    %% Break the loop when the DLT parameters have sufficiently converged
    % Check for convergence by comparing the last iteration's DLT coefficents
    if counter > 1000 || counter > 1 && sum(abs((c - savedC) ./ savedC)) < 1e-9
        break
    end
    
    % Update the counter and save the convergence parameter
    savedC = c; 
    counter = counter + 1;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% dlt_reconstruct
function [xyz,rmse] = dlt_reconstruct(camPts,c)

% function [xyz,rmse] = dlt_reconstruct(c,camPts)
%
% This function reconstructs the 3D position of a coordinate based on a set
% of DLT coefficients and [u,v] pixel coordinates from 2 or more cameras
%
% Inputs:
%  c - 11 DLT coefficients for all n cameras, [11,n] array
%  camPts - [u,v] pixel coordinates from all n cameras over f frames,
%   [f,2*n] array
%
% Outputs:
%  xyz - the xyz location in each frame, an [f,3] array
%  rmse - the root mean square error for each xyz point, and [f,1] array,
%   units are [u,v] i.e. camera coordinates or pixels
%
% Ty Hedrick

% number of frames
nFrames=size(camPts,1);

% number of cameras
nCams=size(camPts,2)/2;

% setup output variables
xyz(1:nFrames,1:3)=NaN;
rmse(1:nFrames,1)=NaN;

% process each frame
for i=1:nFrames
    
    % get a list of cameras with non-NaN [u,v]
    cdx=find(isnan(camPts(i,1:2:nCams*2))==false);
    
    % if we have 2+ cameras, begin reconstructing
    if numel(cdx)>=2
        
        % initialize least-square solution matrices
        m1=[];
        m2=[];
        
        m1(1:2:numel(cdx)*2,1)=camPts(i,cdx*2-1).*c(9,cdx)-c(1,cdx);
        m1(1:2:numel(cdx)*2,2)=camPts(i,cdx*2-1).*c(10,cdx)-c(2,cdx);
        m1(1:2:numel(cdx)*2,3)=camPts(i,cdx*2-1).*c(11,cdx)-c(3,cdx);
        m1(2:2:numel(cdx)*2,1)=camPts(i,cdx*2).*c(9,cdx)-c(5,cdx);
        m1(2:2:numel(cdx)*2,2)=camPts(i,cdx*2).*c(10,cdx)-c(6,cdx);
        m1(2:2:numel(cdx)*2,3)=camPts(i,cdx*2).*c(11,cdx)-c(7,cdx);
        
        m2(1:2:numel(cdx)*2,1)=c(4,cdx)-camPts(i,cdx*2-1);
        m2(2:2:numel(cdx)*2,1)=c(8,cdx)-camPts(i,cdx*2);
        
        % get the least squares solution to the reconstruction
        xyz(i,1:3)=linsolve(m1,m2);
        
        % compute ideal [u,v] for each camera
        uv=m1*xyz(i,1:3)';
        
        % compute the number of degrees of freedom in the reconstruction
        dof=numel(m2)-3;
        
        % estimate the root mean square reconstruction error
        rmse(i,1)=(sum((m2-uv).^2)/dof)^0.5;
    end
end

