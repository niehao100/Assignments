close all;clear all;clc;

load hall hall_gray;
load JpegCoeff;

[dcbin,acbin] = jpegencode(hall_gray,DCTAB,ACTAB,QTAB);

[m,n] = size(hall_gray);
m = uint16(m);  % 由于按8的倍数补齐了图像，必须储存图像大小
n = uint16(n);  % 根据百度百科的描述，JPEG标准支持最大uint16的图像线度
save('jpegcodes.mat','dcbin','acbin','m','n');