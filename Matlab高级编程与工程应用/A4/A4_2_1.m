close all;clear all;clc;

img = imread('process/graygroundtruth.jpg');
[M,N] = size(img);
rows = mean(img,2);
cols = mean(img)';
rows = rows-mean(rows);
cols = cols-mean(cols);


K = 1000;
[~,omg,FT,~] = prefourier([0,N],N,[0,pi],K);
col_f = FT*cols;
[~,m] = max(abs(col_f));
w = 2*pi/(omg(m));
col_p = angle(col_f(m));

[~,omg,FT,~] = prefourier([0,M],M,[0,pi],K);
row_f = FT*rows;
[~,n] = max(abs(row_f));
h = 2*pi/(omg(n));
row_p = angle(row_f(n));

m = floor(M/h);
n = floor(N/w);
x = abs((row_p/pi/2)*h);
y = abs((col_p/pi/2)*w);
for k = 1:m*n
    subplot(m,n,k);
    a = mod(k-1,n);     % 左侧已经有a个
    b = ceil(k/n)-1;    % 上边已经有b个
    imshow(img(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w)));
end