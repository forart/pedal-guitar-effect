clear all;
close all;

infile = 'song.wav';
% read in wav sample and obtain some values
[ x, fs, N ] = wavread(infile);

%[y] = flange(fs, v, x, r)
%
%   This is a basic flanging effect.
%
%      fs = Sample rate
%      v = Variation.
%      x = Input audio signal. This should be a column vector.
%      r = Rate.
%
%   Example:     
%      >>y = flange(fs,0.002,x,0.5);%
%

%%%%%%% EFFECT COEFFICIENTS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Variation factor
v = 0.002;
% Rate
r=0.5;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [y]=flange(fs, v, y, r);

%we start to create the signal variating the sample rate
md= ceil(v*fs);
n=1:length(y)+md;
v=round(v*fs);
z=zeros(md,1);
y=[z;y;z];
rr=2*pi/round(fs*r);
b=round((v/2)*(1-cos(rr.*n)));
y=y(n+md)+y(n+md-b); %we combine the two signals to create the flange effect

%now we normalise
m=max(abs(y));
m=m/max(abs(y));

%the final signal = the combination of both and shortened to the initial lenght
y=m*y;

% write output wav files
wavwrite(y, fs, N, 'flanger.wav');

%and we show it
figure(1)
hold on
plot(x,'r');
plot(yb,'b');
title('Flanger and Original Signal');