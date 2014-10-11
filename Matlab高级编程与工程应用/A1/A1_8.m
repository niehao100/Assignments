close all;clear all;clc;

FS=8000;
% ǰ���㷨�Ѿ��������������ظ�
load('guitar.mat');
tmp = abs(fft(wave2proc));
[max_frequency,max_index] = sort(tmp(1:ceil(length(wave2proc)/2)),'descend');
max_index = max_index-ones(size(max_index));
threshold = max_frequency(1)*0.2;
base_frequency = max_index(1);
for k=1:length(max_frequency)
    if(max_frequency(k)<threshold)
        break;
    end
    base_frequency = gcd(base_frequency,max_index(k));
end
% �������ڽ�ֹʹ��resample����Ϊʱ���ظ�ʵ��Ƶ��ֱ��ʵ�����
original_frequency = fft([realwave;realwave;realwave;realwave;realwave;realwave;realwave;realwave;realwave;realwave]);
w = [0:length(original_frequency)-1]';
w = mod(w,base_frequency)==0;
processed_frequency = w.*original_frequency;
processed_wave = ifft(processed_frequency);
processed_frequency = abs(fft(processed_wave));
processed_frequency = processed_frequency(101:100:ceil(length(processed_frequency)/2))';    % ��ȡ��Ƶ��
processed_frequency = processed_frequency/max(processed_frequency)  %��ʾг��������̨
stem(processed_frequency);
base_frequency = base_frequency*FS/length(wave2proc)    % ���ʵ��Ƶ��