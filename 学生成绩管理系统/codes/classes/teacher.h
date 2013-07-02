#ifndef TEACHER_H_
#define TEACHER_H_
#include"user.h"
class Teacher:virtual public User
{
public:
    Teacher(const char* name,uint64_t id,uint64_t password):
        User(name,id,password){}
    Teacher(const char* buffer,size_t size);
    ~Teacher(){}
    virtual size_t WriteTo(char* buffer,size_t size);
    virtual size_t ReadFrom(const char* buffer,size_t size);

    int Login();
};
#endif // TEACHER_H_
