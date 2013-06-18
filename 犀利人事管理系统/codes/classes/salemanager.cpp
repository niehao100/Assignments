/*
 *  File Encoding: CP936/GBK
 *  Chi Blaok @ EE THU, All Rights Reserved.
 *
 */

#include<iostream>
#include<vector>
#include"salemanager.h"

using namespace std;

const unsigned char Salemanager::grade_[9]=
    {0xCF,0xFA,0xCA,0xDB,0xBE,0xAD,0xC0,0xED,'\0'};
const int kDefaultPay(8000);
const double kDefaultPercentage(0.04);

Salemanager::Salemanager(Salesman managedmen[],int n,bool add):
    Employee(-1,0,add),Manager(false),
    kPay(kDefaultPay),kPercentage(kDefaultPercentage)
{
    if(!add)
    {
        return;
    }
    sales_=0;
    for(int i=0;i<n;++i)
    {
        sales_+=managedmen[i].sales();
    }
    accum_pay_=accum_pay();
}

int Salemanager::accum_pay()
{
    return kPay+kPercentage*sales_;
}

void Salemanager::promote(int pay,double percentage)
{
    kPay=(pay==0?kPay:pay);
    kPercentage=(percentage==0?kPercentage:percentage);
    accum_pay_=accum_pay();
}

istream& Salemanager::read_from(std::istream& in_stream)
{
    return in_stream
        .read((char*)(&individual_emp_no_),sizeof(individual_emp_no_))
        .read((char*)(&accum_pay_),sizeof(accum_pay_))
        .read((char*)(&kPay),sizeof(kPay))
        .read((char*)(&kPercentage),sizeof(kPercentage));
}

ostream& Salemanager::write_to(std::ostream& out_stream)
{
    return out_stream
        .write((char*)(&individual_emp_no_),sizeof(individual_emp_no_))
        .write((char*)(&accum_pay_),sizeof(accum_pay_))
        .write((char*)(&kPay),sizeof(kPay))
        .write((char*)(&kPercentage),sizeof(kPercentage));
}

ostream& operator<<(std::ostream& out,const Salemanager& salemanager)
{
    out<<"个人编号:"<<salemanager.individual_emp_no_\
        <<"\n职位:"<<Salemanager::grade_\
        <<"\n月薪:"<<salemanager.accum_pay_<<endl;
    return out;
}
