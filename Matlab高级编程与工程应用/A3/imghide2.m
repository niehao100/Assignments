function [dcbin,acbin] = imghide2(img,DCTAB,ACTAB,QTAB,msg)
    [m,n] = size(img);
    img = [img,repmat(img(:,n),1,mod(-n,8))];   % 补齐为8的整数倍
    img = [img;repmat(img(m,:),mod(-m,8),1)];
    M = m+mod(-m,8);
    N = n+mod(-n,8);
    M = round(M/8);
    N = round(N/8);
    L = M*N;
    blocks = zeros(8,8*L);
    for k = 1:M
        blocks(:,8*N*(k-1)+1:8*N*k) = img(8*k-7:8*k,:); % 分块
    end
    coefficients = zeros(64,L);
    for k = 1:L
        coefficients(:,k) = ... % 获得量化系数
            zigzag(round(dct2(blocks(:,8*k-7:8*k)-128*ones(8,8))./QTAB));
    end
    % 插入隐藏信息
    step = 2;
    coeffnonzeros = find(coefficients>1 | coefficients<0);
    coeffnonzeros = coeffnonzeros(1:step:end);
    msglength = min(length(msg),length(coeffnonzeros)-32-mod(length(coeffnonzeros),8));
    msg = [dec2bin(msglength,32)=='1',msg];
    count = 1;
    for k = coeffnonzeros'
        coefficients(k) = double(bitset(int16(coefficients(k)),1,msg(count)));
        if count==length(msg)
            break;
        end
        count = count+1;
    end
    
    dc = coefficients(1,:);
    dcdiff = [2*dc(1),dc(1:end-1)]-dc;  % 差分
    dcbin = logical([]);
    acbin = logical([]);
    for k = 1:L
        dccategory = ceil(log2(abs(dcdiff(k))+1))+1;
        if dcdiff(k)==0 % 0不需要编码magnitude
            dcbin = [dcbin,logical(DCTAB(dccategory,2:1+DCTAB(dccategory,1)))];
        else
            if dcdiff(k)<0  % 如果待编码内容为负，则编入1补码
                magnitude = dec2bin(-dcdiff(k))=='0';
            else
                magnitude = dec2bin(dcdiff(k))=='1';
            end
            dcbin = [dcbin,logical(DCTAB(dccategory,2:1+DCTAB(dccategory,1))),...
                magnitude];
        end

        accoefficients = coefficients(2:64,k)';
        acnonzeros = find(accoefficients);  % 只关心非零系数，这可以提高效率
        last_nonzero = 1;
        for acnonzero = acnonzeros
            acrun = acnonzero - last_nonzero;
            last_nonzero = acnonzero+1;
            category = ceil(log2(abs(accoefficients(acnonzero))+1));
            while acrun>15  % 必要时插入ZRL
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
        if last_nonzero~=64 % 必要时插入EOB
            acbin = [acbin,'1010'=='1'];
        end
    end
end