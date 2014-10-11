close all;clear all;clc;

img = im2double(imread('process/graygroundtruth.jpg'));

w = 80;
h = 100;

m = 7;
n = 12;

x = 25;
y = 35;

blocks=zeros(h,w,19);

count = 0;
for k = 1:m*n
    [b,a] = ind2sub([m,n],k);
    new_img = img(y+b*h-h+1:y+b*h,x+a*w-w+1:x+a*w);
    for kk = 1:count+1
        if kk==count+1
           count = count+1;
           blocks(:,:,count) = new_img;
           break;
        end
        if norm(new_img-blocks(:,:,kk))<1
            blocks(:,:,kk) = (new_img+blocks(:,:,kk))/2;
            break;
        end
    end
end

save('blocks','blocks');

for k = 1:19
    imshow(blocks(:,:,k));
    pause;
end