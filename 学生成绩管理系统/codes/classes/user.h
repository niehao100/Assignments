#ifndef USER_H_
#define USER_H_

#define MAX_NAME_LENGTH 16

#include<cstdint>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>

#include<set>

#include<conio.h>
#include<windows.h>

inline void Pause()
{
    fflush(stdin);
    fflush(stdout);
    getch();
}

inline void Wait()
{
    fflush(stdin);
    fflush(stdout);
    time_t start,current;
    time(&start);
    for(time(&current);current-start<1.0;time(&current));
}

class User
{
public:
    User(const char* name,uint64_t id,uint64_t password);
    virtual ~User();

    bool Identify(const char* password);
    virtual size_t WriteTo(char* buffer,size_t size)=0;
    virtual size_t ReadFrom(const char* buffer,size_t size)=0;

    friend class Teacher;
    friend class Student;
    friend class Admin;
    friend int main();

protected:
    char name_[MAX_NAME_LENGTH];    //不允许超长；空为出错
    uint64_t id_;                   //0x0保留
    uint64_t hash_;                 //散列后的密码
};

inline uint64_t Hash(const char* password_char)
{
    char password[25]={'\0'};
    strncpy(password,password_char,24);
    return ((*((uint64_t*)(password   ))+8)>>1|((*((uint64_t*)(password   ))+8)<<7))+
           ((*((uint64_t*)(password+ 8))+5)>>2|((*((uint64_t*)(password+ 8))+5)<<6))+
           ((*((uint64_t*)(password+16))+1)>>5|((*((uint64_t*)(password+16))+1)<<3));
}

#endif // USER_H_
