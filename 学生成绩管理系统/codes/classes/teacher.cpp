#include<cstring>
#include<cstdio>

#include<windows.h>

#include"admin.h"
#include"teacher.h"

using namespace std;

Teacher::Teacher(const char* buffer,size_t size):User(NULL,0,0)
{
    ReadFrom(buffer,size);
}

size_t Teacher::WriteTo(char* buffer,size_t size)
{
    if(buffer==NULL)
    {
        return MAX_NAME_LENGTH+sizeof(uint64_t)*2;
    }
    if(MAX_NAME_LENGTH+sizeof(uint64_t)*2>size)
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

    return MAX_NAME_LENGTH+sizeof(uint64_t)*2;
}

size_t Teacher::ReadFrom(const char* buffer,size_t size)
{
    if(size<MAX_NAME_LENGTH+sizeof(uint64_t)*2)
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

    return MAX_NAME_LENGTH+sizeof(uint64_t)*2;
}

char* GetString(char* str,int n,FILE* file=stdin);
inline uint64_t GetId(const char* str="请输入编号",FILE* file=stdin);

int Teacher::Login(Admin* admin)
{
    bool init=true;
    for(;;)
    {
        system("cls");
        printf("********************************您的身份是:教师*********************************");
        if(init)
        {
            printf("欢迎使用，%s老师！",name_);
            Wait();
            init=false; //只显示一次欢迎信息;
        }
        putchar('\r');
        printf("请选择欲使用的功能:                            \n    1.录入学生成绩\n    2.修改学生成绩\n    3.删除学生成绩\n    4.修改登录密码\n    B.退出登录\n    Q.退出程序\n");
        char choice=getch();

        switch(choice)
        {
        case'1':    //录入学生成绩
        {
            system("cls");
            printf("********************************您的身份是:教师*********************************");
            printf("请要录入的科目:");
            char input_subject[MAX_SUBJECT_NAME_LENGTH]={'\0'};
            if(GetString(input_subject,MAX_SUBJECT_NAME_LENGTH)==NULL)
            {
                printf("输入错误。");
                Wait();
                break;
            }

            for(;;)
            {
                system("cls");
                printf("********************************您的身份是:教师*********************************");

                size_t star_num=80-10*2-strlen(input_subject);
                for(size_t i=0;i<star_num/2;++i)
                {
                    putchar('=');
                }
                printf("现在您录入的是%s的成绩",input_subject);
                for(size_t i=star_num/2;i<star_num;++i)
                {
                    putchar('=');
                }

                uint64_t input_id=GetId("请输入学生的学号:");
                if(input_id==0)
                {
                    printf("输入错误。\n");
                    printf("退出录入吗？按Q/Y/Esc退出。");
                    char quit=getch();
                    if(quit=='q'||quit=='Q'||quit=='Y'||quit=='y'||quit==27)
                    {
                        break;
                    }
                    continue;
                }

                if(admin->FindStudent(input_id)==NULL)
                {
                    printf("学号未找到。\n");
                    printf("退出录入吗？按Q/Y/Esc退出。");
                    char quit=getch();
                    if(quit=='q'||quit=='Q'||quit=='Y'||quit=='y'||quit==27)
                    {
                        break;
                    }
                    continue;
                }
                else
                {
                    Student* student=admin->FindStudent(input_id);
                    size_t found=0;
                    for(vector<Score>::iterator iter=student->score_vector_.begin();iter!=student->score_vector_.end();++iter)
                    {
                        if(strcmp(input_subject,iter->subject_)==0)
                        {
                            found++;
                        }
                    }
                    if(found>0)
                    {
                        printf("该学生已有本课程的成绩存在。");
                        Wait();
                        break;
                    }
                    printf("请输入分数:");
                    double input_mark=.0;
                    fflush(stdin);
                    scanf("%lf",&input_mark);
                    if(ferror(stdin))
                    {
                        printf("输入错误。");
                        printf("退出录入吗？按Q/Y/Esc退出。");
                        char quit=getch();
                        if(quit=='q'||quit=='Q'||quit=='Y'||quit=='y'||quit==27)
                        {
                            break;
                        }
                        continue;
                    }
                    fflush(stdin);
                    student->score_vector_.push_back(Score(input_subject,input_mark,id_));
                    printf("保存成功。\n");
                    printf("退出录入吗？按Q/Y/Esc退出。");
                    char quit=getch();
                    if(quit=='q'||quit=='Q'||quit=='Y'||quit=='y'||quit==27)
                    {
                        break;
                    }
                    continue;
                }
            }


            Wait();
            break;
        }

        case'2':    //修改学生成绩
        {
            uint64_t input_id=GetId("请输入学生的学号:");
            if(input_id==0)
            {
                printf("输入错误。");
                Wait();
                break;
            }
            else
            {
                if(admin->FindStudent(input_id)==NULL)
                {
                    printf("学号未找到。\n");
                    Wait();
                    break;
                }
                else
                {
                    printf("请输入欲修改的科目:");
                    char input_subject[MAX_SUBJECT_NAME_LENGTH]={'\0'};
                    if(GetString(input_subject,MAX_SUBJECT_NAME_LENGTH)==NULL)
                    {
                        printf("输入错误。");
                        Wait();
                        break;
                    }
                    else
                    {
                        Student* student=admin->FindStudent(input_id);
                        size_t found=0;
                        for(vector<Score>::iterator iter=student->score_vector_.begin();iter!=student->score_vector_.end();++iter)
                        {
                            if(strcmp(input_subject,iter->subject_)==0)
                            {
                                ++found;
                                printf("请输入修改后的分数:");
                                double input_mark;
                                if(scanf("%lf",&input_mark)==0)
                                {
                                    printf("输入错误。");
                                    Wait();
                                }
                                else
                                {
                                    iter->mark_=input_mark;
                                    printf("保存成功。");
                                    Wait();
                                }

                            }
                        }
                        if(found==0)
                        {
                            printf("未找到该科目。");
                            Wait();
                            break;
                        }
                        break;

                    }
                    break;

                }
                break;

            }
            break;
        }

        case'3':    //删除学生成绩
        {
            uint64_t input_id=GetId("请输入学生编号:");
            if(admin->FindStudent(input_id)==NULL)
            {
                printf("学号未找到。");
                Wait();
                break;
            }
            else
            {
                Student* student=admin->FindStudent(input_id);
                vector<Score> found;
                for(vector<Score>::iterator iter=student->score_vector_.begin();iter!=student->score_vector_.end();++iter)
                {
                    if(iter->teacher_==id_)
                    {
                        found.push_back(*iter);
                    }
                }
                if(found.empty())
                {
                    printf("该学生的记录中没有您录入的成绩。");
                    Wait();
                    break;
                }
                else
                {
                    for(size_t i=0;i<found.size();++i)
                    {
                        printf("%4u.\t科目:%s\t分数:%g\n",i+1,found[i].subject_,found[i].mark_);
                    }
                    size_t sub=0;
                    printf("请选择要删去的科目:");
                    if(scanf("%u",&sub)==0||sub==0||sub>found.size())
                    {
                        printf("输入错误。");
                        Wait();
                        break;
                    }
                    else
                    {
                        for(vector<Score>::iterator iter=student->score_vector_.begin();iter!=student->score_vector_.end();++iter)
                        {
                            if(strcmp(iter->subject_,found[sub-1].subject_)==0)
                            {
                                student->score_vector_.erase(iter);
                                printf("成功删除科目 %s 。",found[sub-1].subject_);
                                Wait();
                                Wait();
                                if(iter==student->score_vector_.end())
                                {
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    break;

                }
                break;

            }
            break;

        }

        case'4':    //修改登录密码
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

inline char* RemoveLastEndline(char* str,int n)
{
    for(int i=0;i<n;++i)
    {
        if(str[n-1-i]=='\n')
        {
            str[n-1-i]='\0';
            break;
        }
    }
    return str[0]=='\0'?NULL:str;
}

inline char* GetString(char* str,int n,FILE* file)
{
    return fgets(str,n,file)==NULL?NULL:RemoveLastEndline(str,n);
}

inline uint64_t GetId(const char* str,FILE* file)
{
    printf(str);
    uint64_t input_id=0;
    fscanf(file,"%llu",&input_id);
    fflush(file);
    return input_id;
}
