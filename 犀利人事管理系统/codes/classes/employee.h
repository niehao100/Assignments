/*
 *  File Encoding: CP936/GBK
 *  Chi Blaok @ EE THU, All Rights Reserved.
 *
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

class Employee
{
public:
    //使用等级和月薪初始化,如果add设为false则不增加计数
    Employee(int grade=0,int pay=0,bool add=true):
        individual_emp_no_(counter),grade_(grade),accum_pay_(pay)
    {
        if(add){++counter;}
        ;
    }
    //使用虚析构函数避免使用基类指针数组时发生问题
    //因并非每次析构都需要,遂取消了每次提示再见的功能
    virtual ~Employee(){};

    int grade(){return grade_;}
    void set_grade(int grade){grade_=grade;}
    int individual_emp_no(){return individual_emp_no_;}

    //计算月薪
    virtual int accum_pay(){return accum_pay_;}
    //设置底薪和提成
    virtual void promote(int pay,double percentage){accum_pay_=pay;}
    //用于二进制IO
    virtual std::istream& read_from(std::istream&  in_stream);
    virtual std::ostream& write_to (std::ostream& out_stream);

    //流IO和文件IO用到的友元
    friend std::istream& operator>>(std::istream& in,Employee&);
    friend std::ostream& operator<<(std::ostream& in,const Employee&);
    friend int LoadData(const char* filename);
    friend int SaveData(const char* filename);

protected:
    int individual_emp_no_;
    int grade_;
    int accum_pay_;
private:
    static int counter;
};
#endif//EMPLOYEE_H_
