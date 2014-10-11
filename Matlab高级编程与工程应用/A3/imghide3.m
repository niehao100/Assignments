function [dcbin,acbin] = imghide3(img,DCTAB,ACTAB,QTAB,msg)
    msglength = min(length(msg),8*floor(numel(img)/64/8-32));
    msg = [dec2bin(msglength,32)=='1',msg];
    [m,n] = size(img);
    img = [img,repmat(img(:,n),1,mod(-n,8))];   % ����Ϊ8��������
    img = [img;repmat(img(m,:),mod(-m,8),1)];
    M = m+mod(-m,8);
    N = n+mod(-n,8);
    M = round(M/8);
    N = round(N/8);
    L = M*N;
    blocks = zeros(8,8*L);
    for k = 1:M
        blocks(:,8*N*(k-1)+1:8*N*k) = img(8*k-7:8*k,:); % �ֿ�
    end
    coefficients = zeros(64,L);
    for k = 1:L
        coefficients(:,k) = ... % �������ϵ��
            zigzag(round(dct2(blocks(:,8*k-7:8*k)-128*ones(8,8))./QTAB));
    end
    dc = coefficients(1,:);
    dcdiff = [2*dc(1),dc(1:end-1)]-dc;  % ���
    dcbin = logical([]);
    acbin = logical([]);
    for k = 1:L
        dccategory = ceil(log2(abs(dcdiff(k))+1))+1;
        if dcdiff(k)==0 % 0����Ҫ����magnitude
            dcbin = [dcbin,logical(DCTAB(dccategory,2:1+DCTAB(dccategory,1)))];
        else
            if dcdiff(k)<0  % �������������Ϊ���������1����
                magnitude = dec2bin(-dcdiff(k))=='0';
            else
                magnitude = dec2bin(dcdiff(k))=='1';
            end
            dcbin = [dcbin,logical(DCTAB(dccategory,2:1+DCTAB(dccategory,1))),...
                magnitude];
        end

        accoefficients = coefficients(2:64,k)';
        acnonzeros = find(accoefficients);  % ֻ���ķ���ϵ������������Ч��
        if k<=length(msg)   % ����������Ϣ
            if isempty(acnonzeros)
                acnonzerosend = 0;
            else
                acnonzeroend = acnonzeros(end);
            end
            if acnonzeroend==63  % ���һ��ϵ������
                accoefficients(end) = -1+2*msg(k);
            else
                accoefficients(acnonzeroend+1) = -1+2*msg(k);
                acnonzeros(end+1) = acnonzeroend+1;
            end
        end
        last_nonzero = 1;
        for acnonzero = acnonzeros
            acrun = acnonzero - last_nonzero;
            last_nonzero = acnonzero+1;
            category = ceil(log2(abs(accoefficients(acnonzero))+1));
            while acrun>15  % ��Ҫʱ����ZRL
                acbin = [acbin,logical([1 1 1 1 1 1 1 1 0 0 1])];
                acrun = acrun-16;
            end
            acrun = logical(ACTAB(10*acrun+category,...
                4:3+ACTAB(10*acrun+category,3)));
            if accoefficients(acnonzero)<0;
                magnitude = dec2bin(-accoefficients(acnonzero))=='0';
            else
                magnitude = dec2bin(accoefficients(acnonzero))=='1';
            end
            acbin = [acbin,acrun,magnitude];
        end
        if last_nonzero~=64 % ��Ҫʱ����EOB
            acbin = [acbin,'1010'=='1'];
        end
    end
end