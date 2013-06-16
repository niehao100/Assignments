#include<iostream>
#include"salesman.h"
using namespace std;
const unsigned char Salesman::grade_[7]={0xCF,0xFA,0xCA,0xDB,0xD4,0xB1,'\0'};
const double kDefaultPercentage(0.05);

Salesman::Salesman(int sales,bool add):
    Employee(-1,kDefaultPercentage*sales,add),
    sales_(sales),kPercentage(kDefaultPercentage){}

int Salesman::accum_pay()
{
    return kPercentage*sales_;
}
void Salesman::promote(int pay,double percentage)
{
    kPercentage=percentage;
    accum_pay_=accum_pay();
}
istream& Salesman::read_from(std::istream& in_stream)
{
    return in_stream
        .read((char*)(&individual_emp_no_),sizeof(individual_emp_no_))
        .read((char*)(&accum_pay_),sizeof(accum_pay_))
        .read((char*)(&sales_),sizeof(sales_))
        .read((char*)(&kPercentage),sizeof(kPercentage));
}
ostream& Salesman::write_to(std::ostream& out_stream)
{
    return out_stream
        .write((char*)(&individual_emp_no_),sizeof(individual_emp_no_))
        .write((char*)(&accum_pay_),sizeof(accum_pay_))
        .write((char*)(&sales_),sizeof(sales_))
        .write((char*)(&kPercentage),sizeof(kPercentage));
}

istream& operator>>(istream& in,Salesman& salesman)
{
    in>>salesman.sales_;
    if(!in.fail())
    {
        salesman.accum_pay_=salesman.accum_pay();
    }
    return in;
}

ostream& operator<<(ostream& out,const Salesman& salesman)
{
    out<<"个人编号:"<<salesman.individual_emp_no_\
        <<"\n职位:"<<Salesman::grade_\
        <<"\n月销售额:"<<salesman.sales_\
        <<"\n月薪:"<<salesman.accum_pay_<<endl;
    return out;
}
