x_min=0;
x_max=100;
y_min=0;
y_max=50;
delta=.5;
epsilon=1e-3;
X=x_min:delta:x_max;
Y=y_min:delta:y_max;
X_lenth=(x_max-x_min)/delta+1;
Y_lenth=(y_max-y_min)/delta+1;
Phi=zeros(X_lenth,Y_lenth);

Phi(:,end)=ones(X_lenth,1)*10;  %y=y_max

while (true)
    temp=Phi;
    done=false;
    for j=2:Y_lenth-1
        parfor i=2:X_lenth-1
            temp(i,j)=(Phi(i-1,j)+Phi(i+1,j)+Phi(i,j-1)+Phi(i,j+1))/4;
        end
    end
    if norm(temp-Phi,Inf)<epsilon
        break
    end
    Phi=temp;
end
figure;
contour(X,Y,Phi');
axis equal;
xlim([x_min,x_max]);
ylim([y_min,y_max]);
figure;
mesh(X,Y,Phi');
axis equal;
xlim([x_min,x_max]);
ylim([y_min,y_max]);