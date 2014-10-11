close all;clear all;clc;

img = imread('process/graygroundtruth.jpg');
%img = imread('process/graycapture.jpg');
[M,N] = size(img);
rows = mean(img,2);
cols = mean(img)';
rows = rows-mean(rows);
cols = cols-mean(cols);

row_f = fft(rows);
col_f = fft(cols);
figure;
subplot(3,1,1);
plot(rows);
subplot(3,1,2);
plot(abs(row_f));
subplot(3,1,3);
plot(angle(row_f));
figure;
subplot(3,1,1);
plot(cols);
subplot(3,1,2);
plot(abs(col_f));
subplot(3,1,3);
plot(angle(col_f));
% row_f = row_f(1:ceil((length(row_f)-1)/2));
% col_f = col_f(1:ceil((length(col_f)-1)/2));
% row_a = abs(row_f);
% col_a = abs(col_f);

% % 假设可能的行列数是5:20
% [~,m] = max(row_a(6:21));
% [~,n] = max(col_a(6:21));
% m = m+4;
% n = n+4;
% h = M/m;
% w = N/n;
m = M/h
n = N/w
x = abs((row_p/pi/2)*h)
y = abs((col_p/pi/2)*w)
for k = 1:(m-1)*(n-1)
    subplot(m-1,n-1,k);
    a = mod(k-1,n-1);       % 左侧已经有a个
    b = ceil(k/(n-1))-1;    % 上边已经有b个
    imshow(img(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w)));
end

% subplot(2,1,1);
% plot(angle(row_f));
% subplot(2,1,2);
% plot(angle(col_f));
% 
% subplot(2,1,1);
% plot(row_a);
% subplot(2,1,2);
% plot(col_a);