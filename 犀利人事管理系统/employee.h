#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

class Employee
{
public:
    Employee(int grade=0,int pay=0,bool add=true):grade_(grade),accum_pay_(pay)
    {
        if(add){++counter;}
        individual_emp_no_=counter;
    }

    virtual ~Employee();

    int grade(){return grade_;}
    void set_grade(int grade){grade_=grade;}

    int individual_emp_no(){return individual_emp_no_;}

    virtual int accum_pay();
    virtual void promote(int pay,double percentage);
    virtual std::istream& read_from(std::istream&  in_stream);
    virtual std::ostream& write_to (std::ostream& out_stream);

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
