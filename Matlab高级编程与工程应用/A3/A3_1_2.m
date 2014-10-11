close all;clear all;clc;

load hall;
hall_size = size(hall_color);   % 获取图片大小
hall_size = hall_size(1:2);     % 去掉通道数3
radius = min(hall_size)/2;      % 计算半径
center = hall_size/2;           % 计算圆心
n = ceil(2*pi*radius);          % 点数设为周长
hall1 = hall_color;
for k = 1:n
    x = ceil(radius*cos(k/n*2*pi)+center(1));
    y = ceil(radius*sin(k/n*2*pi)+center(2));
    hall1(x,y,1) =  255;
    hall1(x,y,2) =  0;
    hall1(x,y,3) =  0;
end
subplot(2,1,1);
imshow(hall1);
imwrite(hall1,'hall1.bmp','bmp');
hall2 = mod(ones(hall_size(1),1)*[1:hall_size(2)]+...
    [1:hall_size(1)]'*ones(1,hall_size(2)),2);  % 生成01棋盘矩阵
hall2 = uint8(cat(3,hall2,hall2,hall2));
hall2 = hall_color.*hall2;      % 掩去0位置的像素，置为0
subplot(2,1,2);
imshow(hall2);
imwrite(hall2,'hall2.bmp','bmp');