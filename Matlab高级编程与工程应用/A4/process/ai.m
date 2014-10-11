function step = ai(realcapture)   
    % --------- �������˵��  -------- %
    
    %   realcapture������ͷ�����ͼ�񣨾��󣩣������ʽ��rgb��ycbcr��Ҷ�
    %   �����user_camera�����ķ���ֵ��Ҳ��realcapture������
 
    % --------- �������˵��  -------- %
    
    %   ������Ĳ�������step������,��ʽ���£�
    %   ����ǰ���޷��ҵ����������Ŀ飬��step = -1
    %   ����step�����ĸ����������(step(1), step(2))�루step(3), step(4)��λ�õĿ�����
    %   ʾ���� step = [1 1 1 2];  
    %   ��ʾ��ǰ����Ϊ���±�Ϊ(1,1)��(1,2)�Ŀ�����
    
    %   ע���±�(a, b)����Ϸͼ���ж�Ӧ���������½�Ϊԭ�㽨��ֱ������ϵ��
    %   x�᷽���a����y�᷽���b���Ŀ�
    
    %% --------------  �������������Ĵ��� ------------ %
    img = rgb2gray(realcapture);    % Ϊ����������ɫ��Ϣ��ʵ�����ҵ��㷨Ҳ����ɫ��������
    disp('Start.');
    persistent steps;
    persistent now;
    persistent result;
    persistent m;
    if isempty(steps)
        disp('Calculating.');
        [M,N] = size(img);
        rows = mean(img,2);
        cols = mean(img)';
        rows = rows-mean(rows);
        cols = cols-mean(cols);


        K = 1000;
        [~,o,FT,~] = prefourier([0,N],N,[0,pi],K);
        col_f = FT*cols;
        [~,m] = max(abs(col_f(10:end)));
        m = m+9;
        w = 2*pi/(o(m))
        col_p = angle(col_f(m));

        [~,o,FT,~] = prefourier([0,M],M,[0,pi],K);
        row_f = FT*rows;
        [~,n] = max(abs(row_f(10:end)));
        n = n+9;
        h = 2*pi/(o(n))
        row_p = angle(row_f(n));

        m = floor(M/h)
        n = floor(N/w)
        y = abs((row_p/pi/2)*h);
        x = abs((col_p/pi/2)*w);
        blocks = cell(m,n);
        matching = cell(m,n);
        for k = 1:m*n
            a = ceil(k/m)-1;    % ����Ѿ���a��
            b = mod(k-1,m);     % �ϱ��Ѿ���b��
            tmp = im2double(img(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w)));
%             figure(2);
%             imshow(tmp);
            x_corr = normxcorr2(tmp,img);
                minpeakheight = 0.85;
                binary = x_corr>minpeakheight;
                for kk = 1:m*n
                    aa = ceil(kk/m)-1;
                    bb = mod(kk-1,m);
                    part = binary(round((h-1)/2+y+bb*h+1:(h-1)/2+y+(bb+1)*h),round((w-1)/2+x+aa*w+1:(w-1)/2+x+(aa+1)*w));
                    if any(any(part))
                        matching{kk}(end+1) = k;
                    end
                end
            blocks{b+1,a+1} = tmp;
        end
        count = 0;
        result = zeros(m,n);
        matches = [];
        for k = 1:m*n
            if result(k)==0
                if any(result(matching{k})) % �Ƿ��Ѿ���ƥ��?
                    result(matching{k}) = max(result(matching{k}));
                else
                    count = count+1;
                    result(matching{k}) = count;
                end
            else
                result(matching{k}) = result(k);
            end
        end
        result
        steps = cal(result);
        steps(1)
        now = 1;
% % %         [M,N] = size(img)
% % %         rows = mean(img,2);
% % %         cols = mean(img)';
% % %         rows = rows-mean(rows);
% % %         cols = cols-mean(cols);
% % % 
% % % 
% % %         K = 1024;
% % %         [~,omg,FT,~] = prefourier([0,N],N,[0,pi],K);
% % %         col_f = FT*cols;
% % %         [~,m] = max(abs(col_f(10:end)));
% % %         m = m+9;
% % %         w = 2*pi/(omg(m))
% % %         col_p = angle(col_f(m));
% % % 
% % %         [~,omg,FT,~] = prefourier([0,M],M,[0,pi],K);
% % %         row_f = FT*rows;
% % %         [~,n] = max(abs(row_f(10:end)));
% % %         n = n+9;
% % %         h = 2*pi/(omg(n))
% % %         row_p = angle(row_f(n));
% % % 
% % %         m = round(M/h)
% % %         n = round(N/w)
% % %         x = abs((row_p/pi/2)*h)
% % %         y = abs((col_p/pi/2)*w)
% % %         data = {m,n,x,y,h,w};
% % %     end
% % %     [M,N] = size(img);
% % % %     m = 7;
% % % %     n = 12;
% % % %     x = 10;
% % % %     y = 10;
% % % %     h = (M-2*y)/m;
% % % %     w = (N-2*x)/n;
% % %     m = data{1};
% % %     n = data{2};
% % %     x = data{3};
% % %     y = data{4};
% % %     h = data{5};
% % %     w = data{6};
% % %     
% % %     for k = randperm(m*n)
% % %         a = ceil(k/m)-1;
% % %         b = mod(k-1,m);
% % %         block = img(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w));
% % %         x_corr = normxcorr2(block,img);
% % %         corr_mat = zeros(m,n);
% % %         for kk = 1:m*n
% % %             aa = ceil(kk/m)-1;
% % %             bb = mod(kk-1,m);
% % %             
% % %             
% % %             
% % % %         subplot(1,2,1);
% % % %         imshow(block);
% % % %             subplot(1,2,2);
% % % %             imshow(img(round(y+bb*h+1:y+(bb+1)*h),round(x+aa*w+1:x+(aa+1)*w)));
% % % %             pause;
% % %             
% % %             
% % %             
% % %             corr_mat(kk) = max(max(x_corr(round((h-1)/2+bb*h+1:(h-1)/2+(bb+1)*h),round((w-1)/2+aa*w+1:(w-1)/2+(aa+1)*w))));
% % %             if corr_mat(kk)>0.8 && kk~=k
% % %                 step(2) = ceil(k/m);
% % %                 step(1) = m-mod(k-1,m);
% % %                 step(4) = ceil(kk/m);
% % %                 step(3) = m-mod(kk-1,m);
% % %                 step
% % %                 return;
% % %                 
% % %             end
% % %         end
    end
    if now>steps(1)
        disp('Finished.');
        step = -1;
        return;
    end
    astep = steps(4*now-2:4*now+1);
    step(1) = astep(2);
    step(2) = m+1-astep(1);
    step(3) = astep(4);
    step(4) = m+1-astep(3);
    
    now = now+1;
end
