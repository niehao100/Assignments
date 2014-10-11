function result=AddDecay(tone,rise_percent,set_percent,disappear_percent)
% 为音频信号添加包络
% tone为输入的音频信号
% rise_percent为包络上升时间占用的百分比
% set_percent为下降时间占用的百分比
% disappear_percent为消失时间占用的百分比
    rise_time=floor(length(tone)*rise_percent); % 计算上升部分的长度
    set_time=floor(length(tone)*set_percent);   % 计算衰减部分的长度
    disappear_time=floor(length(tone)*disappear_percent);   % 计算消失部分的长度
    rise_amplitude=expm1(0.5*linspace(0,7.22442272,rise_time)); % 计算上升的包络，这里使用指数型包络
    rise_amplitude=rise_amplitude/max(rise_amplitude);  % 归一化
    last_time=length(tone)-rise_time-disappear_time;    % 持续时间为剩余的时间
    set_amplitude=exp(...   % 衰减部分的包络，仍为指数型
        -linspace(-2.77557728,2.77557728...
        /double(set_time)*double(last_time)-1,last_time))+20;
    set_amplitude=set_amplitude/max(set_amplitude); % 归一
    disappear_amplitude=expm1(-0.5*linspace(-6.0890449,0,disappear_time));  % 消失部分
    disappear_amplitude=disappear_amplitude/max(disappear_amplitude)... % 指数型
        *set_amplitude(end);
    result=[rise_amplitude,set_amplitude,disappear_amplitude].*tone;    % 加权
    result=result/norm(result)*norm(tone);  % 保持信号的范数不变
end