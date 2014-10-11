function result=AddDecay(tone,rise_percent,set_percent,disappear_percent)
% Ϊ��Ƶ�ź���Ӱ���
% toneΪ�������Ƶ�ź�
% rise_percentΪ��������ʱ��ռ�õİٷֱ�
% set_percentΪ�½�ʱ��ռ�õİٷֱ�
% disappear_percentΪ��ʧʱ��ռ�õİٷֱ�
    rise_time=floor(length(tone)*rise_percent); % �����������ֵĳ���
    set_time=floor(length(tone)*set_percent);   % ����˥�����ֵĳ���
    disappear_time=floor(length(tone)*disappear_percent);   % ������ʧ���ֵĳ���
    rise_amplitude=expm1(0.5*linspace(0,7.22442272,rise_time)); % ���������İ��磬����ʹ��ָ���Ͱ���
    rise_amplitude=rise_amplitude/max(rise_amplitude);  % ��һ��
    last_time=length(tone)-rise_time-disappear_time;    % ����ʱ��Ϊʣ���ʱ��
    set_amplitude=exp(...   % ˥�����ֵİ��磬��Ϊָ����
        -linspace(-2.77557728,2.77557728...
        /double(set_time)*double(last_time)-1,last_time))+20;
    set_amplitude=set_amplitude/max(set_amplitude); % ��һ
    disappear_amplitude=expm1(-0.5*linspace(-6.0890449,0,disappear_time));  % ��ʧ����
    disappear_amplitude=disappear_amplitude/max(disappear_amplitude)... % ָ����
        *set_amplitude(end);
    result=[rise_amplitude,set_amplitude,disappear_amplitude].*tone;    % ��Ȩ
    result=result/norm(result)*norm(tone);  % �����źŵķ�������
end