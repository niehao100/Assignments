#include<cmath>
#include<cstdio>
using namespace std;
double Problem1(double x1,double x2,\
    const double p1,const double p2,const double p3,const double p4,\
    double* x1_result,double* x2_result);
double Problem2(double x1,double x2,\
    const double a,const double b,const double c,const double d,\
    double* x1_result,double* x2_result);
double Problem3(double x1,double x2,double x3,\
    const double h1,const double h2,const double h3,\
    const double a11,const double a12,const double a13,\
    const double a21,const double a22,const double a23,\
    const double b1,const double b2,\
    double* x1_result,double* x2_result,double* x3_result);
int main()
{
    double x1,x2,x3;
    double p1,p2,p3,p4;
    double a,b,c,d;
    double h1,h2,h3;
    double a11,a12,a13;
    double a21,a22,a23;
    double b1,b2;
    
    double result,x1_result,x2_result,x3_result;
    
    scanf("%lf%lf%lf%lf%lf%lf",&x1,&x2,&p1,&p2,&p3,&p4);
    result=Problem1(x1,x2,p1,p2,p3,p4,&x1_result,&x2_result);
    printf("%.4lf %.4lf %.4lf\n",result,x1_result,x2_result);
    
    scanf("%lf%lf%lf%lf%lf%lf",&x1,&x2,&a,&b,&c,&d);
    result=Problem2(x1,x2,a,b,c,d,&x1_result,&x2_result);
    printf("%.4lf %.4lf %.4lf\n",result,x1_result,x2_result);
    
    scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",\
        &x1,&x2,&x3,&h1,&h2,&h3,&a11,&a12,&a13,&a21,&a22,&a23,&b1,&b2);
    result=Problem3(x1,x2,x3,h1,h2,h3,a11,a12,a13,a21,a22,a23,b1,b2,\
        &x1_result,&x2_result,&x3_result);
    printf("%.4lf %.4lf %.4lf %.4lf\n",result,x1_result,x2_result,x3_result);
    
    return 0;
}


double Problem1(double x1,double x2,\
    const double p1,const double p2,const double p3,const double p4,\
    double* x1_result,double* x2_result)
{
    *x1_result=1.0/p1/3;
    *x2_result=1.0/p2/3;
    return 3*log(3)+log(p1)+log(p2)-log(p3)-log(p4);
}

double Problem2(double x1,double x2,\
    const double a,const double b,const double c,const double d,\
    double* x1_result,double* x2_result)
{
    *x1_result=x1;
    *x2_result=x2;
    register double partial12_f=b/((x1+x2)*(x1+x2));
    register double& partial21_f=partial12_f;
    register double partial11_f=a*a*exp(a*x1)+partial12_f+2*c;
    register double partial22_f=partial12_f+2*d;
    register double partial1_f=a*exp(a*x1)-b/(x1+x2)+2*c*x1;
    register double partial2_f=-b/(x1+x2)+2*d*x2;
    register double delta=partial11_f*partial22_f-partial21_f*partial12_f;
    *x1_result=x1-(partial22_f*partial1_f-partial12_f*partial2_f)/delta;
    *x2_result=x2-(partial11_f*partial2_f-partial21_f*partial1_f)/delta;
    for(;(abs(*x1_result/x1-1)+abs(*x2_result/x2-1)>1e-10);)
    {
        x1=*x1_result;
        x2=*x2_result;
        partial12_f=b/((x1+x2)*(x1+x2));
        partial11_f=a*a*exp(a*x1)+partial12_f+2*c;
        partial22_f=partial12_f+2*d;
        partial1_f=a*exp(a*x1)-b/(x1+x2)+2*c*x1;
        partial2_f=-b/(x1+x2)+2*d*x2;
        delta=partial11_f*partial22_f-partial21_f*partial12_f;
        *x1_result=x1-(partial22_f*partial1_f-partial12_f*partial2_f)/delta;
        *x2_result=x2-(partial11_f*partial2_f-partial21_f*partial1_f)/delta;
    }
    return exp(a*x1)-b*log(x1+x2)+c*x1*x1+d*x2*x2;
}

double Problem3(double x1,double x2,double x3,\
    const double h1,const double h2,const double h3,\
    const double a11,const double a12,const double a13,\
    const double a21,const double a22,const double a23,\
    const double b1,const double b2,\
    double* x1_result,double* x2_result,double* x3_result)
{
    const double a12a23_a22a13=a12*a23-a22*a13;
    const double a13a21_a23a11=a13*a21-a23*a11;
    const double a11a22_a21a12=a11*a22-a21*a12;
    const double a21b1_a11b2=a21*b1-a11*b2;
    const double a22b1_a12b2=a22*b1-a12*b2;
    const double a23b1_a13b2=a23*b1-a13*b2;
    const double denominator=h1*a12a23_a22a13*a12a23_a22a13+\
                             h2*a13a21_a23a11*a13a21_a23a11+\
                             h3*a11a22_a21a12*a11a22_a21a12;
    *x1_result=\
        (-h2*a13a21_a23a11*a23b1_a13b2+h3*a11a22_a21a12*a22b1_a12b2)/denominator;
    *x2_result=\
        (-h3*a11a22_a21a12*a21b1_a11b2+h1*a12a23_a22a13*a23b1_a13b2)/denominator;
    *x3_result=\
        (-h1*a12a23_a22a13*a22b1_a12b2+h2*a13a21_a23a11*a21b1_a11b2)/denominator;
    return h1*(*x1_result)*(*x1_result)+\
           h2*(*x2_result)*(*x2_result)+\
           h3*(*x3_result)*(*x3_result);
}