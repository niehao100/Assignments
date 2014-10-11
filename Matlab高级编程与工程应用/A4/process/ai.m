function step = ai(realcapture)   
    % --------- 输入参数说明  -------- %
    
    %   realcapture是摄像头捕获的图像（矩阵），具体格式是rgb、ycbcr或灰度
    %   由你的user_camera函数的返回值（也叫realcapture）决定
 
    % --------- 输出参数说明  -------- %
    
    %   计算出的操作放在step数组里,格式如下：
    %   若当前已无法找到可以相连的块，则step = -1
    %   否则step里有四个数，代表把(step(1), step(2))与（step(3), step(4)）位置的块相连
    %   示例： step = [1 1 1 2];  
    %   表示当前步骤为把下标为(1,1)和(1,2)的块相连
    
    %   注意下标(a, b)在游戏图像中对应的是以左下角为原点建立直角坐标系，
    %   x轴方向第a个，y轴方向第b个的块
    
    %% --------------  请在下面加入你的代码 ------------ %
    img = rgb2gray(realcapture);    % 为性能牺牲颜色信息，实际上我的算法也对颜色并不依赖
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
            a = ceil(k/m)-1;    % 左侧已经有a个
            b = mod(k-1,m);     % 上边已经有b个
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
                if any(result(matching{k})) % 是否已经有匹配?
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
