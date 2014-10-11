close all;clear all;clc;

[wave,FS]=audioread('fmt.wav');
beat = 0.25;    % ����������ں���ȷ�����ĳ���ʱ��
% ��˹��ͨ�˲�������ο�StackOverFlow
sigma = 200;    % �˲�������Ϊ���Թ����Ժ󾭹�����ȷ����ֵ
filter_size = 2000;
x = linspace(-filter_size / 2, filter_size / 2, filter_size);
gaussFilter = exp(-x .^ 2 / (2 * sigma ^ 2));   % ��˹��
gaussFilter = gaussFilter / sum (gaussFilter); % ��һ��
envelope = conv(abs(wave),gaussFilter,'same');  % ����conv������sameģʽ����û�����Ƶ��ź�
subplot(2,1,1); % �ۿ�����Ч��
plot(abs(wave)/max(abs(wave)));
hold on;
plot(1:length(envelope),envelope/max(abs(envelope)),'g','LineWidth',1.5);   % �Ӵֱ��ڿ���

[peaks,indexes] = findpeaks(abs(envelope),'minpeakdistance',1500);	% Ѱ�Ұ����еķ�ֵ�����źŷֶ�
hold on;
stem(indexes,peaks/max(peaks),'r'); % ���Ƶ�ͼ����
tones = zeros(length(indexes)+1,1);
tones(1) = AnalyseTone(wave(1:indexes(1)-1),FS);
beats = zeros(length(indexes)+1,1);
beats(1) = round((indexes(1)-1)/FS/beat);
% ��Щ��������ȷ������Ƶ�ʵ�г�����㷨������Ҫ
C1_harmonics = zeros(FS/2,1);
D1_harmonics = zeros(FS/2,1);
G0_harmonics = zeros(FS/2,1);
F0_harmonics = zeros(FS/2,1);
D0_harmonics = zeros(FS/2,1);

for k = 1:length(indexes)-1 % �ֶη����ź�
    [tones(k+1),harmonics] = AnalyseTone(wave(indexes(k):indexes(k+1)-1),FS);   % ����Ƶ�ʺ�г��
    beats(k+1) = round((indexes(k+1)-indexes(k))/FS/beat);  % ��¼ʱ��
    % ������Ҫ��¼г������
    if(abs(tones(k+1)-261.63)<1)
        C1_harmonics = C1_harmonics+harmonics;
    elseif(abs(tones(k+1)-293.66)<1)
        D1_harmonics = D1_harmonics+harmonics;
        D0_harmonics = D0_harmonics+harmonics;
    elseif(abs(tones(k+1)-196)<1)
        G0_harmonics = G0_harmonics+harmonics;
    elseif(abs(tones(k+1)-349.23)<1)
        F0_harmonics = F0_harmonics+harmonics;
    end
end
tones(end) = AnalyseTone(wave(indexes(end):end),FS);    % ���һ�ε�������
beats(end) = round((length(wave)-indexes(end))/FS/beat);
figure(1);  % �ۿ�ÿһ�ε�Ƶ�ʺ�ʱ����ÿ�����ݵ��ʾ��ǰһ�����ݵ㵽�õ����Ϣ
subplot(2,1,2);
stem([indexes(1:end);length(wave)],tones,'g');
hold on;
ha_1 = gca;
pos = get(ha_1,'Position');
ha_2 = axes('Position',pos); 
stem([indexes(1:end);length(wave)],beats,'r'); 
set(ha_2,'YAxisLocation','right','Color','none');   % ���ڳ߶����ϴ��趨����������
tones'  % �����Ϣ������̨
beats'