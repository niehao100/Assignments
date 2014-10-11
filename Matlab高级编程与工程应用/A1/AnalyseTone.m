function [base_frequency,harmonics] = AnalyseTone(wave,FS)
    realwave = wave/max(abs(wave)); % ��һ��
    frequency = abs(fft(realwave)); % ��Ƶ����

    slice = length(wave);   % ��Ƭ�źų���
    % ���ܵ�Ƶ��
    possiable_frequency = [184.997211355817,195.997717990875,207.652348789973,220,233.081880759045,246.941650628062,261.625565300599,277.182630976872,293.664767917408,311.126983722081,329.627556912870,349.228231433004,369.994422711634,391.995435981749,415.304697579945,440];

    % Ԥ������˹��ͨ�˲��õ����磬���ð����һ��

    sigma = slice/50;
    filter_size = slice/5;
    x = linspace(-filter_size / 2, filter_size / 2, filter_size);
    gaussFilter = exp(-x .^ 2 / (2 * sigma ^ 2));
    gaussFilter = gaussFilter / sum (gaussFilter);
    envelope = conv(abs(wave),gaussFilter,'same');
    envelope = envelope/max(envelope);
    % ����ע�͵��Ĳ����ǹۿ������Ԥ����Ч��
    % figure;
    % subplot(2,1,1);
    % plot(realwave);
    % hold on;
    % plot(envelope);
    realwave = realwave./envelope;
    realwave = realwave/max(abs(realwave));
    % �Դ������źŽ���ƽ��
    sigma = 5;
    filter_size = 50;
    x = linspace(-filter_size / 2, filter_size / 2, filter_size);
    gaussFilter = exp(-x .^ 2 / (2 * sigma ^ 2));
    gaussFilter = gaussFilter / sum (gaussFilter);
    realwave = conv(realwave,gaussFilter,'same');
    realwave = realwave/max(abs(realwave));

    % subplot(2,1,2);
    % plot(realwave);
    % �����������Ļ�Ƶг����Ϊ���
    energy = 0;
    base_frequency = 0;
    for k = possiable_frequency
        index = round(k/FS*slice+1:k/FS*slice:slice/2);
        new_energy = norm(frequency(index))^2;
        if(new_energy>energy)
            energy = new_energy;
            base_frequency = k;
        end
    end
    base_frequency = round(base_frequency/FS*slice);

    original_frequency = fft(resample(realwave,round(base_frequency),1));   % ���������Ƶ��ֱ����Ժ�FFT
    w = [0:length(original_frequency)-1]';
    w = mod(w,base_frequency)==0;   % �˵���г������
    base_frequency = 2^(round(log2(base_frequency*FS/slice/220)*12)/12)*220;    % �����Ƶ���Ϊ�����ļ�������ֵ
    harmonics = resample(frequency(1:ceil(slice/2)),FS/2,ceil(slice/2));    % ���г��
end