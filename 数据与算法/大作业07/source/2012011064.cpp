/*
*
*  Template for Experiment 7,
*  1)N_th Sorted Float
*  2)Solution For Quadratic Equation
*  3)Kahan Summation
*  4)ill-conditioned Summation
*  Pleas fill in the functions,do not modify other settings 
*  
*  2013/11
*
*/
#include<iostream>
#include<math.h>
using namespace std;
#define LarN 100005      //the possible maximum length of input array,please do not alter it

float sorted_float(int N){
	//N_th sorted normalized positive float number,the first one is +2^(-126) 
	float ret;
	//your solution goes here
    
    int positive_infinite_int=0x7F800000;
    int negative_infinite_int=0xFF800000;
    
    if(0==N)
    {
        return 0.0f;
    }
    
    int n=N>0 ? N : -N;
    if(n>0xFE*0x800000)
    {
        return N>0 ?\
            *((float*)&positive_infinite_int):\
            *((float*)&negative_infinite_int);
    }
    int fake_int=N>0 ? 0 : 0x80000000;
    fake_int|=((n%0x800000==0) ? ((n/0x800000)<<23) : ((n/0x800000+1)<<23));
    fake_int|=((n%0x800000==0) ?     0x7FFFFF       :  (n%0x800000-1));
    ret=*((float*)&fake_int);
	
	
	
	return ret;
}
void quadratic_solution(double a,double b,double c,double *roots){
	//solution for equation ax^2+bx+c=0
	//roots[0]=x1,roots[1]==x2,and x1<=x2
	//your solution goes here
	
	
	
    //除以最大绝对值系数
    double a_abs=(a>0.0 ? a : -a);
    double b_abs=(b>0.0 ? b : -b);
    double c_abs=(c>0.0 ? c : -c);
    double max_abs=\
        (a_abs>b_abs)?(a_abs>c_abs?a_abs:c_abs):(b_abs>c_abs?b_abs:c_abs);
    a/=max_abs;
    b/=max_abs;
    c/=max_abs;
    b_abs/=max_abs;
    
    if(b*b<4.0*a*c)
    {
        roots[0]=0.0;
        roots[1]=0.0;
        return;
    }
    
    double delta=sqrt(b*b-4.0*a*c);
    
    if(b>0)
    {
        roots[0]=(-b-delta)/(2.0*a);
        roots[1]=2.0*c/(-b-delta);
    }
    else
    {
        roots[0]=(b_abs+delta)/(2.0*a);
        roots[1]=2.0*c/(b_abs+delta);
    }
    if(roots[1]<roots[0])
    {
        double temp=roots[1];
        roots[1]=roots[0];
        roots[0]=temp;
    }
    0.0==roots[0] && (roots[0]=0.0);
    0.0==roots[1] && (roots[1]=0.0);
    
    
	
	
	
	return;
}

double ill_conditioned_sum(double *x,int N);
double Kahan_sum(double *x,int N){
return ill_conditioned_sum(x,N);    //注释此行则使用Kahan算法
	//summation of double array,N is the length of the array
	double ret;
	//your solution goes here

    ret=0.0;
    double temp=0.0;
    double c=0.0;
    for(int i=0;i<N;++i)
    {
        temp=ret+(x[i]-c);
        c=temp-ret-x[i];
        ret=temp;
    }
    
	
	
	
	return ret;
}



