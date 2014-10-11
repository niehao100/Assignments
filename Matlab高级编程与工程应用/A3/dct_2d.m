function B = dct_2d(A,M,N)
    if nargin>=3    % 最多可以读入三个参数
        [m_A,n_A] = size(A);
        if M<=m_A
            A=A(1:M,:);
        else
            A=[A;zeros(M-m_A,n_A)];
        end
        if N<=n_A
            A=A(:,1:N);
        else
            A=[A,zeros(M,N-n_A)];
        end
    else if nargin==2
        B = dct_2d(A,M(1),M(2));
        return;
        else
            [M,N] = size(A);
        end
    end
    D = cos([0:M-1]'*[1:2:2*M]*pi/M/2);
    D(1,:) = D(1,:)/sqrt(2);
    Dt = cos([1:2:2*N]'*[0:N-1]*pi/N/2);
    Dt(:,1) = Dt(:,1)/sqrt(2);
    B = D*double(A)*Dt*2/sqrt(M*N);
end