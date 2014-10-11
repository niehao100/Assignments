close all;clear all;clc;

a1 = 1.3789;
a2 = -0.9506;
B = 1;
A = [1,-a1,-a2];    % 这里应当有两个负号

poles = roots(A);
angle(poles(1))/2/pi
figure;
zplane(B,A);
figure;
freqz(B,A);
figure;
impz(B,A);
figure;
impulse_z = [1:300];
impulse_z = filter(B,A,impulse_z==1);   % 单位样值序列就直接用impluse_z==1
stem(impulse_z);