double ill_conditioned_sum(double *x,int N){
	//summation of double array,N is the length of the array
	double ret;
	//your solution goes here
	
	
    
    //将浮点数转为定点数避免精度损失
    //代价是极大地浪费空间和时间，不过反正没说时间要求
    const int kUnitSize=8*sizeof(uint64_t);
    const int kBinMax=2098/kUnitSize+1;
    uint64_t** x_fixed=new uint64_t*[N]();
    uint64_t* result=new uint64_t[kBinMax]();
    bool* x_negative=new bool[N]();
    //每次读一个浮点数转成定点数，定点数固定2112位，另有一个bool存符号
    for(int i=0;i<N;++i)
    {
        x_fixed[i]=new uint64_t[kBinMax]();
        x_negative[i]=(*((uint64_t*)(x+i)))&0x8000000000000000;
        int exp=int(((*((uint64_t*)(x+i)))>>52)&0x7FF)-1023;
        uint64_t bin=(*((uint64_t*)(x+i))&0xFFFFFFFFFFFFF)|0x10000000000000;
        if((1022+exp)%kUnitSize<=11)    //尾数可以归并到一个单元
        {
            x_fixed[i][kBinMax-(1022+exp)/kUnitSize-1]|=\
                (bin<<((1022+exp)%kUnitSize));
        }
        else
        {
            x_fixed[i][kBinMax-(1022+exp)/kUnitSize-1]|=\
                (bin<<((1022+exp)%kUnitSize));
            x_fixed[i][kBinMax-(1022+exp)/kUnitSize-2]|=\
                (bin>>(kUnitSize-(1022+exp)%kUnitSize));
        }
    }
    
    //加减法分开做，反正绝对值和都不会溢出。先做加法
    for(int n=0;n<N;++n)
    {
        if(x_negative[n])
        {
            continue;
        }
        bool overflow=false;
        for(int i=0;i<kBinMax;++i)
        {
            uint64_t temp=result[i];
            result[i]+=x_fixed[n][i];
            bool internal_overflow=result[i]<temp || result[i]<x_fixed[n][i];
            temp=result[i];
            result[i]+=overflow?1:0;
            overflow=internal_overflow||(result[i]<temp || result[i]<overflow);
        }
    }
    
    //减法
    bool overflow=false;
    for(int n=0;n<N;++n)
    {
        if(!x_negative[n])
        {
            continue;
        }
        for(int i=kBinMax-1;i>=0;--i)
        {
            if(result[i]==0 && overflow)
            {
                overflow=true;
                result[i]-=1;
                result[i]-=x_fixed[n][i];
            }
            else
            {
                overflow && (result[i]-=1);
                overflow=result[i]<x_fixed[n][i];
                result[i]-=x_fixed[n][i];
            }
        }
    }
    
    //overflow说明结果为负，应当取反加一得其绝对值
    if(overflow)
    {
        for(int i=0;i<kBinMax;++i)
        {
            result[i]=~result[i];
        }
        bool internal_overflow=true;
        for(int i=kBinMax-1;i>=0;--i)
        {
            uint64_t temp=result[i];
            internal_overflow && (++result[i]);
            internal_overflow=(result[i]<temp);
        }
    }
    
    //计算定点数转为浮点数对应的指数
    int initial_zeros=0;
    for(initial_zeros=0;initial_zeros<kBinMax*kUnitSize;++initial_zeros)
    {
        if((result[initial_zeros/kUnitSize]>>\
            (kUnitSize-initial_zeros%kUnitSize-1))&1)
        {
            break;
        }
    }
    if(initial_zeros==kBinMax*kUnitSize)
    {
        return 0.0;
    }
    int result_exp=kBinMax*kUnitSize-initial_zeros-1075;
    uint64_t result_bin=0;
    if((1022+result_exp)%kUnitSize<=12)
    {
        result_bin =\
            result[kBinMax-(1022+result_exp)/kUnitSize-1]>>\
            ((1022+result_exp)%kUnitSize);
        result_bin&=0xFFFFFFFFFFFFF;
    }
    else
    {
        result_bin =\
            result[kBinMax-(1022+result_exp)/kUnitSize-1]>>\
            ((1022+result_exp)%kUnitSize);
        result_bin|=\
            result[kBinMax-(1022+result_exp)/kUnitSize-2]<<\
            (kUnitSize-(1022+result_exp)%kUnitSize);
    }
    ret=0.0;
    overflow && ((*((uint64_t*)&ret))|=0x8000000000000000);
    (*((uint64_t*)&ret))|=((uint64_t(result_exp)+1023)<<52);
    (*((uint64_t*)&ret))|= (result_bin&0xFFFFFFFFFFFFF);
    
    
    for(int i=0;i<N;++i)
    {
        delete[] x_fixed[i];
    }
    delete[] x_fixed;
    delete[] x_negative;
    
    
	
	
	return ret;
}



float n_inf=-1.0e100,p_inf=+1.0e100;
int main(){
	int T_case,N;
	double coefs[3],roots[2],x[LarN];
	float sf;
	//problem 1, sorted float number
	scanf("%d",&T_case);
	while(T_case--){
		scanf("%d",&N);
		sf=sorted_float(N);
		if(sf==p_inf)printf("+1.0e100\n");
		else if(sf==n_inf)printf("-1.0e100\n");
		else printf("%.9e\n",sf);
	}
	//problem 2, solution for quadratic equation
	scanf("%d",&T_case);	
	while(T_case--){
		scanf("%le %le %le",&coefs[0],&coefs[1],&coefs[2]);
		quadratic_solution(coefs[0],coefs[1],coefs[2],roots);
		printf("%.16le %.16le\n",roots[0],roots[1]);
	}
	//problem 3, Kahan summation
	scanf("%d",&T_case);
	while(T_case--){
		scanf("%d",&N);
		for(int i=0;i<N;i++){scanf("%X %X",(int*)(&x[i])+1,(int*)(&x[i]));}
		printf("%.16e\n",Kahan_sum(x,N));
	}

	//problem 4, ill-conditioned summation
	scanf("%d",&T_case);
	while(T_case--){
		scanf("%d",&N);
		for(int i=0;i<N;i++){scanf("%X %X",(int*)(&x[i])+1,(int*)(&x[i]));}
		printf("%.16e\n",ill_conditioned_sum(x,N));
	}
	return 0;
}
