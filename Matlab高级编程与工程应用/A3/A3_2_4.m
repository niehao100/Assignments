close all;clear all;clc;

load('hall.mat');
block = double(hall_gray(61:68,41:48));
size_block = size(block);
block = block-128*ones(size_block);
subplot(2,2,1);
imshow(uint8(block+128*ones(size_block)));
subplot(2,2,2);
block = dct2(block);
imshow(uint8(idct2(block.')+128*ones(size_block)'));
subplot(2,2,3);
imshow(uint8(idct2(rot90(block,1))+128*ones(size_block)'));
subplot(2,2,4);
imshow(uint8(idct2(rot90(block,2))+128*ones(size_block)));