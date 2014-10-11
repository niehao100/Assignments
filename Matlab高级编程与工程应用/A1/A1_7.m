close all;clear all;clc;

load('guitar.mat');
tmp = abs(fft(realwave));   % 幅频特性
[max_frequency,max_index] = sort(tmp(1:ceil(length(realwave)/2)),'descend');    % 将频域幅度排序
max_index = max_index-ones(size(max_index));    % 下标调整
threshold = max_frequency(1)*0.2;   % 设定纳入考量的幅度阈值，高于这个阈值认为是谐波
base_frequency = max_index(1);  % 初始时认为幅度最大的是基频
for k=1:length(max_frequency)
    if(max_frequency(k)<threshold)
        break;
    end
    base_frequency = gcd(base_frequency,max_index(k));  % 基频取各次谐波的最大公约数
end
original_frequency = fft(resample(realwave,base_frequency,1));  % 以基频升采样提供频域分辨率，做傅立叶变换
w = [0:length(original_frequency)-1]';
w = mod(w,base_frequency)==0;
processed_frequency = w.*original_frequency;    % 去掉非谐波分量
processed_wave = resample(ifft(processed_frequency),1,base_frequency);  % 变回时域，降采样回原来的采样率

% 观察效果
figure;
subplot(2,2,1);
plot(angle(fft(realwave))); % 原信号相频特性
subplot(2,2,3);
plot(angle(fft(wave2proc)));    % 题给信号相频特性
hold on;
plot(angle(fft(processed_wave)),'g');   % 我得到的信号相频特性，与题给信号非常好地重合
subplot(2,2,2);
plot(abs(fft(realwave)));   % 幅频特性，不赘述
subplot(2,2,4);
plot(abs(fft(wave2proc)));
hold on;
plot(abs(fft(processed_wave)),'g');