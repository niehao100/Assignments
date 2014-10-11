function [img, msg] = imgreveal2(dcbin,acbin,m,n,DCTAB,ACTAB,QTAB)
    dcdictsize = size(DCTAB);
    dcdictsize = dcdictsize(1);
    dcdictsizes = zeros(1,dcdictsize);
    dcdict = {};                        % 字典按照码流长度组织，有若干cell
    for k = 1:dcdictsize                % 同一长度的码字组成一个cell数组
        thissize = DCTAB(k,1);          % 每个码字为一个cell
        if thissize<=length(dcdict)     % {1}为值，{2}为码
            newdict = dcdict{thissize};
        else
            newdict = {};
        end
        newdict{end+1} = { k-1,logical(DCTAB(k,2:1+thissize))};
        dcdict{thissize} = newdict;
    end
    acdictsize = size(ACTAB);
    acdictsize = acdictsize(1);
    acdictsizes = zeros(1,acdictsize);
    acdict = {};
    for k = 1:acdictsize
        thissize = ACTAB(k,3);
        if thissize<=length(acdict)
            newdict = acdict{thissize};
        else
            newdict = {};
        end
        newdict{end+1} = {ACTAB(k,1:2),logical(ACTAB(k,4:3+thissize))};
        acdict{thissize} = newdict;
    end
    % EOB和ZRL没有在ACTAB中给出
    newdict = acdict{4};
    newdict{end+1} = {[0 0],'1010'=='1'};
    acdict{4} = newdict;
    newdict = acdict{11};
    newdict{end+1} = {[15 0],'11111111001'=='1'};
    acdict{11} = newdict;
    
    dccoefficients = [];
    k = 1;
    while(k <= length(dcbin))   % 这里解码的写法是参照huffmandeco函数写的
        tempcode = dcbin(k); 
        dccode = isvalid(tempcode,dcdict);
        while(isempty(dccode) && k < length(dcbin))
            k = k+1;
            tempcode = [tempcode, dcbin(k)];
            dccode = isvalid(tempcode,dcdict);
        end
        if dccode==0
            magnitude = 0;
        else
            magnitude = dcbin(k+1:k+dccode);
        end
        if magnitude(1)==1 || dccode==0 % 正数首位是1
            dccoefficients(end+1) = sum(2.^[length(magnitude)-1:-1:0].*magnitude);
        else    % 负数首位是0
            dccoefficients(end+1) = -sum(2.^[length(magnitude)-1:-1:0].*(~magnitude));
        end
        k = k+dccode+1;
    end
    blocksize = length(dccoefficients);     % 至此已经知道块数了
    for k = 2:blocksize     % 反差分
        dccoefficients(k) = dccoefficients(k-1)-dccoefficients(k);
    end
    coefficients = [dccoefficients;zeros(63,blocksize)];
    seek = 1;   % 标志系数矩阵的列数
    offset = 2; % 标志系数矩阵的行数
    k=1;        % 标志码流位置
    while(k <= length(acbin))
        tempcode = acbin(k); 
        accode = isvalid(tempcode,acdict);
        while(isempty(accode) && k < length(acbin))
            k = k+1;
            tempcode = [tempcode, acbin(k)];
            accode = isvalid(tempcode,acdict);
        end
        if accode(2)==0 % 处理特殊码字
            if accode(1)==0 % EOB
                seek = seek+1;
                offset = 2;
                k = k+1;
                continue;
            else    % ZRL
                offset = offset+16;
                k = k+1;
                continue;
            end
        end
        magnitude = acbin(k+1:k+accode(2));
        if magnitude(1)==1  % 将二进制转为十进制，这种算法避免了二次转换
            coefficients(offset+accode(1),seek) = sum(2.^[length(magnitude)-1:-1:0].*magnitude);
        else
            coefficients(offset+accode(1),seek) = -sum(2.^[length(magnitude)-1:-1:0].*(~magnitude));
        end
        if offset+accode(1)+1>64
            seek = seek+1;
            offset = 2;
        else
            offset = offset+accode(1)+1;
        end
        k = k+accode(2)+1;
    end
    % 恢复隐藏信息
    step = 2;
    coeffnonzeros = find(coefficients>1 | coefficients<0);
    coeffnonzeros = coeffnonzeros(1:2:end);
    msglength = false(1,32);
    count = 1;
    for k = coeffnonzeros(1:32)'
        msglength(count) = bitget(int16(coefficients(k)),1);
        count = count+1;
    end
    msglength = sum(2.^[31:-1:0].*double(msglength));
    msg = false(1,msglength);
    count = 1;
    for k = coeffnonzeros(33:32+msglength)'
        msg(count) = bitget(int16(coefficients(k)),1);
        count = count+1;
    end
    
    M = double(m+mod(-m,8));
    N = double(n+mod(-n,8));
    img = zeros(M,N);
    N = N/8;
    for k = 1:blocksize     % 恢复
        x = ceil(k/N);
        y = N-mod(-k,N);
        img(8*x-7:8*x,8*y-7:8*y) = idct2(izigzag(coefficients(:,k),8,8).*QTAB)+128*ones(8,8);
    end
    img = uint8(img(1:m,1:n));
end

function code = isvalid(stream,dict)    % 参照了huffmandeco函数内子函数的写法
    dict = dict{length(stream)};
    code = [];
    for k = 1:length(dict)
        if isequal(stream,dict{1,k}{2})
            code = dict{1,k}{1};
            return;
        end
    end
end