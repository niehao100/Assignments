close all;clear all;clc;

a1 = 1.3789;
a2 = -0.9506;
B = 1;
A = [1,-a1,-a2];
FS = 8000;

poles = roots(A);
% 已经知道只有两个共轭的根，就只求一个了
poles(1) = abs(poles(1))*exp((150*2*pi/FS+abs(angle(poles(1))))*1j);
poles(2) = conj(poles(1));
A = poly(poles);
a1 = -A(2)
a2 = -A(3)
