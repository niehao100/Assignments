function speechproc()
    close all;clear all;clc;
    % 定义常数
    FS = 8000;
    FL = 80;                % 帧长
    WL = 240;               % 窗长
    P = 10;                 % 预测系数个数
    s = readspeech('voice.pcm',100000);             % 载入语音s
    L = length(s);          % 读入语音长度
    FN = floor(L/FL)-2;     % 计算帧数
    % 预测和重建滤波器
    exc = zeros(L,1);       % 激励信号（预测误差）
    zi_pre = zeros(P,1);    % 预测滤波器的状态
    s_rec = zeros(L,1);     % 重建语音
    zi_rec = zeros(P,1);    % 重建滤波器的状态
    % 合成滤波器
    exc_syn = zeros(L,1);   % 合成的激励信号（脉冲串）
    s_syn = zeros(L,1);     % 合成语音
    zi_syn = zeros(P,1);    % 合成滤波器的状态
    % 变调不变速滤波器
    exc_syn_t = zeros(L,1);     % 合成的激励信号（脉冲串）
    s_syn_t = zeros(L,1);       % 合成语音
    zi_syn_t = zeros(P,1);      % 合成滤波器的状态
    % 变速不变调滤波器（假设速度减慢一倍）
    exc_syn_v = zeros(2*L,1);   % 合成的激励信号（脉冲串）
    s_syn_v = zeros(2*L,1);     % 合成语音
    zi_syn_v = zeros(P,1);      % 合成滤波器的状态

    hw = hamming(WL);       % 汉明窗
    
    last = 2*FL;                % 记录上个脉冲的位置
    last_v = 2*2*FL;
    last_t = 2*FL;
    exc_syn(2*FL) = 1;          % 设定初始脉冲位置
    exc_syn_v(2*2*FL) = 1;      % 由于初始两帧被丢弃，直接从第三帧开始
    exc_syn_t(2*FL) = 1;
    
    % 依次处理每帧语音
    for n = 3:FN

        % 计算预测系数（不需要掌握）
        s_w = s(n*FL-WL+1:n*FL).*hw;    %汉明窗加权后的语音
        [A,E] = lpc(s_w, P);            %用线性预测法计算P个预测系数
                                        % A是预测系数，E会被用来计算合成激励的能量

        if n == 27
        % (3) 在此位置写程序，观察预测系统的零极点图
            zplane(1,A);
        end
        
        s_f = s((n-1)*FL+1:n*FL);       % 本帧语音，下面就要对它做处理

        % (4) 在此位置写程序，用filter函数s_f计算激励，注意保持滤波器状态
        [exc((n-1)*FL+1:n*FL),zi_pre] = filter (A,1,s_f,zi_pre);
        
        % exc((n-1)*FL+1:n*FL) = ... 将你计算得到的激励写在这里

        % (5) 在此位置写程序，用filter函数和exc重建语音，注意保持滤波器状态
        [s_rec((n-1)*FL+1:n*FL),zi_rec] = filter(1,A,exc((n-1)*FL+1:n*FL),zi_rec);
        
        % s_rec((n-1)*FL+1:n*FL) = ... 将你计算得到的重建语音写在这里

        % 注意下面只有在得到exc后才会计算正确
        s_Pitch = exc(n*FL-222:n*FL);
        PT = findpitch(s_Pitch);    % 计算基音周期PT（不要求掌握）
        G = sqrt(E*PT);           % 计算合成激励的能量G（不要求掌握）

        
        % (10) 在此位置写程序，生成合成激励，并用激励和filter函数产生合成语音
        for k = (n-1)*FL+1:n*FL
            if k-last>=PT
                exc_syn(k) = G;
                last = k;
            end
        end
        [s_syn((n-1)*FL+1:n*FL),zi_syn] = filter(1,A,exc_syn((n-1)*FL+1:n*FL),zi_syn);
        
        % exc_syn((n-1)*FL+1:n*FL) = ... 将你计算得到的合成激励写在这里
        % s_syn((n-1)*FL+1:n*FL) = ...   将你计算得到的合成语音写在这里

        % (11) 不改变基音周期和预测系数，将合成激励的长度增加一倍，再作为filter
        % 的输入得到新的合成语音，听一听是不是速度变慢了，但音调没有变。
        for k = (n-1)*FL*2+1:n*FL*2
            if k-last_v>=PT
                exc_syn_v(k) = G;
                last_v = k;
            end
        end
        [s_syn_v((n-1)*2*FL+1:n*2*FL),zi_syn_v] = filter(1,A,exc_syn_v((n-1)*2*FL+1:n*2*FL),zi_syn_v);
        
        % exc_syn_v((n-1)*FL_v+1:n*FL_v) = ... 将你计算得到的加长合成激励写在这里
        % s_syn_v((n-1)*FL_v+1:n*FL_v) = ...   将你计算得到的加长合成语音写在这里
        
        % (13) 将基音周期减小一半，将共振峰频率增加150Hz，重新合成语音，听听是啥感受～
        poles = roots(A);
        for k=1:length(poles)
            if isreal(k)    % 实极点不用处理，他们不提供谐振峰
                continue;
            end
            if(angle(poles(1))>0)   % 根据极点位置，增加或减少幅角
                poles(k) = abs(poles(k))*exp((150*2*pi/FS+angle(poles(k)))*1j);
            else
                poles(k) = abs(poles(k))*exp((-150*2*pi/FS+angle(poles(k)))*1j);
            end
        end
        A_t = poly(poles);  % 变调滤波器系数
        
        for k = (n-1)*FL+1:n*FL
            if k-last_t>=PT/2
                exc_syn_t(k) = G;
                last_t = k;
            end
        end
        [s_syn_t((n-1)*FL+1:n*FL),zi_syn_t] = filter(1,A_t,exc_syn_t((n-1)*FL+1:n*FL),zi_syn_t);
        
        % exc_syn_t((n-1)*FL+1:n*FL) = ... 将你计算得到的变调合成激励写在这里
        % s_syn_t((n-1)*FL+1:n*FL) = ...   将你计算得到的变调合成语音写在这里
        
    end

    % (6) 在此位置写程序，听一听 s ，exc 和 s_rec 有何区别，解释这种区别
    % 后面听语音的题目也都可以在这里写，不再做特别注明
    sound([exc;s;s_rec;s_syn;s_syn_v;s_syn_t],FS);
    
    figure;
    subplot(3,1,1);
    plot(exc);
    subplot(3,1,2);
    plot(s);
    subplot(3,1,3);
    plot(s_rec);
    figure;
    subplot(3,1,1);
    plot(exc(5000:6000));
    subplot(3,1,2);
    plot(s(5000:6000));
    subplot(3,1,3);
    plot(s_rec(5000:6000));
    norm(s-s_rec)/norm(s)   % 重建信号整体误差
    norm(s(5000:6000)-s_rec(5000:6000))/norm(s(5000:6000))  % 截取部分误差

    % 保存所有文件
    writespeech('exc.pcm',exc);
    writespeech('rec.pcm',s_rec);
    writespeech('exc_syn.pcm',exc_syn);
    writespeech('syn.pcm',s_syn);
    writespeech('exc_syn_t.pcm',exc_syn_t);
    writespeech('syn_t.pcm',s_syn_t);
    writespeech('exc_syn_v.pcm',exc_syn_v);
    writespeech('syn_v.pcm',s_syn_v);
return

% 从PCM文件中读入语音
function s = readspeech(filename, L)
    fid = fopen(filename, 'r');
    s = fread(fid, L, 'int16');
    fclose(fid);
return

% 写语音到PCM文件中
function writespeech(filename,s)
    fid = fopen(filename,'w');
    fwrite(fid, s, 'int16');
    fclose(fid);
return

% 计算一段语音的基音周期，不要求掌握
function PT = findpitch(s)
[B, A] = butter(5, 700/4000);
s = filter(B,A,s);
R = zeros(143,1);
for k=1:143
    R(k) = s(144:223)'*s(144-k:223-k);
end
[R1,T1] = max(R(80:143));
T1 = T1 + 79;
R1 = R1/(norm(s(144-T1:223-T1))+1);
[R2,T2] = max(R(40:79));
T2 = T2 + 39;
R2 = R2/(norm(s(144-T2:223-T2))+1);
[R3,T3] = max(R(20:39));
T3 = T3 + 19;
R3 = R3/(norm(s(144-T3:223-T3))+1);
Top = T1;
Rop = R1;
if R2 >= 0.85*Rop
    Rop = R2;
    Top = T2;
end
if R3 > 0.85*Rop
    Rop = R3;
    Top = T3;
end
PT = Top;
return