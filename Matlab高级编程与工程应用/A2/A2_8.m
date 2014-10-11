close all;clear all;clc;

FS = 8000;
x = zeros(FS,1);

x(1) = 1;   % 初始有一个信号
last = 1;   % 记录上个信号位置
PT = 85;
for k = 2:FS
    if k-last==PT   % 以上个信号的基音周期为准
        m = ceil(k/80);
        PT = 80+5*mod(m,50);
        x(k) = 1;
        last = k;
    end
end
sound(x,FS);