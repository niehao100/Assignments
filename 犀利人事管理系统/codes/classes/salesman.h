#ifndef SALESMAN_H_
#define SALESMAN_H_

#include"employee.h"

class Salesman:virtual public Employee
{
public:
    Salesman(int sales=0,bool add=true);
    ~Salesman(){}

    virtual int accum_pay();
    virtual void promote(int pay,double percentage);
    virtual std::istream& read_from(std::istream&  in_stream);
    virtual std::ostream& write_to (std::ostream& out_stream);

    int sales(){return sales_;}
    void set_sales(int sales)
    {
        sales_=sales;
        accum_pay_=accum_pay();
    }

    friend std::istream& operator>>(std::istream& in,Salesman&);
    friend std::ostream& operator<<(std::ostream& in,const Salesman&);

protected:
    static const unsigned char grade_[7];
    int sales_;
    double kPercentage;
};

#endif//SALESMAN_H_
