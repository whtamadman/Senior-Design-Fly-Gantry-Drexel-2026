function [data] = runIntensityAcquisition(circleCenter,offset,runAcq,color)
% Clear the workspace and the screen
sca;daqreset;
imaqreset;

%% get stimulus
%circleColorAll = num2cell(repmat([0.1 0 0],12,1).*[0,0.5,(1:10)]',2);
circleColorAll = num2cell(repmat(color,21,1).*(0:0.05:1)',2);
%circleColorAll = num2cell(repmat(color,6,1).*(0:0.2:1)',2);
nColor = numel(circleColorAll);

circleDiameterAll = (300:100:500)';%(50:50:300)';
%circleDiameterAll = (300:200:500)';%(50:50:300)';
nRad = numel(circleDiameterAll);

rectCenterAll = repmat(circleCenter,nRad,1);
circleMatrixAll = [(rectCenterAll-circleDiameterAll./2) (rectCenterAll+circleDiameterAll./2)];
circleMatrixAll = num2cell(circleMatrixAll,2);

combNdx = CombVec(1:nColor,1:nRad);
circleComb = circleMatrixAll(combNdx(2,:));
colorComb = circleColorAll(combNdx(1,:));
circleDiameterAll = circleDiameterAll(combNdx(2,:)).*1.01;

% add a 2 frame delay
% circleComb = [repmat(circleComb(1),offset,1);circleComb;repmat(circleComb(1),offset,1)];
% colorComb = [repmat({[0 0 0]},offset,1);colorComb;repmat({[0 0 0]},offset,1)];
% circleDiameterAll = [repmat(circleDiameterAll(1),offset,1);circleDiameterAll...
%     ;repmat(circleDiameterAll(1),offset,1);];
circleComb = [circleComb;repmat(circleComb(1),offset,1)];
colorComb = [colorComb;repmat({[0 0 0]},offset,1)];
circleDiameterAll = [circleDiameterAll;repmat(circleDiameterAll(1),offset,1);];

%%
% basic parameters
frameRate=0.1;
totalTime=numel(circleDiameterAll)./frameRate;
sampleRate=1200;

%%
if runAcq
    % defining output
%     cameraTrigger = initializeCameraTrigger(totalTime,frameRate,sampleRate);
    cameraTrigger(:,1) = initializeCameraTrigger(totalTime,frameRate,sampleRate);
    cameraTrigger(:,2) = initializeCameraTrigger(totalTime,frameRate,sampleRate);
    cameraTrigger(:,3) = initializeCameraTrigger(totalTime,frameRate,sampleRate);
    cameraTrigger(:,4) = initializeCameraTrigger(totalTime,frameRate,sampleRate);
    % initialize DAQ
    [s] = initializeDAQ(sampleRate,cameraTrigger,'DataAcquisition');
    % for analog out
    %s.NotifyWhenDataAvailableExceeds = (sampleRate./frameRate);
    s.ScansAvailableFcnCount = (sampleRate./frameRate);
    disp('Data acquisition starting');
    
    %%
    [~,window,~,~] = setupProjector;
    vb1 = Screen('Flip', window);
    
    %%
    %start the listener in the background
%     dataListener = s.addlistener('DataAvailable', @(src,event) updateProjectorCircleIntensity_noZ...
%         (src,event,window,circleComb,colorComb,circleDiameterAll,vb1));% call listener when data is available to loop to next position
    s.ScansAvailableFcn = @(src,event) updateProjectorCircleIntensity_noZ...
        (src,event,window,circleComb,colorComb,circleDiameterAll,vb1,offset);
    if offset>0
        init.NumScansAcquired = 0;
        init.ScansAvailableFcnCount = s.ScansAvailableFcnCount;
        updateProjectorCircleIntensity_noZ(init,[],window,circleComb,...
            colorComb,circleDiameterAll,vb1,offset)
    end
    disp('starting');
%     s.startBackground(); %start background is code to start data acquisition
    s.start();
    pause(totalTime+0.5)
    display(['scans acquired equals ', num2str(s.NumScansAcquired)]);
    sca;
end

data.circleDiameterAll = circleDiameterAll./1.01;
data.circleColorAll = circleColorAll;
data.circleComb = circleComb;
data.colorComb = colorComb;
data.stimframeRate = frameRate;
data.totalTime = totalTime;

end

