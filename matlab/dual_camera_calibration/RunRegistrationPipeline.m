addpath(genpath([pwd '\Utils']))
addpath(genpath([pwd '\Subroutines']))
clear;close all;daqreset

% set up paths
calibrationFolder = 'C:\Users\lt532\Desktop\WalkingChamberRig\Data\Calibrations\';
figureFolder = 'C:\Users\lt532\Desktop\WalkingChamberRig\Data\Calibrations\';
runAcq = true;
plotFig = true;

%% Set up the trigger object
if runAcq
    nSec = 5;
    d = daq('ni');
    %d.Rate = 100;  % Doubled to create the on/off DAQ pulse
    d.addoutput('Dev2','ao0','voltage'); % Dual Basler camera trigger
    d.addoutput('Dev2','ao1','Voltage');
    ramp = [reshape(ones(nSec*d.Rate,1)*[0:0.1:5,0],[],1)];
    daq_output = [zeros(size(ramp)),ramp];
    d.preload(daq_output);
    d.start();
end

r = 9.5/2;%in mm
r = r./10;% in cm
A = pi*r.^2;

T = readtable('617_NoPinHole_1.csv');
startNdx = find(T.DelimiterUsed_==0);
tt = T.DelimiterUsed_(startNdx:end);
power = T.Var4(startNdx:end);% in Watts
power = power*1000;% mW

int = power./A;

[pks,ndx] = findpeaks(gradient(int'),'MinPeakHeight',0.05);
ndx = [1,ndx,ndx(end)+50];

int_step = zeros(numel(ndx)-1,1);
for i = 1:numel(ndx)-1
    int_step(i) = mean(int((ndx(i)+10):(ndx(i+1)-10)));
end
daq_out = [eps:0.1:5]';

dq2Int = fit(daq_out,int_step,'poly3');
Int2dq = fit(int_step,daq_out,'poly3');

figure;set(gcf,'Position',[2 42 838 924])
subplot(2,1,1);
plot(dq2Int,daq_out,int_step);
legend('Location','best')
xlabel('daq output');ylabel('Intensity')
subplot(2,1,2);
plot(Int2dq,int_step,daq_out);
legend('Location','best')
xlabel('Intensity');ylabel('daq output');
exportgraphics(gcf,[figureFolder '_IntCalibration.pdf'],"Append",true,'ContentType','vector')

save([calibrationFolder 'IntCalibration.mat'],'daq_out','int_step','dq2Int','Int2dq')
