function [img, msg] = imgreveal1(dcbin,acbin,m,n,DCTAB,ACTAB,QTAB)
    dcdictsize = size(DCTAB);
    dcdictsize = dcdictsize(1);
    dcdictsizes = zeros(1,dcdictsize);
    dcdict = {};                        % �ֵ䰴������������֯��������cell
    for k = 1:dcdictsize                % ͬһ���ȵ��������һ��cell����
        thissize = DCTAB(k,1);          % ÿ������Ϊһ��cell
        if thissize<=length(dcdict)     % {1}Ϊֵ��{2}Ϊ��
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
    % EOB��ZRLû����ACTAB�и���
    newdict = acdict{4};
    newdict{end+1} = {[0 0],'1010'=='1'};
    acdict{4} = newdict;
    newdict = acdict{11};
    newdict{end+1} = {[15 0],'11111111001'=='1'};
    acdict{11} = newdict;
    
    dccoefficients = [];
    k = 1;
    while(k <= length(dcbin))   % ��������д���ǲ���huffmandeco����д��
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
        if magnitude(1)==1 || dccode==0 % ������λ��1
            dccoefficients(end+1) = sum(2.^[length(magnitude)-1:-1:0].*magnitude);
        else    % ������λ��0
            dccoefficients(end+1) = -sum(2.^[length(magnitude)-1:-1:0].*(~magnitude));
        end
        k = k+dccode+1;
    end
    blocksize = length(dccoefficients);     % �����Ѿ�֪��������
    for k = 2:blocksize     % �����
        dccoefficients(k) = dccoefficients(k-1)-dccoefficients(k);
    end
    coefficients = [dccoefficients;zeros(63,blocksize)];
    seek = 1;   % ��־ϵ�����������
    offset = 2; % ��־ϵ�����������
    k=1;        % ��־����λ��
    while(k <= length(acbin))
        tempcode = acbin(k); 
        accode = isvalid(tempcode,acdict);
        while(isempty(accode) && k < length(acbin))
            k = k+1;
            tempcode = [tempcode, acbin(k)];
            accode = isvalid(tempcode,acdict);
        end
        if accode(2)==0 % ������������
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
        if magnitude(1)==1  % ��������תΪʮ���ƣ������㷨�����˶���ת��
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
    % �ָ�������Ϣ
    coeffnonzeros = find(coefficients>1 | coefficients<0);
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
    for k = 1:blocksize     % �ָ�
        x = ceil(k/N);
        y = N-mod(-k,N);
        img(8*x-7:8*x,8*y-7:8*y) = idct2(izigzag(coefficients(:,k),8,8).*QTAB)+128*ones(8,8);
    end
    img = uint8(img(1:m,1:n));
end

function code = isvalid(stream,dict)    % ������huffmandeco�������Ӻ�����д��
    dict = dict{length(stream)};
    code = [];
    for k = 1:length(dict)
        if isequal(stream,dict{1,k}{2})
            code = dict{1,k}{1};
            return;
        end
    end
end