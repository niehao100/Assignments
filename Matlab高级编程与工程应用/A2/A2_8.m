close all;clear all;clc;

FS = 8000;
x = zeros(FS,1);

x(1) = 1;   % ��ʼ��һ���ź�
last = 1;   % ��¼�ϸ��ź�λ��
PT = 85;
for k = 2:FS
    if k-last==PT   % ���ϸ��źŵĻ�������Ϊ׼
        m = ceil(k/80);
        PT = 80+5*mod(m,50);
        x(k) = 1;
        last = k;
    end
end
sound(x,FS);