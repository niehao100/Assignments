close all;clear all;clc;

load mtx;

img = imread('process/graycapture.jpg');
% img = imread('process/graygroundtruth.jpg');
[M,N] = size(img);
rows = mean(img,2);
cols = mean(img)';
rows = rows-mean(rows);
cols = cols-mean(cols);


K = 1000;
[~,omg,FT,~] = prefourier([0,N],N,[0,pi],K);
col_f = FT*cols;
[~,m] = max(abs(col_f));
w = 2*pi/(omg(m));
col_p = angle(col_f(m));

[~,omg,FT,~] = prefourier([0,M],M,[0,pi],K);
row_f = FT*rows;
[~,n] = max(abs(row_f));
h = 2*pi/(omg(n));
row_p = angle(row_f(m));

m = floor(M/h);
n = floor(N/w);
x = abs((row_p/pi/2)*h);
y = abs((col_p/pi/2)*w);
blocks = cell(m,n);
flt = fspecial('log',7,0.35);
% flt = sinc((-10:10)/2);
% flt = flt'*flt;
% flt = flt/sum(sum(flt));
% flt = [-1,-1,-1;-1,8,-1;-1,-1,-1]/9;
% % % % tmp = filter2(flt,im2double(img));
% % % % imshow(tmp)
% minmin = min(min(tmp))
% maxmax = max(max(tmp))
% imshow((tmp-min(min(tmp)))/(maxmax-minmin));
% return
for k = 1:m*n
    a = mod(k-1,n);     % 左侧已经有a个
    b = ceil(k/n)-1;    % 上边已经有b个
    tmp = imfilter(im2double(img(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w))),flt);
%     subplot(m,n,k);
%     
%     
%     
% %     subplot(m,n,k);
% %     imshow(blocks{b+1,a+1});
%     
%     
% %     blocks{b+1,a+1} = im2double(img(round(y+b*h+1:y+(b+1)*h),round(x+a*w+1:x+(a+1)*w)));
%     tmp = blocks{b+1,a+1};
%     imshow(tmp-mean(mean(tmp))+0.5);
%     imshow(tmp);
    minmin = min(min(tmp));
    maxmax = max(max(tmp));
    tmp = (tmp-min(min(tmp)))/(maxmax-minmin);
    tmp = tmp-mean(mean(tmp))+0.5;
%     imshow(tmp);
    blocks{b+1,a+1} = tmp;
%     pause();
end
% h = butter(20,0.5,'high')
% tmp = filter2(h,im2double(img));
% tmp = tmp-min(min(tmp));
% return
result = zeros(m*n*(m*n-1)/2,4);
k = 1;
[h,w] = size(blocks{1});
for i = 1:m*n
    for j = i+1:m*n
        
%         x_corr = 0;
%         blocki = blocks{i};
%         blockj = blocks{j};
%         for a = 2:2*h-2
%             for b = 2:2*w-2
%                 block1 = blocki(max(h-a+1,1):min(h,2*h-a),max(w-b+1,1):min(w,2*w-b));
%                 block2 = blockj(max(h-a+1,1):min(h,2*h-a),max(w-b+1,1):min(w,2*w-b));
%                 new_xcorr = sum(sum(block1.*block2));
%                 if new_xcorr>x_corr
%                     x_corr = new_xcorr;
%                 end
%             end
%         end
        
        
        
        x_corr = xcorr2(blocks{i},blocks{j});
%         subplot(1,3,1);imshow(blocks{i});
%         subplot(1,3,2);imshow(blocks{j});
%         subplot(1,3,3);mesh(x_corr);
        x_corr = max(max(x_corr))/mean(mean(abs(x_corr)));


% %         getframe();
% % % %         if i==24 && j==65
% % % %             pause;
% % % %         end
% % % %         pause;
        result(k,:) = [x_corr;i;j;mtx(i)==mtx(j)];
        k = k+1;
    end
end
result = sortrows(result,1);
final_result = zeros(1,4);
for k = m*n*(m*n-1)/2:-1:1
    if ~any(final_result(:,2:3)==result(k,2))  % 检测是否已经有匹配
        if ~any(final_result(:,2:3)==result(k,3))
            final_result(end+1,:) = result(k,:);
        end
    end
end
final_result