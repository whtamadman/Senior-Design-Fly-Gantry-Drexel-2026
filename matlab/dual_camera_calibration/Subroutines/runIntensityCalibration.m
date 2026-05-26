function [stim2Int] = runIntensityCalibration(data,meta,obj,color)

circleDiameterAll = data.circleDiameterAll;%(1:end-delay);
colorComb = data.colorComb;%(1:end-delay);
load([meta.calibrationFolder meta.calibrationFileName],'cf','cf_x','cf_y');% in theory should model as an oval with cf_x,cf_y

% get the recorded power and conver from W to mW
%power = cellfun(@(x) convFun(x), csv{1,2}(startLine+1:2:end));
power = data.power_reading.*10^3;% conver to mW
power = power(:,3:end);

% get the baseline power and intensity
baselinePower = min(power(:));
ObjectiveArea = pi.*(obj.FN./obj.mag./2).^2;
baselineIntensity = baselinePower./ObjectiveArea;%mW/cm.^2

% baseline subtract power
power = power-baselinePower;
meanPower = mean(power,2);

% adjust for small linear baseline drift by indexing regions where the
% signal is set to zero. Note that while this drift is small (~10^-4 mW), 
% the error in intensity will magnified under a small stimulus ROI
powerZeros = meanPower;
powerZeros(sum(cell2mat(colorComb),2)~=0,:) = nan;
powerZeros(end,:) = nan;
time = (1:size(powerZeros,1))';

% then use ordinary least squares to model the linear drift
X_pred = [ones(size(powerZeros,1),1),time];
X = X_pred(~isnan(powerZeros),:);
X_T = X';
y = powerZeros(~isnan(powerZeros));
OSL_params = (X_T*X)\X_T*y;

% correct for the baseline power 
baselinePowerCorr = reshape(X_pred*OSL_params,1,[]);
meanPowerCorr = meanPower-baselinePowerCorr';

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
stim2Int.dataFile = [meta.calibrationFolder meta.calibrationFileName];
fittedIntensityCurve=stim2Int.fun(param,mean(uniqueColor,2));

% update the calibration file
updateCalibrationFile(meta,stim2Int,color)

%% plotting functions
figure;set(gcf,'Position',[2 42 838 924]);
sgtitle([meta.calibrationFileName ', Color=' num2str(color(end)) 'nm'], ...
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
    calExist = all(stim2IntColor==color,2);
    if ~any(calExist)
        stim2Int = [stim2Int {currStim2Int}];
        stim2IntColor = [stim2IntColor;color];
    else
        disp('Calibration already exist for this wavelength. Updating the calibration.')
        stim2Int(calExist) = {currStim2Int};
        stim2IntColor(calExist,:) = color;
    end
end

save([meta.calibrationFolder meta.calibrationFileName],'I_maxProj','stim2Int','stim2IntColor',...
    'ImagePoints','dlpPoints','tform_cam2proj','offset','cf_x','cf_y','cf');

end
