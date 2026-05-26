function [timingMdl] = getDMDTimingCalibration(t_total)

% get the DMD times and wall times over the course of some time period
%t_total = 60;%in seconds
WallTime = zeros(t_total,3);
GetSecsTime = zeros(t_total,3);
for i = 1:t_total
    [GetSecsTime(i,1), WallTime(i,1), ~, ~] = GetSecs('AllClocks');
    pause(1/3);
    [GetSecsTime(i,2), WallTime(i,2), ~, ~] = GetSecs('AllClocks');
    pause(1/3);
    [GetSecsTime(i,3), WallTime(i,3), ~, ~] = GetSecs('AllClocks');
    pause(1/3);
    %DMD_timeOffset(i,:) = WallTime-GetSecsTime;
end

GetSecsTime_lin = reshape(GetSecsTime',[],1);
WallTime_lin = reshape(WallTime',[],1);
timingMdl = fitlm(GetSecsTime_lin,WallTime_lin);
% ypred = predict(timingMdl,GetSecsTime_lin);
% 
% figure;plot(GetSecsTime_lin,WallTime_lin);hold on;
% scatter(GetSecsTime_lin,ypred)

end