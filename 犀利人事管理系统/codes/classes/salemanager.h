/*
 *  File Encoding: CP936/GBK
 *  Chi Blaok @ EE THU, All Rights Reserved.
 *
 */

#ifndef SALEMANAGER_H_
#define SALEMANAGER_H_

#include"manager.h"
#include"salesman.h"

class Salemanager:virtual public Manager,virtual public Salesman
{
public:
    //ȡ������������ʾ
    Salemanager(Salesman managedmen[],int n,bool add=true);
    ~Salemanager(){}

    //ͬ������
    virtual int accum_pay();
    virtual void promote(int pay,double percentage);
    virtual std::istream& read_from(std::istream&  in_stream);
    virtual std::ostream& write_to (std::ostream& out_stream);

    //���۾�����������
    friend std::ostream& operator<<(std::ostream& in,const Salemanager&);

protected:
    static const unsigned char grade_[9];
    int kPay;
    double kPercentage;
};
#endif//SALEMANAGER_H_
