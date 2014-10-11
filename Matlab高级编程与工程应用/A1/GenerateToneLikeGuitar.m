function result=GenerateToneLikeGuitar(frequency,time,FS)
    % 改变谐波分布
    amplitudes=[6.64560949698900; 9.65694007225628; 6.32285176625552; 7.29083938719962; 0; 0; 2.33048268216879];
    result=zeros(1,floor(time*FS)+1);
    for i=[1:length(amplitudes)]
        result=result+amplitudes(i)*sin(double([0:time*FS])*2*pi*frequency*i/FS);
    end
    result=result/sum(amplitudes);
end