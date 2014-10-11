close all;clear all;clc;

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

la_1_frequency=D0;
si_1_frequency=E0;
do0_frequency=F0;
re0_frequency=G0;
mi0_frequency=A1;
fa0_frequency=Bb1;
so0_frequency=C1;
la0_frequency=D1;
si0_frequency=E1;
do1_frequency=F1;

beat=0.5;
FS=8000;

rise_time=1/9;
set_time=1/18;
disappear_time=1/6;
% 利用更多信息生成谐波，详见GenerateToneMoreLikeGuitar函数
tones={...
    AddDecay(GenerateToneMoreLikeGuitar(so0_frequency,beat,FS),...
    rise_time, set_time,disappear_time),...
    AddDecay(GenerateToneMoreLikeGuitar(so0_frequency,beat/2,FS),...
    rise_time, set_time,disappear_time),...
    AddDecay(GenerateToneMoreLikeGuitar(la0_frequency,beat/2,FS),...
rise_time, set_time,disappear_time),...
    AddDecay(GenerateToneMoreLikeGuitar(re0_frequency,beat*2,FS),...
rise_time, set_time,disappear_time),...
    AddDecay(GenerateToneMoreLikeGuitar(do0_frequency,beat,FS),...
rise_time, set_time,disappear_time),...
    AddDecay(GenerateToneMoreLikeGuitar(do0_frequency,beat/2,FS),...
rise_time, set_time,disappear_time),...
    AddDecay(GenerateToneMoreLikeGuitar(la_1_frequency,beat/2,FS),...
rise_time,set_time,disappear_time),...
    AddDecay(GenerateToneMoreLikeGuitar(re0_frequency,beat*2,FS),...
rise_time,set_time, disappear_time)};
sound(ConcatenateTones(tones,FS*beat/16),FS);