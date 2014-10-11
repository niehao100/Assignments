close all;clear all;clc;

load('guitar.mat');
tmp = abs(fft(realwave));   % ��Ƶ����
[max_frequency,max_index] = sort(tmp(1:ceil(length(realwave)/2)),'descend');    % ��Ƶ���������
max_index = max_index-ones(size(max_index));    % �±����
threshold = max_frequency(1)*0.2;   % �趨���뿼���ķ�����ֵ�����������ֵ��Ϊ��г��
base_frequency = max_index(1);  % ��ʼʱ��Ϊ���������ǻ�Ƶ
for k=1:length(max_frequency)
    if(max_frequency(k)<threshold)
        break;
    end
    base_frequency = gcd(base_frequency,max_index(k));  % ��Ƶȡ����г�������Լ��
end
original_frequency = fft(resample(realwave,base_frequency,1));  % �Ի�Ƶ�������ṩƵ��ֱ��ʣ�������Ҷ�任
w = [0:length(original_frequency)-1]';
w = mod(w,base_frequency)==0;
processed_frequency = w.*original_frequency;    % ȥ����г������
processed_wave = resample(ifft(processed_frequency),1,base_frequency);  % ���ʱ�򣬽�������ԭ���Ĳ�����

% �۲�Ч��
figure;
subplot(2,2,1);
plot(angle(fft(realwave))); % ԭ�ź���Ƶ����
subplot(2,2,3);
plot(angle(fft(wave2proc)));    % ����ź���Ƶ����
hold on;
plot(angle(fft(processed_wave)),'g');   % �ҵõ����ź���Ƶ���ԣ�������źŷǳ��õ��غ�
subplot(2,2,2);
plot(abs(fft(realwave)));   % ��Ƶ���ԣ���׸��
subplot(2,2,4);
plot(abs(fft(wave2proc)));
hold on;
plot(abs(fft(processed_wave)),'g');