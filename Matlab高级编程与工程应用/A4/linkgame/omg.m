function steps = omg(mtx)
    % -------------- �������˵�� --------------
    
    %   ��������У�mtxΪͼ���ľ������������ĸ�ʽ��
    %   [ 1 2 3;
    %     0 2 1;
    %     3 0 0 ]
    %   ��ͬ�����ִ�����ͬ��ͼ����0����˴�û�п顣
    %   ������[m, n] = size(mtx)��ȡ������������
    
    % --------------- �������˵�� --------------- %
    
    %   Ҫ�����ó��Ĳ����������steps������,��ʽ���£�
    %   steps(1)��ʾ��������
    %   ֮��ÿ�ĸ���x1 y1 x2 y2�������mtx(x1,y1)��mtx(x2,y2)��ʾ�Ŀ�������
    %   ʾ���� steps = [2, 1, 1, 1, 2, 2, 1, 3, 1];
    %   ��ʾһ������������һ����mtx(1,1)��mtx(1,2)��ʾ�Ŀ�������
    %   �ڶ�����mtx(2,1)��mtx(3,1)��ʾ�Ŀ�������
    
    %% --------------  �������������Ĵ��� O(��_��)O~  ------------
    
    [m, n] = size(mtx);
    steps = [];
    while true
        [x1 y1 x2 y2] = next_step(mtx);
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

function [x1 y1 x2 y2] = next_step(mtx)
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
        % �������п���
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