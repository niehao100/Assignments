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

% �ڶ�С�ʣ��ֿ�
figure;
for k = 1:m*n
    subplot(m,n,k);
    a = mod(k-1,n);     % ����Ѿ���a��
    b = ceil(k/n)-1;    % �ϱ��Ѿ���b��
    imshow(img_rgb(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w),:));
end

% ����С�ʣ������Ƶ�ʮ��
figure;
blocks = cell(m,n);
matching = cell(m,n);
corr_mat = zeros(m*n,m*n);
minpeakheight = 0.77;
for k = 1:m*n
    a = ceil(k/m)-1;    % ����Ѿ���a��
    b = mod(k-1,m);     % �ϱ��Ѿ���b��
    tmp = im2double(img_rgb(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w),:));
    x_corr = sqrt(normxcorr2(tmp(:,:,1),img_rgb(:,:,1)).^2 ...
                 +normxcorr2(tmp(:,:,2),img_rgb(:,:,2)).^2 ...
                 +normxcorr2(tmp(:,:,3),img_rgb(:,:,3)).^2)/sqrt(3);
    for kk = 1:m*n
        aa = ceil(kk/m)-1;
        bb = mod(kk-1,m);
        part = x_corr(round((h-1)/2+y+bb*h+1:(h-1)/2+y+(bb+1)*h),round((w-1)/2+x+aa*w+1:(w-1)/2+x+(aa+1)*w));
        if k~=kk    % ͬһ��Ƚ�û������
            corr_mat(k,kk) = max(part(:));
        end
        if any(part(:)>minpeakheight)
            matching{kk}(end+1) = k;
        end
    end
    blocks{b+1,a+1} = tmp;
end
corr_mat = (corr_mat+corr_mat')/2;  % �����㷨�Ĳ��Գ��ԣ�����ĶԳ�����΢��ȱ
corr_mat = tril(corr_mat);          % �ٴ�ƽ���Ժ��ʹ�������ǲ���
[~,index] = sort(corr_mat(:),'descend');
index10 = index(1:10);    % ��ȡǰʮ��
index_i = mod(index10-1,m*n)+1;   % תΪ��ά����
index_j = ceil(index10/(m*n));
for k = 1:10
    subplot(2,5,k);
    handle = imshow([blocks{index_i(k)};blocks{index_j(k)}]);
    title(sprintf('r=%.4f',corr_mat(index_i(k),index_j(k))));
end

% ����С�ʣ������Ƶ�������ȷƥ���ʮ��
figure;
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
index1 = mod(selected-1,m*n)+1;   % תΪ��ά����
index2 = ceil(selected/(m*n));
for k = 1:10
    subplot(2,5,k);
    imshow([blocks{index1(k)};blocks{index2(k)}]);
    title(sprintf('r=%.4f',corr_mat(index1(k),index2(k))));
end

% ����С��
figure;
for k = 1:m*n
    subplot(m,n,k);
    a = mod(k-1,n);     % ����Ѿ���a��
    b = ceil(k/n)-1;    % �ϱ��Ѿ���b��
    imshow(img_rgb(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w),:));
    title(sprintf('%d',result(b+1,a+1)));
end

% ����С��
figure;
addpath(strcat(pwd,'\linkgame'));
steps = omg(result);    % ����֮ǰ�ĺ������㲽��
img_now = img_rgb;
% ¼����Ƶ
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