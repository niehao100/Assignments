close all;clear all;clc;

files = dir('Faces/*.bmp'); % 只读取bmp文件，忽略'.'和'..'
filenum = length(files);    % 文件个数固定不变，避免反复计算
faces = cell(filenum,1);    % 用cell存不同大小的图片
for k = 1:filenum
    faces{k} = imread(['Faces/',files(k).name]);    % 读入
end

for L = 3:5;
    u = zeros(filenum,8^L);
    for k = 1:filenum
        face = uint32(floor(double(faces{k})/256*(2^L)));   % 对RGB空间进行缩放
        n = bitsll(face(:,:,1),2*L)+bitsll(face(:,:,2),L)+face(:,:,3);  % 映射
        stat = histc(n(:),0:8^L-1);
        u(k,:) = stat/sum(stat);
    end
    v = mean(u);
    figure;
    bar(0:8^L-1,v,'histc');
    xlim([0 8^L-1]);
    if L==3
        v3 = v;
    elseif L==4
        v4 = v;
    else
        v5 = v;
    end
end
save face v3 v4 v5;