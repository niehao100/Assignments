close all;clear all;clc;

load('jpegcodes.mat','dcbin','acbin','m','n');
load hall hall_gray;
[a,b] = size(hall_gray);
a*b*8/(length(dcbin)+length(acbin)+32)  % ͼ���Сm��nӦ����������