close all;clear all;clc;

[wave,FS]=audioread('fmt.wav');
beat = 0.25;    % 这个变量用于后面确定节拍持续时间
% 高斯低通滤波，代码参考StackOverFlow
sigma = 200;    % 滤波器参数为粗略估计以后经过调试确定的值
filter_size = 2000;
x = linspace(-filter_size / 2, filter_size / 2, filter_size);
gaussFilter = exp(-x .^ 2 / (2 * sigma ^ 2));   % 高斯型
gaussFilter = gaussFilter / sum (gaussFilter); % 归一化
envelope = conv(abs(wave),gaussFilter,'same');  % 利用conv函数的same模式生成没有相移的信号
subplot(2,1,1); % 观看包络效果
plot(abs(wave)/max(abs(wave)));
hold on;
plot(1:length(envelope),envelope/max(abs(envelope)),'g','LineWidth',1.5);   % 加粗便于看清

[peaks,indexes] = findpeaks(abs(envelope),'minpeakdistance',1500);	% 寻找包络中的峰值，将信号分段
hold on;
stem(indexes,peaks/max(peaks),'r'); % 绘制到图形上
tones = zeros(length(indexes)+1,1);
tones(1) = AnalyseTone(wave(1:indexes(1)-1),FS);
beats = zeros(length(indexes)+1,1);
beats(1) = round((indexes(1)-1)/FS/beat);
% 这些变量用于确定各个频率的谐波，算法本身不需要
C1_harmonics = zeros(FS/2,1);
D1_harmonics = zeros(FS/2,1);
G0_harmonics = zeros(FS/2,1);
F0_harmonics = zeros(FS/2,1);
D0_harmonics = zeros(FS/2,1);

for k = 1:length(indexes)-1 % 分段分析信号
    [tones(k+1),harmonics] = AnalyseTone(wave(indexes(k):indexes(k+1)-1),FS);   % 分析频率和谐波
    beats(k+1) = round((indexes(k+1)-indexes(k))/FS/beat);  % 记录时长
    % 根据需要记录谐波分量
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
tones(end) = AnalyseTone(wave(indexes(end):end),FS);    % 最后一段单独处理
beats(end) = round((length(wave)-indexes(end))/FS/beat);
figure(1);  % 观看每一段的频率和时长，每个数据点表示其前一个数据点到该点的信息
subplot(2,1,2);
stem([indexes(1:end);length(wave)],tones,'g');
hold on;
ha_1 = gca;
pos = get(ha_1,'Position');
ha_2 = axes('Position',pos); 
stem([indexes(1:end);length(wave)],beats,'r'); 
set(ha_2,'YAxisLocation','right','Color','none');   % 由于尺度相差较大，设定两个坐标轴
tones'  % 输出信息到控制台
beats'