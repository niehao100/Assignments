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
    //ȡ���˾�������������
    Manager(bool add=true);
    ~Manager(){}

    //�����������ͬ,���踲��
    //virtual int accum_pay(){return accum_pay_;}
    //virtual void promote(int pay,double percentage){accum_pay_=pay;}
    //ͬ������
    virtual std::istream& read_from(std::istream&  in_stream);
    virtual std::ostream& write_to (std::ostream& out_stream);

    //������ʹ��������,ԭ�������޷�������н,���ı���нֻ��ʹ��promote
    friend std::ostream& operator<<(std::ostream& out,const Manager&);

protected:
    static const unsigned char grade_[5];
};

#endif//MANAGER_H_
