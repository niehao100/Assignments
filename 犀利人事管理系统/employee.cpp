#include<iostream>
#include"employee.h"
using namespace std;
int Employee::counter(2013000);

Employee::~Employee()
{
    clog<<"欢迎使用,再见No."<<individual_emp_no_<<".\n";
}


int Employee::accum_pay()
{
    return accum_pay_;
}
void Employee::promote(int pay,double percentage)
{
    accum_pay_=pay;
}
istream& Employee::read_from(std::istream& in_stream)
{
    return in_stream
        .read((char*)(&individual_emp_no_),sizeof(individual_emp_no_))
        .read((char*)(&grade_),sizeof(grade_))
        .read((char*)(&accum_pay_),sizeof(accum_pay_));
}
ostream& Employee::write_to(std::ostream& out_stream)
{
    return out_stream
        .write((char*)(&individual_emp_no_),sizeof(individual_emp_no_))
        .write((char*)(&grade_),sizeof(grade_))
        .write((char*)(&accum_pay_),sizeof(accum_pay_));
}

istream& operator>>(istream& in,Employee& employee)
{
    in>>employee.grade_>>employee.accum_pay_;
    return in;
}

ostream& operator<<(ostream& out,const Employee& employee)
{
    out<<"个人编号:"<<employee.individual_emp_no_\
        <<"\n级别:"<<employee.grade_\
        <<"\n月薪:"<<employee.accum_pay_<<endl;
    return out;
}
