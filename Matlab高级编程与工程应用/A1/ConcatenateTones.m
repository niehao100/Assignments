function result=ConcatenateTones(tones,overlap_time)
% ����tones�и����źţ�����ʱ��Ϊoverlap_time
    overlap_time=int64(overlap_time);
    if(length(tones)>2) % �ݹ�
        first=ConcatenateTones(tones(1:int64(length(tones)/2)),overlap_time);
        second=ConcatenateTones(tones(int64(length(tones)/2)+1:end),overlap_time);
        result=ConcatenateTones({first,second},overlap_time);
    elseif(length(tones)==2)
        first=tones{1};
        second=tones{2};
        result=[first,zeros(1,length(second)-overlap_time)];
        result=result+[zeros(1,length(first)-overlap_time),second]; % ֱ�Ӵ�һ����Ȼ�����
    else
        result=tones{1};
    end
end