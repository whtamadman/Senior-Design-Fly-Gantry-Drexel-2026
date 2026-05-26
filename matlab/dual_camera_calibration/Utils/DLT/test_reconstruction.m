function [calibModelError, reconModelError] = test_reconstruction(frame, camPts, numTrials)

nCamera = round(size(camPts,2)./2);
reconModelError = zeros(numTrials, 1);
calibModelError = zeros(numTrials, 1);

camPts_good = camPts(sum(~isnan(camPts),2)>2,:);
frame_good = frame(sum(~isnan(camPts),2)>2,:);
numPoints = size(camPts_good,1);
numSamples = max(11, floor(numPoints/2)); % Using half gives a good estimate for the error

for trial = 1:numTrials
    k_train = randsample(numPoints, numSamples);
    k_test = setdiff(1:numPoints,k_train);

    for n = 1:nCamera
        [sampleC(:,n),~] = dlt_computeCoefficients(frame_good(k_train,:),camPts_good(k_train,(n-1)*2+1:n*2));
    end

        knownFrame = frame(k_test,:);
        knownCamPts = camPts_good(k_test,:);

        [predictedFrame, reconModelRmse] = dlt_reconstruct(sampleC, knownCamPts);
        reconModelRmse = mean(reconModelRmse);

        numReconstructedPts = size(predictedFrame, 1);
        calibModelError(trial) = sum(sqrt(mean((predictedFrame - knownFrame).^2, 2))) / numReconstructedPts;% xyz error
        reconModelError(trial) = reconModelRmse;% uv error
end

end

