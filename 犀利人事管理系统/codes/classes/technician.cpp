/*
 *  File Encoding: CP936/GBK
 *  Chi Blaok @ EE THU, All Rights Reserved.
 *
 */

#include<iostream>
#include"technician.h"
using namespace std;
const unsigned char Technician::grade_[7]={0xBC,0xBC,0xCA,0xF5,0xD4,0xB1,'\0'};
const int kDefaultHourPay(260);

Technician::Technician(int working_hours,bool add):Employee(-1,kDefaultHourPay*working_hours,add),working_hours_(working_hours),kHourPay(kDefaultHourPay){}

int Technician::accum_pay()
{
    return kHourPay*working_hours_;
}
void Technician::promote(int pay,double percentage)
{
    kHourPay=pay;
    accum_pay_=accum_pay();
}
istream& Technician::read_from(std::istream& in_stream)
{
    return in_stream
        .read((char*)(&individual_emp_no_),sizeof(individual_emp_no_))
        .read((char*)(&accum_pay_),sizeof(accum_pay_))
        .read((char*)(&working_hours_),sizeof(working_hours_))
        .read((char*)(&kHourPay),sizeof(kHourPay));
}
ostream& Technician::write_to(std::ostream& out_stream)
{
    return out_stream
        .write((char*)(&individual_emp_no_),sizeof(individual_emp_no_))

        .write((char*)(&accum_pay_),sizeof(accum_pay_))
        .write((char*)(&working_hours_),sizeof(working_hours_))
        .write((char*)(&kHourPay),sizeof(kHourPay));
}

istream& operator>>(istream& in,Technician& technician)
{
    in>>technician.working_hours_;
    if(!in.fail())
    {
        technician.accum_pay_=technician.accum_pay();
    }
    return in;
}

ostream& operator<<(ostream& out,const Technician& technician)
{
    out<<"个人编号:"<<technician.individual_emp_no_\
        <<"\n职位:"<<Technician::grade_\
        <<"\n月工作小时数:"<<technician.working_hours_\
        <<"\n月薪:"<<technician.accum_pay_<<endl;
    return out;
}
