close all;clear all;clc;

load hall hall_gray;
load JpegCoeff QTAB;
[m,n] = size(hall_gray);
img = [hall_gray,repmat(hall_gray(:,n),1,mod(-n,8))];
img = [img;repmat(img(m,:),mod(-m,8),1)];
M = m+mod(-m,8);
N = n+mod(-n,8);
M = round(M/8);
N = round(N/8);
blocks = zeros(8,8*M*N);
for k = 1:M
    blocks(:,8*N*(k-1)+1:8*N*k) = img(8*k-7:8*k,:);
end
coefficients = zeros(64,M*N);
for k = 1:M*N
    coefficients(:,k) = zigzag(round(dct2(blocks(:,8*k-7:8*k)-128*ones(8,8))./QTAB));
end
coefficients
