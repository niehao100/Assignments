close all;clear all;clc;

img_rgb = imread('process/colorcapture.jpg');
video_out = 'A4_2_7.mp4';
[M,N,~] = size(img_rgb);
for img_k = 1:3
    img = img_rgb(:,:,img_k);
    rows = mean(img,2);
    cols = mean(img)';
    rows = rows-mean(rows);
    cols = cols-mean(cols);


    K = 1024;
    [~,o,FT,~] = prefourier([0,N],N,[0,pi],K);
    col_f = FT*cols;
    [~,m(img_k)] = max(abs(col_f));
    w(img_k) = 2*pi/(o(m(img_k)));
    col_p = angle(col_f(m(img_k)));

    [~,o,FT,~] = prefourier([0,M],M,[0,pi],K);
    row_f = FT*rows;
    [~,n(img_k)] = max(abs(row_f));
    h(img_k) = 2*pi/(o(n(img_k)));
    row_p = angle(row_f(n(img_k)));

    m(img_k) = floor(M/h(img_k));
    n(img_k) = floor(N/w(img_k));
    x(img_k) = abs((row_p/pi/2)*h(img_k));
    y(img_k) = abs((col_p/pi/2)*w(img_k));
end
m = mean(m);
n = mean(n);
x = mean(x);
y = mean(y);
w = mean(w);
h = mean(h);

% 第二小问，分块
figure;
for k = 1:m*n
    subplot(m,n,k);
    a = mod(k-1,n);     % 左侧已经有a个
    b = ceil(k/n)-1;    % 上边已经有b个
    imshow(img_rgb(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w),:));
end

% 第三小问，最相似的十块
figure;
blocks = cell(m,n);
matching = cell(m,n);
corr_mat = zeros(m*n,m*n);
minpeakheight = 0.77;
for k = 1:m*n
    a = ceil(k/m)-1;    % 左侧已经有a个
    b = mod(k-1,m);     % 上边已经有b个
    tmp = im2double(img_rgb(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w),:));
    x_corr = sqrt(normxcorr2(tmp(:,:,1),img_rgb(:,:,1)).^2 ...
                 +normxcorr2(tmp(:,:,2),img_rgb(:,:,2)).^2 ...
                 +normxcorr2(tmp(:,:,3),img_rgb(:,:,3)).^2)/sqrt(3);
    for kk = 1:m*n
        aa = ceil(kk/m)-1;
        bb = mod(kk-1,m);
        part = x_corr(round((h-1)/2+y+bb*h+1:(h-1)/2+y+(bb+1)*h),round((w-1)/2+x+aa*w+1:(w-1)/2+x+(aa+1)*w));
        if k~=kk    % 同一块比较没有意义
            corr_mat(k,kk) = max(part(:));
        end
        if any(part(:)>minpeakheight)
            matching{kk}(end+1) = k;
        end
    end
    blocks{b+1,a+1} = tmp;
end
corr_mat = (corr_mat+corr_mat')/2;  % 由于算法的不对称性，结果的对称性稍微破缺
corr_mat = tril(corr_mat);          % 再次平均以后仅使用下三角部分
[~,index] = sort(corr_mat(:),'descend');
index10 = index(1:10);    % 截取前十个
index_i = mod(index10-1,m*n)+1;   % 转为二维坐标
index_j = ceil(index10/(m*n));
for k = 1:10
    subplot(2,5,k);
    handle = imshow([blocks{index_i(k)};blocks{index_j(k)}]);
    title(sprintf('r=%.4f',corr_mat(index_i(k),index_j(k))));
end

% 第四小问，最相似但不是正确匹配的十块
figure;
count = 0;
result = zeros(m,n);
matches = [];
for k = 1:m*n
    if result(k)==0
        if any(result(matching{k})) % 是否已经有匹配?
            result(matching{k}) = max(result(matching{k}));
        else
            count = count+1;
            result(matching{k}) = count;
        end
    else
        result(matching{k}) = result(k);
    end
end
index1 = mod(index-1,m*n)+1;
index2 = ceil(index/(m*n));
i1 = mod(index1-1,m)+1;
j1 = ceil(index1/m);
i2 = mod(index2-1,m)+1;
j2 = ceil(index2/m);
selected = zeros(1,10);
count = 0;
for k = 1:length(index)
    if result(i1(k),j1(k))~=result(i2(k),j2(k))
        count = count+1;
        selected(count) = index(k);
    end
    if count == 10
        break;
    end
end
index1 = mod(selected-1,m*n)+1;   % 转为二维坐标
index2 = ceil(selected/(m*n));
for k = 1:10
    subplot(2,5,k);
    imshow([blocks{index1(k)};blocks{index2(k)}]);
    title(sprintf('r=%.4f',corr_mat(index1(k),index2(k))));
end

% 第五小问
figure;
for k = 1:m*n
    subplot(m,n,k);
    a = mod(k-1,n);     % 左侧已经有a个
    b = ceil(k/n)-1;    % 上边已经有b个
    imshow(img_rgb(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w),:));
    title(sprintf('%d',result(b+1,a+1)));
end

% 第六小问
figure;
addpath(strcat(pwd,'\linkgame'));
steps = omg(result);    % 调用之前的函数计算步骤
img_now = img_rgb;
% 录制视频
video_obj=VideoWriter(video_out,'MPEG-4');
open(video_obj);

for k = 1:steps(1)
    img_last = img_now;
    b = steps(4*k-2)-1;
    a = steps(4*k-1)-1;
    img_now(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w),:) = 0;
    b = steps(4*k)-1;
    a = steps(4*k+1)-1;
    img_now(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w),:) = 0;
    imshow(img_now);
    current_frame=getframe;
    for kk = 1:15   % 帧率30fps
        writeVideo(video_obj,current_frame);
    end
    pause(0.5);
    imshow(img_last);
    current_frame=getframe;
    for kk = 1:15   % 帧率30fps
        writeVideo(video_obj,current_frame);
    end
    pause(0.5);
    imshow(img_now);
    current_frame=getframe;
    for kk = 1:15   % 帧率30fps
        writeVideo(video_obj,current_frame);
    end
    pause(0.5);
end
close(video_obj);