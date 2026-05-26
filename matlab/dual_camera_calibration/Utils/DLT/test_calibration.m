function [calibrationError, calibModelError] = test_calibration(frame, camPts, numTrials)

nCamera = round(size(camPts,2)./2);
numPoints = zeros(1,nCamera);
frame_good = cell(1,nCamera);
camPts_good = cell(1,nCamera);

calibrationError = zeros(numTrials, nCamera);
calibModelError = zeros(numTrials, nCamera);

for n = 1:nCamera
    frame_good{n} = frame;
    camPts_good{n} = camPts(:,(n-1)*2+1:n*2);
    frame_good{n}(isnan(camPts_good{n}(:,1)),:) = [];
    camPts_good{n}(isnan(camPts_good{n}(:,1)),:) = [];
    numPoints(n) = size(camPts_good{n},1);
end
numSamples = max(11, floor(numPoints/2)); % Using half gives a good estimate for the error

for trial = 1:numTrials
    for n = 1:nCamera
        k_train = randsample(numPoints(n), numSamples(n));
        k_test = setdiff(1:numPoints(n),k_train);

        [sampleC,modelRMSE] = dlt_computeCoefficients(frame_good{n}(k_train,:),camPts_good{n}(k_train,:));

        knownFrame = frame(k_test,:);
        knownCamPts = camPts_good{n}(k_test,:);

        predictedCamPts = dlt_inverse(sampleC, knownFrame);
        numKnown = length(k_test);
        calibrationError(trial,n) = sum(sqrt(mean((predictedCamPts - knownCamPts).^2, 2))) / numKnown;% uv error
        calibModelError(trial,n) = modelRMSE;% uv error
    end
end

end