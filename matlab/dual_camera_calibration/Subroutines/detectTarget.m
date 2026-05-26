function [targetCentroid,targetLabel] = detectTarget(framesBS,maxFrameMeanBS,cameraNum,opts)

cutoff = opts.cutoff_base(cameraNum)+opts.buffer;
if maxFrameMeanBS>=cutoff
    bufferThresh = (opts.targetPixels)./size(framesBS,1)./size(framesBS,2);
    se = strel('disk', 3, 6); % Structuring element for dilation
    ROI = true(size(framesBS,1),size(framesBS,2));

    tmp = framesBS-cutoff;
    buffer = max(quantile(tmp(:),1-bufferThresh),0);

    BW = imbinarize(framesBS, cutoff+buffer);

    BW = imfill(imdilate(BW,se),'holes');
    BW(~ROI)= false;

    stats = regionprops(BW,'Centroid','Circularity','Area');
    
    [~,targetNdx(1)] = min(abs([stats.Circularity]-1));
    [~,targetNdx(2)] = max([stats.Area]);
    [~,targetNdx(3)] = min(0.05.*abs([stats.Circularity]-1)+max(1./[stats.Area],0));

    targetCentroid = reshape([stats(targetNdx).Centroid],2,[])';
else
    targetCentroid = nan(3,2);
end
targetLabel = {'area','circularity','both'};

end