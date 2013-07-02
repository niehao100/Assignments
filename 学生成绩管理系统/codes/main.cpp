#include<cerrno>
#include<cstdlib>
#include<cstdio>
#include<ctime>

#include<iostream>

#include<conio.h>
#include<windows.h>

#include"classes/admin.h"
#include"classes/score.h"
#include"classes/student.h"
#include"classes/teacher.h"
#include"classes/user.h"

using namespace std;

bool go_on=true;
int main()
{
    system("title 学生成绩管理系统\ncls");
    Sleep(200);
    for(int i=0;i<12;++i)
    {
        for(int j=0;j<i;++j)
        {
            printf("     ");
        }
        printf("欢迎使用学生成绩管理系统\r");
        Sleep(100);
    }
    system("cls");

    //读取数据结构
    FILE* read_data=fopen("default.admin","r+");
    for(;read_data==NULL;)
    {
        if(errno==ENOENT)
        {
            printf("没有找到数据库文件\"default.admin\"，将创建空文件。");
            fclose(fopen("default.admin","w"));
            read_data=fopen("default.admin","r+");
            Wait();
            Wait();
            putchar('\r');
        }
        else
        {
            perror("Unable to open database default.admin");
        }
    }
    Admin* admin;
    long int init_pos=ftell(read_data);
    fseek(read_data,0,SEEK_END);    //测试文件尾位置
    if(ftell(read_data)==init_pos)  //文件空
    {
        admin=new Admin(Hash("password"));   //TODO:new:admin
        fseek(read_data,0,SEEK_SET);    //重置文件指针
    }
    else
    {
        long int size=ftell(read_data)-init_pos;
        char* buffer=new char[size];    //NOTE:new:buffer
        fseek(read_data,0,SEEK_SET);    //重置文件指针
        fread(buffer,1,size,read_data);
        admin=new Admin(buffer,size);   //TODO:new:admin
        delete[] buffer;                //NOTE:delete:buffer
        fseek(read_data,0,SEEK_SET);    //重置文件指针
    }

    /*//////////////////////////
    Score score1("微积分",1,1);
    vector<Score> score_vector1(1,score1);
    score_vector1;
    Student zhang_yue("张跃",2,1,score_vector1);
    Teacher su_ning("苏宁",3,23);
    //Admin* admin=new Admin(213);
    admin->AddTeacher(su_ning);
    admin->AddStudent(zhang_yue);
    admin->AddTeacher(su_ning);
    admin->AddStudent(zhang_yue);
    admin->AddTeacher(su_ning);
    admin->AddStudent(zhang_yue);
    admin->AddTeacher(su_ning);
    admin->AddStudent(zhang_yue);
    admin->AddTeacher(su_ning);
    admin->AddStudent(zhang_yue);
    admin->AddTeacher(su_ning);
    admin->AddStudent(zhang_yue);
    char* buf=new char[admin->WriteTo(NULL,0)];
    cout<<admin->WriteTo(NULL,0)<<endl;
    cout<<admin->WriteTo(NULL,0)<<endl;
    cout<<(admin->WriteTo(buf,admin->WriteTo(NULL,0)))<<endl;
    cout<<admin->ReadFrom(buf,admin->WriteTo(NULL,0))<<endl;
    cout<<(admin->teacher_vector_.begin()->name_);
    //return 0;
    //////////////////////////*/



    for(;go_on;)
    {
        system("cls");
        printf("****************************欢迎使用学生成绩管理系统****************************");
        char login_name[20]={'\0'};     //19位是uint64_t类型的上限
        char password_char[25]={'\0'};  //24字节密码经过Hash变为64位整数储存
        printf("请输入您的姓名或学号:");
        fgets(login_name,20,stdin);
        for(int i=0;i<20;++i)
        {
            login_name[19-i]=(login_name[19-i]=='\n'||login_name[19-i]=='\r')?'\0':login_name[19-i];
        }
        if(login_name[0]=='\0')
        {
            printf("用户名不能为空；按Q键退出，或按其他键重新输入。\n");
            Wait();
            char quit=getch();
            if(quit=='Q'||quit=='q')
            {
                break;
            }
            continue;
        }
        printf("请输入您的密码:");
        for(int i=0;i<24;++i)
        {
            char get=getch();
            switch(get)
            {
            case'\r':
                password_char[i]='\0';
                i=24;
                putch('\n');
                Wait(); //输入密码结束之后等待，防止暴力破解
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
        bool number=true;   //判断输入的是id还是用户名
        if(strlen(login_name)<MAX_NAME_LENGTH)
        {
            for(int i=0;i<20;++i)
            {
                if((login_name[i]>'9'||login_name[i]<'0')&&login_name[i]!='\0')
                {
                    number=false;
                }
                break;
            }
        }
        Teacher* teacher=NULL;
        Student* student=NULL;
        if(number)
        {
            uint64_t id;
            sscanf(login_name,"%llud",&id);
            if(id==admin->id_)  //管理员登录
            {
                if(Hash(password_char)!=admin->hash_)
                {
                    printf("用户名或密码不正确；按Q键退出，或按其他键重新输入。\n");
                    Wait();
                    char quit=getch();
                    if(quit=='Q'||quit=='q')
                    {
                        break;
                    }
                    continue;
                }
                admin->Manage();
                continue;
            }
            else    //其他用户登录
            {
                if(admin->admin_id_set_.count(id)!=0)     //如果已存在
                {
                    teacher=admin->FindTeacher(id);
                    if(teacher==NULL)
                    {
                        student=admin->FindStudent(id);
                        if(student!=NULL)
                        {
                            if(Hash(password_char)!=student->hash_)
                            {
                                printf("用户名或密码不正确；按Q键退出，或按其他键重新输入。\n");
                                Wait();
                                char quit=getch();
                                if(quit=='Q'||quit=='q')
                                {
                                    break;
                                }
                                continue;
                            }
                            student->Login();
                            continue;
                        }
                    }
                    else
                    {
                        if(Hash(password_char)!=teacher->hash_)
                        {
                            printf("用户名或密码不正确；按Q键退出，或按其他键重新输入。\n");
                            Wait();
                            char quit=getch();
                            if(quit=='Q'||quit=='q')
                            {
                                break;
                            }
                            continue;
                        }
                        teacher->Login();
                        continue;
                    }
                }
            }
        }
        if(strcmp(login_name,"admin")==0||
           strcmp(login_name,"Admin")==0||
           strcmp(login_name,"ADMIN")==0||
           strcmp(login_name,"administrator")==0||
           strcmp(login_name,"Administrator")==0||
           strcmp(login_name,"ADMINISTRATOR")==0)
        {
            if(Hash(password_char)!=admin->hash_)
            {
                printf("用户名或密码不正确；按Q键退出，或按其他键重新输入。\n");
                Wait();
                char quit=getch();
                if(quit=='Q'||quit=='q')
                {
                    break;
                }
                continue;
            }
            admin->Manage();
            continue;
        }
        teacher=admin->FindTeacher(login_name);
        if(teacher==NULL)
        {
            student=admin->FindStudent(login_name);
            if(student!=NULL)
            {
                if(Hash(password_char)!=student->hash_)
                {
                    printf("用户名或密码不正确；按Q键退出，或按其他键重新输入。\n");
                    Wait();
                    char quit=getch();
                    if(quit=='Q'||quit=='q')
                    {
                        break;
                    }
                    continue;
                }
                student->Login();
                continue;
            }
        }
        else
        {
            if(Hash(password_char)!=teacher->hash_)
            {
                printf("用户名或密码不正确；按Q键退出，或按其他键重新输入。\n");
                Wait();
                char quit=getch();
                if(quit=='Q'||quit=='q')
                {
                    break;
                }
                continue;
            }
            teacher->Login();
            continue;
        }
        printf("用户名或密码不正确；按Q键退出，或按其他键重新输入。\n");
        Wait();
        char quit=getch();
        if(quit=='Q'||quit=='q')
        {
            break;
        }
        continue;
    }
    size_t size=admin->WriteTo(NULL,0);
    char* buffer=new char[size];    //TODO:new:buffer
    admin->WriteTo(buffer,size);
    fwrite(buffer,1,size,read_data);
    fclose(read_data);
    delete[] buffer;                //NOTE:delete:buffer
    printf("感谢您的使用，再见!");












    return 0;
}
