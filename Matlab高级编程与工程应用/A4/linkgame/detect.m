function bool = detect(mtx, x1, y1, x2, y2)
    % ========================== 参数说明 ==========================
    
    % 输入参数中，mtx为图像块的矩阵，类似这样的格式：
    % [ 1 2 3;
    %   0 2 1;
    %   3 0 0 ]
    % 相同的数字代表相同的图案，0代表此处没有块。
    % 可以用[m, n] = size(mtx)获取行数和列数。
    % (x1, y1)与（x2, y2）为需判断的两块的下标，即判断mtx(x1, y1)与mtx(x2, y2)
    % 是否可以消去。
    
    % 输出参数bool = 1表示可以消去，bool = 0表示不能消去。
    
    %% 在下面添加你的代码O(∩_∩)O
    
    [m, n] = size(mtx);
    if mtx(x1,y1)~=mtx(x2,y2)
        bool = false;
        return;
    end
    
    % 第一种可能，直接相连
    bool = direct(mtx,x1,y1,x2,y2);
    if bool == true
        return;
    end
    % 第二种可能，拐一个弯相连
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
    % 第三种可能，拐两个弯相连
    % 扩展图形区域，以便包括所有可能
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