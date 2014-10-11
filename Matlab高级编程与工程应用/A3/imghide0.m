function img = imghide0(carrier,msg)
    msglength = length(msg);                % msg应为logical型二进制码流
    msg = [dec2bin(msglength,32)=='1',msg]; % 使用32位储存隐藏信息的位数
    imgvec = carrier(:)';
    imgvec = [bitset(imgvec(1:msglength+32),1,msg),imgvec(msglength+33:end)];
    img = reshape(imgvec,size(carrier));
end