function steps = cal(mtx)
    % -------------- 输入参数说明 --------------
    
    %   输入参数中，mtx为图像块的矩阵，类似这样的格式：
    %   [ 1 2 3;
    %     0 2 1;
    %     3 0 0 ]
    %   相同的数字代表相同的图案，0代表此处没有块。
    %   可以用[m, n] = size(mtx)获取行数和列数。
    
    % --------------- 输出参数说明 --------------- %
    
    %   要求最后得出的操作步骤放在steps数组里,格式如下：
    %   steps(1)表示步骤数。
    %   之后每四个数x1 y1 x2 y2，代表把mtx(x1,y1)与mtx(x2,y2)表示的块相连。
    %   示例： steps = [2, 1, 1, 1, 2, 2, 1, 3, 1];
    %   表示一共有两步，第一步把mtx(1,1)和mtx(1,2)表示的块相连，
    %   第二步把mtx(2,1)和mtx(3,1)表示的块相连。
    
    %% --------------  请在下面加入你的代码 O(∩_∩)O~  ------------
    
    steps = [];
    while true
        [x1, y1, x2, y2] = next_step(mtx);
        if all([x1 y1 x2 y2])
            steps = [steps,x1,y1,x2,y2];
            mtx(x1,y1) = 0;
            mtx(x2,y2) = 0;
        else
            steps = [length(steps)/4,steps];
            return;
        end
    end
end

function [x1, y1, x2, y2] = next_step(mtx)
    if ~any(any(mtx))
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
        return;
    end
    [m, n] = size(mtx);
    remains = unique(mtx);
    if remains(1)==0
        remains = remains(2:end);
    end
    for k = randperm(length(remains))
        positions = find(remains(k)==mtx);
        % 遍历所有可能
        actions = combntns(positions,2)';
        for action = actions
            pos1 = action(1);
            pos2 = action(2);
            y1 = ceil(pos1/m);
            x1 = pos1-(y1-1)*m;
            y2 = ceil(pos2/m);
            x2 = pos2-(y2-1)*m;
            if detect(mtx,x1,y1,x2,y2)
                return;
            end
        end
    end
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
end