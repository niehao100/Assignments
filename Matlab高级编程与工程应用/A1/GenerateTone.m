function result=GenerateTone(frequency,time,FS)
    result=sin(double([0:time*FS])*2*pi*frequency/FS);
end