function [stim2Int] = runIntensityCalibration(data,delay,meta,obj,color)

circleDiameterAll = data.circleDiameterAll(1:end-delay);
colorComb = data.colorComb(1:end-delay);
load([meta.calibrationFolder meta.calibrationFileName],'cf','cf_x','cf_y');% in theory should model as an oval with cf_x,cf_y

% load the intensity data from the calibration file
csv_file = fopen([meta.calibrationFolder meta.intCalibrationFileName],'rt');
formatSpec = '%s%s';
csv = textscan(csv_file, formatSpec, 'Delimiter', ';');
startLine = find(~cellfun('isempty',strfind(csv{1,1},'Time of day (hh:mm:ss)')))+1;
convFun =@(x) str2double(strrep(x, ',', '.'));
fclose(csv_file);

% get the calibration file framerate
timestamps  = csv{1,1}(startLine+1:2:end);
formatIn = 'HH:MM:SS';
thorlabsFrameRate = round(1./mean(diff(datenum(timestamps,formatIn))*24*60*60));

% get the recorded power and conver from W to mW
power = cellfun(@(x) convFun(x), csv{1,2}(startLine+1:2:end));
power = power.*10^3;% conver to mW

% get the baseline power and intensity
baselinePower = min(power);
ObjectiveArea = pi.*(obj.FN./obj.mag./2).^2;
baselineIntensity = baselinePower./ObjectiveArea;%mW/cm.^2

% baseline subtract power
power = power-baselinePower;

samplesPerStim = thorlabsFrameRate./data.stimframeRate;
totalSamples = samplesPerStim*numel(colorComb);
%totalSamples = data.totalTime.*thorlabsFrameRate;

% remove the initial peak in signal when psychtoolbox turns on
power(1:round(thorlabsFrameRate*25)) = 0;%25 seconds
% get the start and end index of the calibration sequence to index power
[~,endNdx]=min(diff(smooth(power,3)));endNdx = endNdx-1;
startNdx = endNdx-totalSamples+1;
if startNdx<1
    power = [zeros(abs(min(0,startNdx))+1,1); power(1:endNdx)];
else
    power = power(startNdx:endNdx);
end

% reshape the recorded power into matrix where each row is a different
% stimulus
power2 = reshape(power,samplesPerStim,[]);
% take the average recorded power for each stimulus
try
    % using the middle values lower chance of index mismatch
    meanPower = mean(power2(2:end-1,:));
catch
    meanPower = mean(power2(1:end,:));
end

% adjust for small linear baseline drift by indexing regions where the
% signal is set to zero. Note that while this drift is small (~10^-4 mW), 
% the error in intensity will magnified under a small stimulus ROI
powerZeros = power2;
powerZeros(:,sum(cell2mat(colorComb),2)~=0) = nan;
powerZeros([1,2,end-1,end],:) = nan;
powerZeros = reshape(powerZeros,[],1);
time = (1:totalSamples)'.*thorlabsFrameRate;

% then use ordinary least squares to model the linear drift
X_pred = [ones(totalSamples,1),time];
X = X_pred(~isnan(powerZeros),:);
X_T = X';
y = powerZeros(~isnan(powerZeros));
OSL_params = (X_T*X)\X_T*y;

% correct for the baseline power 
baselinePowerCorr = reshape(X_pred*OSL_params,samplesPerStim,[]);
meanPowerCorr = mean(power2(2:end-1,:)-baselinePowerCorr(2:end-1,:));

% get the area of the stimulus circles
radius = circleDiameterAll./2./cf;% convert to pixel space
radius = radius.*obj.cf_Pxl2um;% convert to real space (um)
radius = radius./10000;% convert from um to cm
Area = pi.*((radius).^2); % in cm^2

% get the unique stimulus and area sizes present in the calibration stimulus
[uniqueRadius,~,ic] = unique(circleDiameterAll);
[uniqueColor,~,~] = unique(cell2mat(colorComb),'rows');
uniqueColor = nanmean(uniqueColor./color(1,1:3),2);
nUniqueRadius = size(uniqueRadius,1);
nUniqueColor = size(uniqueColor,1);

% get eh average power and area for each stimulus pattern
powerByDiam = zeros(nUniqueRadius,nUniqueColor);
powerCorrByDiam = zeros(nUniqueRadius,nUniqueColor);
areaByDiam = zeros(nUniqueRadius,nUniqueColor);
for i = 1:nUniqueRadius
    powerByDiam(i,:) = meanPower(ic==i);
    powerCorrByDiam(i,:) = meanPowerCorr(ic==i);
    areaByDiam(i,:) = Area(ic==i);
end

