delta_z=0.3;
delta_t=0.5*delta_z/299792458;

mu=4*pi()/10e7;
epsilon=1/299792458^2/mu;

E=zeros(1,101);
H=zeros(1,100);

E(31)=exp(-(((0-30)/15)^2));

n=270;

for i=1:n
    for k=1:100
        H(k)=H(k)-delta_t/mu/delta_z*(E(k+1)-E(k));
    end
    for k=2:100
        E(k)=E(k)-delta_t/epsilon/delta_z*(H(k)-H(k-1));
    end
    E(31)=E(31)+exp(-(((i-30)/15)^2));
    plot(E);
    axis([0 110 -2 2]);
    getframe();
    if(i==60)
        E60=E;
        H60=H;
    elseif(i==150)
        E150=E;
    elseif(i==270)
        E270=E;
    end
end
figure;
plot(E60);
axis([0 110 -2 2]);
figure;
plot(H60);
axis([0 110 -.05 .05]);
figure;
plot(E150);
axis([0 110 -2 2]);
figure;
plot(E270);
axis([0 110 -2 2]);

E=zeros(1,101);
H=zeros(1,100);

E(31)=exp(-(((0-30)/15)^2));

n=300;

for i=1:n
    for k=1:100
        H(k)=H(k)-delta_t/mu/delta_z*(E(k+1)-E(k));
    end
    for k=2:59
        E(k)=E(k)-delta_t/epsilon/delta_z*(H(k)-H(k-1));
    end
    for k=60:100
        E(k)=E(k)-delta_t/epsilon/delta_z*(H(k)-H(k-1))/4;
    end
    E(31)=E(31)+exp(-(((i-30)/15)^2));
    plot(E);
    axis([0 110 -2 2]);
    getframe();
    if(i==180)
        E180=E;
    elseif(i==300)
        E300=E;
    end
end
figure;
plot(E180);
axis([0 110 -2 2]);
figure;
plot(E300);
axis([0 110 -2 2]);