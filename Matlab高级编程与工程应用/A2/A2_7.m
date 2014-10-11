close all;clear all;clc;

FS = 8000;
N = round(FS/200)   % 1s钟一共FS个点，频率是200Hz则1s内应有200个点，每N点一个
NS = round(FS/N)    % 一共FS/N，200个

x = double(mod([1:FS],N)==0);   % 利用同余，首个信号在N点而不是1

N1 = round(FS/300);
x1 = double(mod([1:FS],N1)==0);

sound([x,zeros(1,4000),x1],FS);