/*
 *  File Encoding: CP936/GBK
 *  Chi Blaok @ EE THU, All Rights Reserved.
 *
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include"employee.h"

class Manager:virtual public Employee
{
public:
    //取消了经理人数的限制
    Manager(bool add=true);
    ~Manager(){}

    //功能与基类相同,不予覆盖
    //virtual int accum_pay(){return accum_pay_;}
    //virtual void promote(int pay,double percentage){accum_pay_=pay;}
    //同名覆盖
    virtual std::istream& read_from(std::istream&  in_stream);
    virtual std::ostream& write_to (std::ostream& out_stream);

    //经理不能使用流输入,原因在于无法设置月薪,欲改变月薪只能使用promote
    friend std::ostream& operator<<(std::ostream& out,const Manager&);

protected:
    static const unsigned char grade_[5];
};

#endif//MANAGER_H_
