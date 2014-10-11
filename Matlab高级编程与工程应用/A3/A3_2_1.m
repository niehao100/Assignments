close all;clear all;clc;

load('hall.mat');
block = hall_gray(9:16,129:136);
result1 = dct2(block-uint8(128*ones(8,8)))
result2 = dct2(block)-dct2(128*ones(8,8))
difference = result1-result2