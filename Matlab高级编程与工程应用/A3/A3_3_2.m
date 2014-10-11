close all;clear all;clc;

msgfid = fopen('msg.txt','r');
txt = fread(msgfid,inf,'ubit1=>logical')';
fclose(msgfid);

load hall hall_gray;
load jpegCoeff

[dcbin,acbin] = imghide1(hall_gray,DCTAB,ACTAB,QTAB,txt);
[m,n] = size(hall_gray);
[img,msg] = imgreveal1(dcbin,acbin,m,n,DCTAB,ACTAB,QTAB);
msglength = length(msg);
figure;
imshow(img);
error = length(find(msg-txt(1:msglength)));
msg = reshape(msg,8,msglength/8)';
msgtxt = zeros(1,msglength);
for k = 1:msglength/8
    msgtxt(k) = sum(2.^[0:7].*msg(k,:));
end
rate = m*n*8/(length(dcbin)+length(acbin)+32);
MSE = sum(sum((img-hall_gray).^2))/m/n;
PSNR = 10*log10(255*255/MSE);
fprintf('方法一提取结果:\n\n\t%s\n\n压缩率 %.4f; PSNR %.2f.\n\n',...
    msgtxt,rate,PSNR);

[dcbin,acbin] = imghide2(hall_gray,DCTAB,ACTAB,QTAB,txt);
[m,n] = size(hall_gray);
[img,msg] = imgreveal2(dcbin,acbin,m,n,DCTAB,ACTAB,QTAB);
msglength = length(msg);
figure;
imshow(img);
error = length(find(msg-txt(1:msglength)));
msg = reshape(msg,8,msglength/8)';
msgtxt = zeros(1,msglength);
for k = 1:msglength/8
    msgtxt(k) = sum(2.^[0:7].*msg(k,:));
end
rate = m*n*8/(length(dcbin)+length(acbin)+32);
MSE = sum(sum((img-hall_gray).^2))/m/n;
PSNR = 10*log10(255*255/MSE);
fprintf('方法二提取结果:\n\n\t%s\n\n压缩率 %.4f; PSNR %.2f.\n\n',...
    msgtxt,rate,PSNR);

[dcbin,acbin] = imghide3(hall_gray,DCTAB,ACTAB,QTAB,txt);
[m,n] = size(hall_gray);
[img,msg] = imgreveal3(dcbin,acbin,m,n,DCTAB,ACTAB,QTAB);
msglength = length(msg);
figure;
imshow(img);
error = length(find(msg-txt(1:msglength)));
msg = reshape(msg,8,msglength/8)';
msgtxt = zeros(1,msglength);
for k = 1:msglength/8
    msgtxt(k) = sum(2.^[0:7].*msg(k,:));
end
rate = m*n*8/(length(dcbin)+length(acbin)+32);
MSE = sum(sum((img-hall_gray).^2))/m/n;
PSNR = 10*log10(255*255/MSE);
fprintf('方法三提取结果:\n\n\t%s\n\n压缩率 %.4f; PSNR %.2f.\n\n',...
    msgtxt,rate,PSNR);
