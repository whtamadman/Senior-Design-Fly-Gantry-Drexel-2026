function plotCalibrationImage(ax,plotType,cameraNum,currView,currFrame,opts,varargin)
% plotting
switch plotType
    case 'Raw'
        frame = evalin('base','frame');
        I = frame{cameraNum}(:,:,currFrame);
    case 'Baseline Sub'
        framesBS = evalin('base','framesBS');
        I = framesBS{cameraNum}(:,:,currFrame);
    case 'Binarized'
        framesBS = evalin('base','framesBS');
        framesBS = framesBS{cameraNum}(:,:,currFrame);

        % get the cutoff threshold
        cutoff = opts.cutoff_base(cameraNum)+opts.buffer;
        tmp = (framesBS-cutoff);
        bufferThresh = (opts.targetPixels)./size(framesBS,1)./size(framesBS,2);
        buffer = max(quantile(tmp(:),1-bufferThresh),0);
        I = imbinarize(framesBS, cutoff+buffer);
end
switch opts.imageEnhance
    case 'Brighten'
        I = imlocalbrighten(I);
    case 'histeq'
        I = histeq(I);
    case 'adapthisteq'
        I = adapthisteq(I);
end

imagesc(I, 'Parent', ax);
colormap(ax,gray(256))
ax.XLim = [0 size(I,2)];
ax.YLim = [0 size(I,1)];
axis(ax,'equal')
hold(ax,'on')

%currCentroid = evalin('base','currCentroid');
finalCentroid = evalin('base','finalCentroid');
if nargin == 7
    currCentroid = evalin('base','currCentroid');
else
    currCentroid = finalCentroid{cameraNum,currView}(currFrame,:);
end
for view = 1:size(finalCentroid,2)
    if ~isnan(finalCentroid{cameraNum,view}(currFrame,1))
        plot(ax,finalCentroid{cameraNum,view}(currFrame,1),finalCentroid{cameraNum,view}(currFrame,2),'o','LineWidth',2);
        text(ax,finalCentroid{cameraNum,view}(currFrame,1)+5,finalCentroid{cameraNum,view}(currFrame,2)+5,num2str(view),'Color','green','FontSize',20);
    end
end
if ~isnan(finalCentroid{cameraNum,currView}(currFrame,1))
    ax.XLim = finalCentroid{cameraNum,currView}(currFrame,1)+[-50 50];
    ax.YLim = finalCentroid{cameraNum,currView}(currFrame,2)+[-50 50];
end
if ~isnan(currCentroid)
    dragpoints(ax,currCentroid)
end
% if ~all(isnan(currCentroid))
%     %h = plot(ax,currCentroid(1),currCentroid(2),'rx','LineWidth',2);
%     dragpoints(ax,currCentroid)
% end
hold(ax,'off')

end