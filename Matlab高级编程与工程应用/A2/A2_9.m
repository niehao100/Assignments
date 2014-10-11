close all;clear all;clc;

FS = 8000;
x = zeros(FS,1);
a1 = 1.3789;
a2 = -0.9506;
B = 1;
A = [1,-a1,-a2];

x(1) = 1;
last = 1;
PT = 85;
for k = 2:FS
    if k-last==PT
        m = ceil(k/80);
        PT = 80+5*mod(m,50);
        x(k) = 1;
        last = k;
    end
end

y = filter(B,A,x);
sound(y);