Intensity = powerByDiam./areaByDiam;
Intensity_corr = powerCorrByDiam./areaByDiam;

% fit the average intensity curve to a sigmoid
stim2Int.fun = @(p,xval) p(1)+(p(2)-p(1))./(1+10.^((p(3)-xval)*p(4)));
stim2Int.fun_inv = @(p,yval) p(3)-log10((p(2)-yval)./(yval-p(1)))/p(4);
[param,~]=sigm_fit(mean(uniqueColor,2),nanmean(Intensity_corr),[],[],false);
stim2Int.param = param;
stim2Int.dataFile = [meta.calibrationFolder meta.intCalibrationFileName];
fittedIntensityCurve=stim2Int.fun(param,mean(uniqueColor,2));

% update the calibration file
updateCalibrationFile(meta,stim2Int,color)

%% plotting functions
figure;set(gcf,'Position',[2 42 838 924]);
sgtitle([meta.intCalibrationFileName ', Color=' num2str(color(end)) 'nm'], ...
    'interpreter', 'none');

% plots related to the baseline drift
subplot(4,2,1);
scatter(time,powerZeros,'or');hold on;
plot(time,X_pred*OSL_params,'k');
xlabel('time (s)');ylabel('Baseline Drift Power (mW)')
subplot(4,2,2);
plot(time,power,'k','LineWidth',1);hold on;
plot(time,power-X_pred*OSL_params,'r','LineWidth',1);hold off
legend({'raw','drift corrected'})
xlim([0 max(time)]);ylim([0 inf])
xlabel('time (s)');ylabel('Power (mW)')

% plots related to the measured power
subplot(4,2,3);
plot(uniqueRadius,powerCorrByDiam);
legend(cellstr(num2str(mean(uniqueColor,2))),'Location','best')
xlim([min(uniqueRadius) max(uniqueRadius)])
xlabel('radius');ylabel('Power (mW)')
subplot(4,2,4);
plot(mean(uniqueColor,2),powerCorrByDiam');%red color
legend(cellstr(num2str(uniqueRadius)),'Location','best')
xlim([min(mean(uniqueColor,2)) max(mean(uniqueColor,2))])
xlabel('Normalized Intensity');ylabel('Power (mW)')

% plots related to the stimulus area
subplot(4,2,5);
plot(uniqueRadius,areaByDiam);
%plot(uniqueRadius,areaByDiam.*(10000^2));% convert to um.^2
xlim([min(uniqueRadius) max(uniqueRadius)])
xlabel('radius');ylabel('Area (cm^2)')%ylabel('Area (um^2)')
subplot(4,2,6);
plot(mean(uniqueColor,2),areaByDiam');%red color
%plot(uniqueColor(:,1),areaByDiam.*(10000^2)');%red color
xlim([min(mean(uniqueColor,2)) max(mean(uniqueColor,2))])
xlabel('Normalized Intensity');ylabel('Area (cm^2)')%ylabel('Area (um^2)')

% plots related to the calculated intensity
subplot(4,2,7);
plot(uniqueRadius,Intensity_corr);hold on;
plot([min(uniqueRadius) max(uniqueRadius)],[baselineIntensity baselineIntensity],'r--')
xlim([min(uniqueRadius) max(uniqueRadius)]);
xlabel('radius');ylabel('Intensity (mW/cm^2)')
subplot(4,2,8);
plot(mean(uniqueColor,2),Intensity_corr');hold on;%red color
h(1)=plot([min(mean(uniqueColor,2)) max(mean(uniqueColor,2))],[baselineIntensity baselineIntensity],'r:','linewidth',1);
h(2)=plot(mean(uniqueColor,2), fittedIntensityCurve,'r--','linewidth',1);
legend(h,{'baseline','sigmoid fit'},'Location','best')
xlim([min(mean(uniqueColor,2)) max(mean(uniqueColor,2))])
xlabel('Normalized Intensity');ylabel('Intensity (mW/cm^2)')

end

function [] = updateCalibrationFile(meta,currStim2Int,color)

stim2Int = [];
load([meta.calibrationFolder meta.calibrationFileName],'I_maxProj','stim2Int','stim2IntColor',...
    'ImagePoints','dlpPoints','tform_cam2proj','offset','cf_x','cf_y','cf');

if isempty(stim2Int)
    stim2Int = {currStim2Int};
    stim2IntColor = color;
else
    stim2Int = [stim2Int {currStim2Int}];
    stim2IntColor = [stim2IntColor;color];
end

save([meta.calibrationFolder meta.calibrationFileName],'I_maxProj','stim2Int','stim2IntColor',...
    'ImagePoints','dlpPoints','tform_cam2proj','offset','cf_x','cf_y','cf');

end
