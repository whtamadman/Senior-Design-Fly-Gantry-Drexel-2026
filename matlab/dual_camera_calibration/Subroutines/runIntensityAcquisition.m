function [data] = runIntensityAcquisition(circleCenter,powerMeter_rate,wavelength,test_meter,runAcq)
% Clear the workspace and the screen
sca;daqreset;
imaqreset;

%% get stimulus
color = wavelength2color(wavelength);
circleColorAll = num2cell(repmat(color,21,1).*(0:0.05:1)',2);
nColor = numel(circleColorAll);

circleDiameterAll = (300:100:500)';
nDiam = numel(circleDiameterAll);

rectCenterAll = repmat(circleCenter,nDiam,1);
circleMatrixAll = [(rectCenterAll-circleDiameterAll./2) (rectCenterAll+circleDiameterAll./2)];
circleMatrixAll = num2cell(circleMatrixAll,2);

combNdx = CombVec(1:nColor,1:nDiam);
circleComb = circleMatrixAll(combNdx(2,:));
colorComb = circleColorAll(combNdx(1,:));
circleDiameterAll = circleDiameterAll(combNdx(2,:)).*1.01;

%%
DMD_framerate = 5;
nFrames = numel(circleDiameterAll);
nReadingPerFrame = floor(powerMeter_rate./DMD_framerate);
totalTime = nFrames./DMD_framerate;

if runAcq
    %set up the projector
    [~,window,~,~] = setupProjector;
    Screen('Flip', window);
    power_reading = zeros(nFrames,nReadingPerFrame);
    powerUnits = cell(nFrames,nReadingPerFrame);
    % loop through each intensity/circle size
    for frame = 1:nFrames
        Screen('FillOval', window, colorComb{frame}, circleComb{frame}, circleDiameterAll(frame));
        Screen('Flip', window);
        % read in the power reading
        for r = 1:nReadingPerFrame
            test_meter.updateReading(0);
            power_reading(frame,r) = test_meter.meterPowerReading;
            powerUnits{frame,r} = test_meter.meterPowerUnit;
        end
    end
    sca;
end

data.circleDiameterAll = circleDiameterAll./1.01;
data.circleColorAll = circleColorAll;
data.circleComb = circleComb;
data.colorComb = colorComb;
data.stimframeRate = DMD_framerate;
data.totalTime = totalTime;
data.power_reading = power_reading;
data.powerUnits = powerUnits;
end

