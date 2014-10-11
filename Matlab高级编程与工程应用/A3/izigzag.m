function A = izigzag(v,m,n)
    if nargin==1
        m = round(sqrt(length(v)));
        n = m;
    end
    if nargin==2
        n = m(2);
        m = m(1);
    end
    A = zeros(m,n);
    i = 1;
    j = 1;
    up = true;
    for k=1:m*n
        A(i,j) = v(k);
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