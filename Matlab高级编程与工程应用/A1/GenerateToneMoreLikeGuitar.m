function result=GenerateToneMoreLikeGuitar(frequency,time,FS)
% 根据频率的不同添加不同的谐波
    A0=220;
    Bb0=A0*2^(1/12);
    B0=Bb0*2^(1/12);
    C0=B0*2^(1/12);
    Db0=C0*2^(1/12);
    D0=Db0*2^(1/12);
    Eb0=D0*2^(1/12);
    E0=Eb0*2^(1/12);
    F0=E0*2^(1/12);
    Gb0=F0*2^(1/12);
    G0=Gb0*2^(1/12);
    Ab1=G0*2^(1/12);
    A1=440;
    Bb1=A1*2^(1/12);
    B1=Bb1*2^(1/12);
    C1=B1*2^(1/12);
    Db1=C1*2^(1/12);
    D1=Db1*2^(1/12);
    Eb1=D1*2^(1/12);
    E1=Eb1*2^(1/12);
    F1=E1*2^(1/12);
    Gb1=F1*2^(1/12);
    G1=Gb1*2^(1/12);
    Ab2=G1*2^(1/12);
    
    amplitudes=[6.64560949698900; 9.65694007225628; 6.32285176625552; 7.29083938719962; 0; 0; 2.33048268216879];  % 默认的谐波，来自题给短信号
    result=zeros(1,floor(time*FS)+1);
    if(abs(frequency-C1)<1)
        amplitudes = [698.8;286.4;281.1;57.84;166.6;50.06;53.15;15.2;21.06];  % 信息来自9中手工对得到的幅频特性进行分析拷贝
    elseif(abs(frequency-D1)<1||abs(frequency-D0)<1)
        amplitudes = [1109;898;176.8;45.82;43.43;153.4;35.07;30.64;40.63;44.54;10.02];
    elseif(abs(frequency-G0)<1)
        amplitudes = [338.1;439;177.8;128.6;32.19;53.06;35;24.72];
    elseif(abs(frequency-F0)<1)
        amplitudes = [146.8;81.36;27.18;17.98;7.76];
    end
    for i=[1:length(amplitudes)]
        result=result+amplitudes(i)*sin(double([0:time*FS])*2*pi*frequency*i/FS);
    end
    result=result/sum(amplitudes);
end