#include<cstring>

#include"admin.h"
#include"student.h"

using namespace std;

Student::Student(const char* buffer,size_t size):User(NULL,0,0),score_vector_()
{
    ReadFrom(buffer,size);
}

size_t Student::WriteTo(char* buffer,size_t size)
{
    if(buffer==NULL)
    {
        return MAX_NAME_LENGTH+sizeof(uint64_t)*2+sizeof(size_t)+sizeof(Score)*score_vector_.size();
    }

    if(MAX_NAME_LENGTH+sizeof(uint64_t)*2+sizeof(size_t)+sizeof(Score)*score_vector_.size()>size)
    {
        return 0;
    }

    strcpy(buffer,name_);
    buffer+=MAX_NAME_LENGTH;

    for(size_t i=0;i<sizeof(uint64_t);++i)
    {
        buffer[i]=((char*)(&id_))[i];
    }
    buffer+=sizeof(uint64_t);

    for(size_t i=0;i<sizeof(uint64_t);++i)
    {
        buffer[i]=((char*)(&hash_))[i];
    }
    buffer+=sizeof(uint64_t);

    size_t score_vector_size=score_vector_.size();
    for(size_t i=0;i<sizeof(size_t);++i)
    {
        buffer[i]=((char*)(&score_vector_size))[i];
    }
    buffer+=sizeof(size_t);

    for(vector<Score>::iterator iter=score_vector_.begin();iter!=score_vector_.end();++iter)
    {
        for(size_t i=0;i<sizeof(Score);++i)
        {
            buffer[i]=((char*)(&(*iter)))[i];
        }
        buffer+=sizeof(Score);
    }
    return MAX_NAME_LENGTH+sizeof(uint64_t)*2+sizeof(size_t)+sizeof(Score)*score_vector_size;
}

size_t Student::ReadFrom(const char* buffer,size_t size)
{
    if(size<MAX_NAME_LENGTH+sizeof(uint64_t)*2+sizeof(size_t))
    {
        return 0;
    }

    strncpy(name_,buffer,MAX_NAME_LENGTH);
    buffer+=MAX_NAME_LENGTH;

    for(size_t i=0;i<sizeof(uint64_t);++i)
    {
        ((char*)(&id_))[i]=buffer[i];
    }
    buffer+=sizeof(uint64_t);

    for(size_t i=0;i<sizeof(uint64_t);++i)
    {
        ((char*)(&hash_))[i]=buffer[i];
    }
    buffer+=sizeof(uint64_t);

    size_t score_vector_size;
    for(size_t i=0;i<sizeof(size_t);++i)
    {
        ((char*)(&score_vector_size))[i]=buffer[i];
    }
    buffer+=sizeof(size_t);

    score_vector_.clear();
    for(size_t i=0;i<score_vector_size;++i)
    {
        score_vector_.push_back(Score(buffer,MAX_SUBJECT_NAME_LENGTH+sizeof(double)+sizeof(uint64_t)));
        buffer+=sizeof(Score);
    }
    return MAX_NAME_LENGTH+sizeof(uint64_t)*2+sizeof(size_t)+sizeof(Score)*score_vector_size;
}

int Student::Login(Admin* admin)
{
    bool init=true;
    for(;;)
    {
        system("cls");
        printf("********************************您的身份是:学生*********************************");
        if(init)
        {
            printf("欢迎使用，%s同学！",name_);
            Wait();
            init=false; //只显示一次欢迎信息;
        }
        putchar('\r');
        printf("请选择欲使用的功能:                         \n    1.查询成绩\n    2.修改登录密码\n    B.退出登录\n    Q.退出程序\n");
        char choice=getch();

        switch(choice)
        {
        case'1':    //查询成绩
        {
            system("cls");
            printf("********************************您的身份是:学生*********************************");
            for(vector<Score>::iterator iter=score_vector_.begin();iter!=score_vector_.end();++iter)
            {
                printf("    科目：%s\t分数：%g\t负责教师：%s\n",iter->subject_,iter->mark_,(admin->FindTeacher(iter->teacher_)==NULL)?"\0x8\0x8\0x8\0x8\0x8\0x8\0x8\0x8":admin->FindTeacher(iter->teacher_)->name_);
            }


            Pause();
            break;
        }

        case'2':    //修改登录密码
        {
            printf("请输入原来的密码:");
            char password_char[25]={'\0'};
            for(int i=0;i<24;++i)
            {
                char get=getch();
                switch(get)
                {
                case'\r':
                    password_char[i]='\0';
                    i=24;
                    putch('\n');
                    Wait();
                    break;
                case 8:
                    if(i>0)
                    {
                        putch(8);
                        putch(0);
                        putch(8);
                        --i;
                    }
                    --i;
                    break;
                default:
                    if(get>=0x20&&get<=0x7E)
                    {
                        putch('*');
                        password_char[i]=get;
                    }
                    else
                    {
                        --i;
                    }
                }
            }
            if(Hash(password_char)!=hash_)
            {
                printf("密码错误。");
                Wait();
                Wait();
                break;
            }

            printf("请输入新的密码:");
            for(int i=0;i<24;++i)
            {
                char get=getch();
                switch(get)
                {
                case'\r':
                    password_char[i]='\0';
                    i=24;
                    putch('\n');
                    break;
                case 8:
                    if(i>0)
                    {
                        putch(8);
                        putch(0);
                        putch(8);
                        --i;
                    }
                    --i;
                    break;
                default:
                    if(get>=0x20&&get<=0x7E)
                    {
                        putch('*');
                        password_char[i]=get;
                    }
                    else
                    {
                        --i;
                    }
                }
            }
            printf("请再次输入密码以确认:");
            char password_check[25]={'\0'};  //24字节密码经过Hash变为64位整数储存
            for(int i=0;i<24;++i)
            {
                char get=getch();
                switch(get)
                {
                case'\r':
                    password_check[i]='\0';
                    i=24;
                    putch('\n');
                    break;
                case 8:
                    if(i>0)
                    {
                        putch(8);
                        putch(0);
                        putch(8);
                        --i;
                    }
                    --i;
                    break;
                default:
                    if(get>=0x20&&get<=0x7E)
                    {
                        putch('*');
                        password_check[i]=get;
                    }
                    else
                    {
                        --i;
                    }
                }
            }
            if(strcmp(password_char,password_check)==0)
            {
                hash_=Hash(password_char);
                printf("密码修改成功。");
                Wait();
                Wait();
                break;
            }
            else
            {
                printf("两次输入的密码不符。");
                Wait();
                Wait();
                break;
            }
            break;
        }

        case'B':case'b':case 27:
            return 0;

        case'Q':case'q':
            extern bool go_on;
            go_on=false;
            return 0;
        default:
            printf("输入错误。");
            Wait();
        }
    }
    return 0;
}
