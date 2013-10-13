/*
 *  File Encoding: CP936/GBK
 *  Chi Blaok @ EE THU, All Rights Reserved.
 *
 */

#ifndef TECHNICIAN_H_
#define TECHNICIAN_H_

#include"employee.h"

class Technician:virtual public Employee
{
public:
    //去掉人数限制提示
    Technician(int working_hours=0,bool add=true);
    ~Technician(){}

    virtual int accum_pay();
    virtual void promote(int pay,double percentage);
    virtual std::istream& read_from(std::istream&  in_stream);
    virtual std::ostream& write_to (std::ostream& out_stream);

    int working_hours(){return working_hours_;}
    void set_working_hours(int working_hours)
    {
        working_hours_=working_hours;
        accum_pay_=kHourPay*working_hours;
    }

    friend std::istream& operator>>(std::istream& in,Technician&);
    friend std::ostream& operator<<(std::ostream& in,const Technician&);

protected:
    static const unsigned char grade_[7];
    int working_hours_;
    int kHourPay;
};

#endif//TECHNICIAN_H_
