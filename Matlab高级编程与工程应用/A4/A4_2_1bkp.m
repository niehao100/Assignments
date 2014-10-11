close all;clear all;clc;

img = imread('process/graygroundtruth.jpg');
%img = imread('process/graycapture.jpg');
[M,N] = size(img);
rows = mean(img,2);
cols = mean(img)';
%cols = mod(1:length(cols),100)';
rows = rows-mean(rows);
cols = cols-mean(cols);


K = 1000;
[t,omg,FT,IFT] = prefourier([0,N],N,[0,pi],K);
col_f = FT*cols;
[~,m] = max(abs(col_f));
w = 2*pi/(omg(m));
col_p = angle(col_f(m))
% subplot(3,1,1);
% plot(cols);
% subplot(3,1,2);
% plot(omg,abs(col_f));
% subplot(3,1,3);
% plot(omg,angle(col_f))
% return

[t,omg,FT,IFT] = prefourier([0,M],M,[0,pi],K);
row_f = FT*rows;
[~,n] = max(abs(row_f));
h = 2*pi/(omg(n));
row_p = angle(row_f(m))
% figure;
% subplot(2,1,1);
% plot(rows);
% subplot(2,1,2);
% plot(omg,abs(row_f));
%  return
% % % [t,omg,FT,IFT] = prefourier([0,N],N,[0,N]/N,1000);
% % % subplot(2,1,2);
% % % plot(omg,col_a);
% % % col_f = FT*cols';
%return

% row_f = fft(rows);
% col_f = fft(cols);
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
m = floor(M/h)
n = floor(N/w)
x = abs((row_p/pi/2)*h)
y = abs((col_p/pi/2)*w)
for k = 1:m*n
    subplot(m,n,k);
    a = mod(k-1,n);       % 左侧已经有a个
    b = ceil(k/n)-1;    % 上边已经有b个
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