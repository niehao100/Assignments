#ifndef MANAGER_H_
#define MANAGER_H_

#include"employee.h"

class Manager:virtual public Employee
{
public:
    Manager(bool check=true,bool add=true);
    ~Manager(){}

    virtual int accum_pay();
    virtual void promote(int pay,double percentage);
    virtual std::istream& read_from(std::istream&  in_stream);
    virtual std::ostream& write_to (std::ostream& out_stream);

    friend std::ostream& operator<<(std::ostream& out,const Manager&);
protected:
    static const unsigned char grade_[5];
private:
    static int manager_counter;
};

#endif//MANAGER_H_
