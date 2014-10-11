close all;clear all;clc;

load JpegCoeff;
load hall hall_gray;

QTAB = QTAB/2;

[dcbin,acbin] = jpegencode(hall_gray,DCTAB,ACTAB,QTAB);   % 传入一半的QTAB
[m,n] = size(hall_gray);

img = jpegdecode(dcbin,acbin,m,n,DCTAB,ACTAB,QTAB);

m*n*8/(length(dcbin)+length(acbin)+32)

MSE = sum(sum((img-hall_gray).^2))/m/n;
PSNR = 10*log10(255*255/MSE)
imshow(img);