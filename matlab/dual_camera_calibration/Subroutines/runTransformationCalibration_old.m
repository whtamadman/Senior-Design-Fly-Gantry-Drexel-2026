function [] = runTransformationCalibration_old(rectCenterAll,XX,YY,meta)

folder = meta.registrationVideoFolder;
fileName = meta.registrationFile;

% get the information on the stack
info = imfinfo([folder fileName]);
Width = info(1).Width;
Height = info(1).Height;
nStack = length(info);

% get the circle centers in the captured stack
I = zeros(Width,Height,nStack);
for k = 1:nStack
    I(:,:,k) = imread([folder fileName], k);
end
maxI = max(I,[],'all');
I2 = I./maxI;
I2 = I2>0.04;%0.2
cent = zeros(nStack,2);
offset = 0;
for k = 1:nStack
    s = regionprops(I2(:,:,k), 'Centroid',"Area");
    try
        [~,maxNdx] = max([s.Area]);
        cent(k,:) = s(maxNdx).Centroid;
    catch
        offset = offset+1;
    end
end
ImagePoints = cent(offset+1:end,:);
dlpPoints = rectCenterAll(1:end-offset,:);
%% get the transformation matrix
% get the transformation matrix from camera to projector
tform_cam2proj = fitgeotrans(ImagePoints,dlpPoints,'affine');
% forward transform the testing points
[x,y] = transformPointsForward(tform_cam2proj,ImagePoints(:,1),ImagePoints(:,2));
I_maxProj = max(I2>0.2,[],3);

% plot the information
figure;set(gcf,'Position',[2 42 838 924]);
subplot(2,1,1);
imagesc(max(I2>0.2,[],3));hold on;
scatter(ImagePoints(:,1),ImagePoints(:,2),'*r');hold off
colormap(hot)
legend({'Tracked'});title('Thresholded Microscope Image')
xlabel('Microscope x-pos');xlabel('Microscope y-pos');
subplot(2,1,2);
scatter(dlpPoints(:,1),dlpPoints(:,2),'k');hold on;
scatter(x,y,'r*');hold off;
legend({'GT','predicted'})
xlabel('Projector x-pos');xlabel('Projector y-pos');

%% get the conversion factor from pixels in the dmd screen to pixels in hcimage
tform_proj2cam = invert(tform_cam2proj);
[x,y] = transformPointsForward(tform_proj2cam,rectCenterAll(:,1),rectCenterAll(:,2));
camCoord = [x,y];

XX_cam = reshape(camCoord(:,1),size(XX));
YY_cam = reshape(camCoord(:,2),size(YY));

cf_x = abs(mean(diff(XX,[],2)./diff(XX_cam,[],2),'all'));
cf_y = abs(mean(diff(YY,[],1)./diff(YY_cam,[],1),'all'));
cf = mean([cf_x cf_y]);

save([meta.calibrationFolder meta.calibrationFileName],'I_maxProj',...
    'ImagePoints','dlpPoints','tform_cam2proj','offset','cf_x','cf_y','cf')


end
