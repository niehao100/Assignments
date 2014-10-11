close all;clear all;clc;

img = imread('process/graycapture.jpg');
video_out = 'A4_2_6.mp4';
[M,N] = size(img);
rows = mean(img,2);
cols = mean(img)';
rows = rows-mean(rows);
cols = cols-mean(cols);


K = 1000;
[~,o,FT,~] = prefourier([0,N],N,[0,pi],K);
col_f = FT*cols;
[~,m] = max(abs(col_f));
w = 2*pi/(o(m));
col_p = angle(col_f(m));

[~,o,FT,~] = prefourier([0,M],M,[0,pi],K);
row_f = FT*rows;
[~,n] = max(abs(row_f));
h = 2*pi/(o(n));
row_p = angle(row_f(n));

m = floor(M/h);
n = floor(N/w);
x = abs((row_p/pi/2)*h);
y = abs((col_p/pi/2)*w);
blocks = cell(m,n);
matching = cell(m,n);
for k = 1:m*n
    a = ceil(k/m)-1;    % ����Ѿ���a��
    b = mod(k-1,m);     % �ϱ��Ѿ���b��
    tmp = im2double(img(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w)));
    x_corr = normxcorr2(tmp,img);
        minpeakheight = 0.85;
        binary = x_corr>minpeakheight;
        for kk = 1:m*n
            aa = ceil(kk/m)-1;
            bb = mod(kk-1,m);
            part = binary(round((h-1)/2+y+bb*h+1:(h-1)/2+y+(bb+1)*h),round((w-1)/2+x+aa*w+1:(w-1)/2+x+(aa+1)*w));
            if any(any(part))
                matching{kk}(end+1) = k;
            end
        end
    blocks{b+1,a+1} = tmp;
end
count = 0;
result = zeros(m,n);
matches = [];
for k = 1:m*n
    if result(k)==0
        if any(result(matching{k})) % �Ƿ��Ѿ���ƥ��?
            result(matching{k}) = max(result(matching{k}));
        else
            count = count+1;
            result(matching{k}) = count;
        end
    else
        result(matching{k}) = result(k);
    end
end
addpath(strcat(pwd,'\linkgame'));
steps = omg(result);    % ����֮ǰ�ĺ������㲽��
img_now = img;
% ¼����Ƶ
video_obj=VideoWriter(video_out,'MPEG-4');
open(video_obj);

for k = 1:steps(1)
    img_last = img_now;
    b = steps(4*k-2)-1;
    a = steps(4*k-1)-1;
    img_now(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w)) = 0;
    b = steps(4*k)-1;
    a = steps(4*k+1)-1;
    img_now(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w)) = 0;
    imshow(img_now);
    current_frame=getframe;
    for kk = 1:15   % ֡��30fps
        writeVideo(video_obj,current_frame);
    end
    pause(0.5);
    imshow(img_last);
    current_frame=getframe;
    for kk = 1:15   % ֡��30fps
        writeVideo(video_obj,current_frame);
    end
    pause(0.5);
    imshow(img_now);
    current_frame=getframe;
    for kk = 1:15   % ֡��30fps
        writeVideo(video_obj,current_frame);
    end
    pause(0.5);
end
close(video_obj);