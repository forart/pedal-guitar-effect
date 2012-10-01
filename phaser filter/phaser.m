% BP filter with narrow pass band, Fc oscillates up and down the spectrum
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
yb=zeros(size(x));
yl=zeros(size(x));

% first sample, to avoid referencing of negative signals
yh(1) = x(1);
yb(1) = F1*yh(1);
yl(1) = F1*yb(1);

% apply difference equation to the sample
for n=2:length(x),
    
    %Notch Filter (Bandreject (BR)/Bandpass(BP))
    
	x=0.7*sin(2*pi*50*t)+sin(2*pi*120*t);
	wo = 50/(1000/2); 
	bw = wo/35;
	[b,a] = iirnotch(wo,bw);
    %Review the comments of
    %http://www.mathworks.com/matlabcentral/newsreader/view_thread/292960
	%y=filter(b,a,x);yh(n) = x(n) - yl(n-1) - Q1*yb(n-1);
    %yb(n) = F1*yh(n) + yb(n-1);
    %yl(n) = F1*yb(n) + yl(n-1);
	%End of Notch Filter
    
    F1 = 2*sin((pi*Fc(n))/fs);
end

%normalise
maxyb = max(abs(yb));
yb = yb/maxyb;

% write output wav files
wavwrite(yb, fs, N, 'phaser.wav');

%and we show it
figure(1)
hold on
plot(x,'r');
plot(yb,'b');
title('Phaser and Original Signal');