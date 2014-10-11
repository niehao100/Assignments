close all;clear all;clc;

load hall;
img = hall_gray;
v = zigzag(img);
img1 = uint8(izigzag(v,size(img)));
max(max(img-img1))
imshow(img1);