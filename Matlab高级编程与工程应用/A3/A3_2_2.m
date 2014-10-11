close all;clear all;clc;

load('hall.mat');
block = double(hall_gray(9:16,129:136))-128*ones(8,8);
result1 = dct2(block)
result2 = dct_2d(block)
difference = result2 - result2