close all;clear all;clc;

FS = 8000;
N = round(FS/200)   % 1s��һ��FS���㣬Ƶ����200Hz��1s��Ӧ��200���㣬ÿN��һ��
NS = round(FS/N)    % һ��FS/N��200��

x = double(mod([1:FS],N)==0);   % ����ͬ�࣬�׸��ź���N�������1

N1 = round(FS/300);
x1 = double(mod([1:FS],N1)==0);

sound([x,zeros(1,4000),x1],FS);