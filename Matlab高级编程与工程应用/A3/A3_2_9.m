close all;clear all;clc;

load hall hall_gray;
load JpegCoeff;

[dcbin,acbin] = jpegencode(hall_gray,DCTAB,ACTAB,QTAB);

[m,n] = size(hall_gray);
m = uint16(m);  % ���ڰ�8�ı���������ͼ�񣬱��봢��ͼ���С
n = uint16(n);  % ���ݰٶȰٿƵ�������JPEG��׼֧�����uint16��ͼ���߶�
save('jpegcodes.mat','dcbin','acbin','m','n');