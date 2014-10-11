close all;clear all;clc;

load('hall.mat');
block = double(hall_gray(95:102,57:64));
size_block = size(block);
block = block-128*ones(size_block);
subplot(1,3,1);
imshow(uint8(block+128*ones(size_block)));
subplot(1,3,2);
block = dct2(block);
imshow(uint8(idct2([block(:,1:4),zeros(8,4)])+128*ones(8,8)));
subplot(1,3,3);
imshow(uint8(idct2([zeros(8,4),block(:,5:8)])+128*ones(8,8)));