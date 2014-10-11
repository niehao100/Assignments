function v = zigzag(A)
    [m,n] = size(A);
    if m==1 || n==1
        v = A;
        return;
    end
    v = zeros(m*n,1);
    i = 1;
    j = 1;
    up = true;
    for k=1:m*n
        v(k) = A(i,j);
        if up
            if j==n     % 到最后一列往回走
                i = i+1;
                up = ~up; 
            else
                if i==1 % 到第一行往回走
                    j = j+1;
                    up = ~up;
                else
                    i = i-1;
                    j = j+1;
                end
            end
        else
            if i==m
                j = j+1;
                up = ~up;
            else
                if j==1
                    i = i+1;
                    up = ~up;
                else
                    i = i+1;
                    j = j-1;
                end
            end
        end
    end
end