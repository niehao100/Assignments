function result=GenerateToneWithHarmonic(frequency,time,FS)
    amplitudes=[1,0.2,0.3]; % 谐波，可以自适应长度和方向
    result=zeros(1,floor(time*FS)+1);
    for i=[1:length(amplitudes)]
        result=result+amplitudes(i)*sin(double([0:time*FS])*2*pi*frequency*i/FS);
    end
    result=result/sum(amplitudes);  % 归一化
end