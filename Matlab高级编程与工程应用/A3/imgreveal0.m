function msg = imgreveal0(carrier)
    imgvec = carrier(:)';
    msglength = imgvec(1:32);
    msglength = bitget(msglength,1);
    msglength = min(sum(2.^[31:-1:0].*double(msglength)),length(imgvec)-32);
    msg = imgvec(33:32+msglength);
    msg = logical(bitget(msg,1));
end