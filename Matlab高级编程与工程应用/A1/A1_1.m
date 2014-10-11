close all;clear all;clc;

A0=220; % A0定为220Hz，以其作为基准
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

% 《东方红》是F大调，1=F
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

% 《东方红》是2/4拍，每分钟120拍
beat=0.5;
% 采样率8000Hz
FS=8000;
% 生成给定频率、时长和采样率的信号
do0=GenerateTone(do0_frequency,beat,FS);
re0=GenerateTone(re0_frequency,beat,FS);
mi0=GenerateTone(mi0_frequency,beat,FS);
fa0=GenerateTone(fa0_frequency,beat,FS);
so0=GenerateTone(so0_frequency,beat,FS);
la0=GenerateTone(la0_frequency,beat,FS);
si0=GenerateTone(si0_frequency,beat,FS);
do1=GenerateTone(do1_frequency,beat,FS);
% 先播放音阶，然后空一拍，再播放乐曲
sound([do0,re0,mi0,fa0,so0,la0,si0,do1,zeros(1,FS*beat),...
    GenerateTone(so0_frequency,beat,FS),...
    GenerateTone(so0_frequency,beat/2,FS),...
    GenerateTone(la0_frequency,beat/2,FS),...
    GenerateTone(re0_frequency,beat*2,FS),...
    GenerateTone(do0_frequency,beat,FS),...
    GenerateTone(do0_frequency,beat/2,FS),...
    GenerateTone(la_1_frequency,beat/2,FS),...
    GenerateTone(re0_frequency,beat*2,FS)],FS);