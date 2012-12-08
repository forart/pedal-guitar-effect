function y = flanger_m();

[x, fs, n] = wavread('acoustic.wav'); %read in wav file 

%%%%%%% EFFECT COEFFICIENTS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% it's used for increase the delayed effect amplitude
a=1;

%Calculate the number of samples in the delay
    % No. Of Samples = D = delay*fs
delay = 10e-3; % delay = 10ms = Max delay for having 512 samples at 48Khz of fs (actually for 512 is delay = 0,010666 sec.)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


D = ceil(delay*fs); %Nº of samples rounded towards positive. Max should be 512 samples.
xlen = length(x);
y = zeros(size(x)); %makes our final signal, but all made of 0s.
delay = zeros(size(x)); %returns an array the same size as x consisting of all zeros.


for i = 1:1:D+1 %makes our 0s signal y being as x
    y(i) = x(i);
end;
for i = D+1:1:xlen % creates the matrix of delay
    delay(i) = abs(round(D * cos(2*pi*i/((xlen-D-1))))); % creates the delay
end;
plot(delay);
for i = D+1:1:xlen % delays the signal
    y(i) = x(i) + a*x(i-delay(i)); %original sound with itself delayed added
end;

% write output wav files
wavwrite(y, fs, n, 'flanger.wav');

% make it sound
sound(y,fs);

%and we show it
figure(1)
plot(x,'r');
title('Original Signal');
figure(2)
plot(y,'b');
title('Flanger Signal');