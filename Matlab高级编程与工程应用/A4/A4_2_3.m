close all;clear all;clc;

img = imread('process/graycapture.jpg');
[M,N] = size(img);
rows = mean(img,2);
cols = mean(img)';
rows = rows-mean(rows);
cols = cols-mean(cols);


K = 1000;
[~,omg,FT,~] = prefourier([0,N],N,[0,pi],K);
col_f = FT*cols;
[~,m] = max(abs(col_f));
w = 2*pi/(omg(m));
col_p = angle(col_f(m));

[~,omg,FT,~] = prefourier([0,M],M,[0,pi],K);
row_f = FT*rows;
[~,n] = max(abs(row_f));
h = 2*pi/(omg(n));
row_p = angle(row_f(n));

m = floor(M/h);
n = floor(N/w);
x = abs((row_p/pi/2)*h);
y = abs((col_p/pi/2)*w);
blocks = cell(m,n);
matching = cell(m,n);
minpeakheight = 0.85;
corr_mat = zeros(m*n,m*n);
for k = 1:m*n
    a = ceil(k/m)-1;    % 左侧已经有a个
    b = mod(k-1,m);     % 上边已经有b个
    tmp = im2double(img(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w)));
    x_corr = normxcorr2(tmp,img);
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
index = index(1:10);    % 截取前十个
index_i = mod(index-1,m*n)+1;   % 转为二维坐标
index_j = ceil(index/(m*n));
for k = 1:10
    subplot(2,5,k);
    handle = imshow([blocks{index_i(k)};blocks{index_j(k)}]);
    title(sprintf('r=%.4f',corr_mat(index_i(k),index_j(k))));
end