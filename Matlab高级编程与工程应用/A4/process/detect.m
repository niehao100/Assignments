function bool = detect(mtx, x1, y1, x2, y2)
    % ========================== ����˵�� ==========================
    
    % ��������У�mtxΪͼ���ľ������������ĸ�ʽ��
    % [ 1 2 3;
    %   0 2 1;
    %   3 0 0 ]
    % ��ͬ�����ִ�����ͬ��ͼ����0����˴�û�п顣
    % ������[m, n] = size(mtx)��ȡ������������
    % (x1, y1)�루x2, y2��Ϊ���жϵ�������±꣬���ж�mtx(x1, y1)��mtx(x2, y2)
    % �Ƿ������ȥ��
    
    % �������bool = 1��ʾ������ȥ��bool = 0��ʾ������ȥ��
    
    %% �����������Ĵ���O(��_��)O
    
    [m, n] = size(mtx);
    if mtx(x1,y1)~=mtx(x2,y2)
        bool = false;
        return;
    end
    
    % ��һ�ֿ��ܣ�ֱ������
    bool = direct(mtx,x1,y1,x2,y2);
    if bool == true
        return;
    end
    % �ڶ��ֿ��ܣ���һ��������
    if mtx(x1,y2)==0
        bool = direct(mtx,x1,y1,x1,y2) && direct(mtx,x2,y2,x1,y2);
        if bool == true
            return;
        end
    elseif mtx(x2,y1)==0
        bool = direct(mtx,x1,y1,x2,y1) && direct(mtx,x2,y2,x2,y1);
        if bool == true
            return;
        end
    end
    % �����ֿ��ܣ�������������
    % ��չͼ�������Ա�������п���
    mtx_ext = [zeros(m+2,1),[zeros(1,n);mtx;zeros(1,n)],zeros(m+2,1)];
    for x = 1:m+2
        if mtx_ext(x,y1+1)==0 && mtx_ext(x,y2+1)==0
            bool = direct(mtx_ext,x1+1,y1+1,x,y1+1) &&...
                direct(mtx_ext,x,y2+1,x,y1+1) &&...
                direct(mtx_ext,x,y2+1,x2+1,y2+1);
            if bool == true
                return;
            end
        end
    end
    for y = 1:n+2
        if mtx_ext(x1+1,y)==0 && mtx_ext(x2+1,y)==0
            bool = direct(mtx_ext,x1+1,y1+1,x1+1,y) &&...
                direct(mtx_ext,x2+1,y,x1+1,y) &&...
                direct(mtx_ext,x2+1,y,x2+1,y2+1);
            if bool == true
                return;
            end
        end
    end
end

function bool = direct(mtx,x1,y1,x2,y2)
    if x1==x2
        if y2<y1
            tmp = y1;
            y1 = y2;
            y2 = tmp;
        end
        if ~any(mtx(x1,y1+1:y2-1))
            bool = true;
            return;
        end
    elseif y1==y2
        if x2<x1
            tmp = x1;
            x1 = x2;
            x2 = tmp;
        end
        if ~any(mtx(x1+1:x2-1,y1))
            bool = true;
            return;
        end
    end
    bool = false;
end