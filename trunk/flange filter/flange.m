function [y]=flange(fs, v, y, r)
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
%   See also WAVREAD and SOUND
%
%Version 1.0
%Once we have the input and output variables, adapt it ^^

md= ceil(v*fs); %we start to create the signal variating the sample rate
n=1:length(y)+md;
v=round(v*fs);
z=zeros(md,1);
m=max(abs(y));
y=[z;y;z];
rr=2*pi/round(fs*r);
b=round((v/2)*(1-cos(rr.*n)));
y=y(n+md)+y(n+md-b); %we combine the two signals to create the flange effect
m=m/max(abs(y));
y=m*y; %the final signal = the combination of both and shortened to the initial lenght
