function img = imghide0(carrier,msg)
    msglength = length(msg);                % msgӦΪlogical�Ͷ���������
    msg = [dec2bin(msglength,32)=='1',msg]; % ʹ��32λ����������Ϣ��λ��
    imgvec = carrier(:)';
    imgvec = [bitset(imgvec(1:msglength+32),1,msg),imgvec(msglength+33:end)];
    img = reshape(imgvec,size(carrier));
end