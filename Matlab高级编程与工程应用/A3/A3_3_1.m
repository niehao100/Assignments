close all;clear all;clc;

msgfid = fopen('msg.txt','r');
msg = fread(msgfid,inf,'ubit1=>logical')';
fclose(msgfid);

load hall hall_gray;
load jpegCoeff
img = imghide0(hall_gray,msg);
msglength = length(msg);
imshow(img);
[dcbin,acbin] = jpegencode(img,DCTAB,ACTAB,QTAB);
[m,n] = size(hall_gray);
jpeg = jpegdecode(dcbin,acbin,m,n,DCTAB,ACTAB,QTAB);
msg0 = imgreveal0(img);
msg1 = imgreveal0(jpeg);
msg1 = msg1(1:msglength);

error0 = length(find(msg-msg0));
msg0 = reshape(msg0,8,msglength/8)';
msgtxt0 = zeros(1,msglength);
for k = 1:msglength/8
    msgtxt0(k) = sum(2.^[0:7].*msg0(k,:));
end
fprintf('空域隐藏后提取结果:\n\n\t%s\n\n出错位数: %d (占%.2f%%).\n\n',...
    msgtxt0,error0,error0/msglength*100);

error1 = length(find(msg-msg1));
msg1 = reshape(msg1,8,msglength/8)';
msgtxt1 = zeros(1,msglength);
for k = 1:msglength/8
    msgtxt1(k) = sum(2.^[0:7].*msg1(k,:));
end
fprintf('空域隐藏并经过JPEG编解码后提取结果:\n\n\t%s\n\n出错位数: %d (占%.2f%%).\n\n',...
    msgtxt1,error1,error1/msglength*100);