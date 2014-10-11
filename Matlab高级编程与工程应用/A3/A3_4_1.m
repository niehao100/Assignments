close all;clear all;clc;

files = dir('Faces/*.bmp'); % ֻ��ȡbmp�ļ�������'.'��'..'
filenum = length(files);    % �ļ������̶����䣬���ⷴ������
faces = cell(filenum,1);    % ��cell�治ͬ��С��ͼƬ
for k = 1:filenum
    faces{k} = imread(['Faces/',files(k).name]);    % ����
end

for L = 3:5;
    u = zeros(filenum,8^L);
    for k = 1:filenum
        face = uint32(floor(double(faces{k})/256*(2^L)));   % ��RGB�ռ��������
        n = bitsll(face(:,:,1),2*L)+bitsll(face(:,:,2),L)+face(:,:,3);  % ӳ��
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