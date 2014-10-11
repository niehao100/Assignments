close all;clear all;clc;

load jpegcodes;
load JpegCoeff;
load hall hall_gray;

img = jpegdecode(dcbin,acbin,m,n,DCTAB,ACTAB,QTAB);
MSE = sum(sum((img-hall_gray).^2))/double(m)/double(n);
PSNR = 10*log10(255*255/MSE)
imshow(img);