#ifndef STUDENT_H_
#define STUDENT_H_

#include<cstdlib>
#include<vector>

#include"score.h"
#include"user.h"

class Admin;

class Student:virtual public User
{
public:
    Student(const char* name,uint64_t id,uint64_t password,std::vector<Score> score_vector):
        User(name,id,password),score_vector_(score_vector){}
    Student(const char* buffer,size_t size);
    ~Student(){}
    virtual size_t WriteTo(char* buffer,size_t size);
    virtual size_t ReadFrom(const char* buffer,size_t size);

    int Login(Admin* admin);

    friend class Teacher;
    friend class Admin;

protected:
    std::vector<Score> score_vector_;
};
#endif // STUDENT_H_
