close all;clear all;clc;

load JpegCoeff;
load snow;

[dcbin,acbin] = jpegencode(snow,DCTAB,ACTAB,QTAB);
[m,n] = size(snow);
imshow(snow);

img = jpegdecode(dcbin,acbin,m,n,DCTAB,ACTAB,QTAB);

m*n*8/(length(dcbin)+length(acbin)+32)

MSE = sum(sum((img-snow).^2))/m/n;
PSNR = 10*log10(255*255/MSE)
figure;
imshow(img);