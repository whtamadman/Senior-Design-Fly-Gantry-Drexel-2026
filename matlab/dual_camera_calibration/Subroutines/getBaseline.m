function [framesBS,maxFrameMeanBS,opts] = getBaseline(background,frame,cameraNum,opts)

framesBS = abs(double(frame{cameraNum})-double(background{cameraNum}));
meanFrameBS = mean(framesBS,3);
frameMeanBS = framesBS-meanFrameBS;
maxFrameMeanBS = squeeze(max(frameMeanBS,[],[1,2]));
opts.cutoff_base(cameraNum) = quantile(ceil(maxFrameMeanBS),0.25);
framesBS = uint8(framesBS);
end



