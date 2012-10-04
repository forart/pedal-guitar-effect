% Difference equation taken from DAFX chapter 2

clear all;
close all;

infile = 'song.wav';

% read in wav sample and obtain some values
[ x, fs, N ] = wavread(infile);

%%%%%%% EFFECT COEFFICIENTS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% damping factor. The lower the damping factor, the smaller the pass band
damp = 0.05;

% min and max centre cutoff frequency of variable bandpass filter
minf=500;
maxf=3000;

% phaser frequency, how many Hz per second are cycled through
Fw = 2000; 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% change in centre frequency per sample (Hz)
%delta=0.1; --> 0.1 => at 44100 samples per second should mean 4.41kHz Fc shift per sec
delta = Fw/fs;

% create triangle wave of centre frequency values
Fc=minf:delta:maxf;
while(length(Fc) < length(x) )
    Fc= [ Fc (maxf:-delta:minf) ];
    Fc= [ Fc (minf:delta:maxf) ];
end

% trim tri wave to size of input
Fc = Fc(1:length(x));

% difference equation coefficients
F1 = 2*sin((pi*Fc(1))/fs);  % must be recalculated each time Fc changes
Q1 = 2*damp;                % this dictates size of the pass bands
yh=zeros(size(x));          % create emptly out vectors
y=zeros(size(x));
yl=zeros(size(x));

% first sample, to avoid referencing of negative signals
yh(1) = x(1);
y(1) = F1*yh(1);
yl(1) = F1*y(1);

% apply difference equation to the sample, but starting in the second one (the first one was created before)
for n=2:length(x),
    
    %Notch Filter (Bandreject (BR)/Bandpass(BP))
    
	x=0.7*sin(2*pi*50*t)+sin(2*pi*120*t);
	wo = fo/(fs/2);  %fo is the tone that should be eliminated
	bw = wo/35; %the BW of the notch located at wo
	[b,a] = iirnotch(wo,bw);
	y=filter(b,a,x);
    %Review the comments of
    %http://www.mathworks.com/matlabcentral/newsreader/view_thread/292960
	%y=filter(b,a,x);yh(n) = x(n) - yl(n-1) - Q1*y(n-1);
    %y(n) = F1*yh(n) + y(n-1);
    %yl(n) = F1*y(n) + yl(n-1);
	%End of Notch Filter
    
    F1 = 2*sin((pi*Fc(n))/fs);
end

%normalise
max_y = max(abs(y));
y = y/max_y;

% write output wav files
wavwrite(y, fs, N, 'phaser.wav');

%and we show it
figure(1)
hold on
plot(x,'r');
plot(y,'b');
title('Phaser and Original Signal');