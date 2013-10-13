/*
 *  File Encoding: CP936/GBK
 *  Chi Blaok @ EE THU, All Rights Reserved.
 *
 */

#include<iostream>
#include"manager.h"

using namespace std;
const unsigned char Manager::grade_[5]={0xBE,0xAD,0xC0,0xED,'\0'};  //经理inGBK
const int kDefaultPay(12000);

Manager::Manager(bool add):Employee(-1,kDefaultPay,add){}

istream& Manager::read_from(std::istream& in_stream)
{
    return in_stream
        .read((char*)(&individual_emp_no_),sizeof(individual_emp_no_))
        .read((char*)(&accum_pay_),sizeof(accum_pay_));
}

ostream& Manager::write_to(std::ostream& out_stream)
{
    return out_stream
        .write((char*)(&individual_emp_no_),sizeof(individual_emp_no_))
        .write((char*)(&accum_pay_),sizeof(accum_pay_));
}

ostream& operator<<(ostream& out,const Manager& manager)
{
    out<<"个人编号:"<<manager.individual_emp_no_\
        <<"\n职位:"<<Manager::grade_\
        <<"\n月薪:"<<manager.accum_pay_<<endl;
    return out;
}
