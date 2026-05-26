function [] = runTransformationAcquisition(rectCenterAll,runAcq,offset,color)
% Clear the workspace and the screen
daqreset;imaqreset;sca;
global flpTime
%% 
% basic parameters
nStim = size(rectCenterAll,1);
frameRate=2;
totalTime=nStim./frameRate;
sampleRate=1200;

%% set up stimulus
circleRadiusAll = 5.*ones(nStim,1);
circleColorAll = repmat({color},nStim,1);

circleMatrixAll = [(rectCenterAll-circleRadiusAll./2) (rectCenterAll+circleRadiusAll./2)];
circleMatrixAll = num2cell(circleMatrixAll,2);
circleRadiusAll = circleRadiusAll.*1.01;

% add a frame delay
circleMatrixAll = [circleMatrixAll;repmat(circleMatrixAll(end),offset,1)];
circleColorAll = [circleColorAll;repmat(circleColorAll(1),offset,1)];
circleRadiusAll = [circleRadiusAll;repmat(circleRadiusAll(end),offset,1);];
circleMatrixAll = mat2cell(reshape(circleMatrixAll,1,[]),1,ones(1,numel(circleMatrixAll)));
circleColorAll = mat2cell(reshape(circleColorAll,1,[]),1,ones(1,numel(circleColorAll)));
circleRadiusAll = mat2cell(reshape(circleRadiusAll,1,[]),1,ones(1,numel(circleRadiusAll)));
transitionNdx = repmat({true},numel(circleRadiusAll),1);
dt = 0;
flpTime = zeros(numel(circleRadiusAll),1);


%%
if runAcq
    % defining output
    cameraTrigger(:,1) = initializeCameraTrigger(totalTime,frameRate,sampleRate);
    cameraTrigger(:,2) = initializeCameraTrigger(totalTime,frameRate,sampleRate);
    cameraTrigger(:,3) = initializeCameraTrigger(totalTime,frameRate,sampleRate);
    cameraTrigger(:,4) = initializeCameraTrigger(totalTime,frameRate,sampleRate);

    % initialize DAQ
    [s] = initializeDAQ_Patch(sampleRate,cameraTrigger,'DataAcquisition');
    % for analog out
    %s.NotifyWhenDataAvailableExceeds = (sampleRate./frameRate);
    s.ScansAvailableFcnCount = (sampleRate./frameRate);
    disp('Data acquisition starting');

    %% set up projector
    [~,window,~,~] = setupProjector;
    vb1 = Screen('Flip', window);

    %% Run Acquisition
    %start the listener in the background
%     dataListener = s.addlistener('DataAvailable', @(src,event) updateProjectorCircleIntensity_noZ...
%         (src,event,window,circleMatrixAll,circleColorAll,circleRadiusAll,vb1));% call listener when data is available to loop to next position
    s.ScansAvailableFcn = @(src,event) updateProjectorCircleIntensity_noZ...
        (src,event,window,circleMatrixAll,circleColorAll,circleRadiusAll,transitionNdx,offset,dt);
    if offset>0
        init.NumScansAcquired = 0;
        init.ScansAvailableFcnCount = s.ScansAvailableFcnCount;
        updateProjectorCircleIntensity_noZ(init,[],window,circleMatrixAll,...
            circleColorAll,circleRadiusAll,transitionNdx,offset,dt)
    end

    disp('starting');
    s.start();
    pause(totalTime+0.5)
%     s.startBackground(); %start background is code to start data acquisition
%     s.wait();
    display(['scans acquired equals ', num2str(s.NumScansAcquired)]);
    sca;
end

end

