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
    system("title ѧ���ɼ�����ϵͳ");
    system("cls");
    Sleep(200);
    for(int i=0;i<12;++i)
    {
        for(int j=0;j<i;++j)
        {
            printf("     ");
        }
        printf("��ӭʹ��ѧ���ɼ�����ϵͳ\r");
        Sleep(100);
    }
    system("cls");

    //��ȡ���ݽṹ
    FILE* read_data=fopen("default.admin","r+b");
    for(;read_data==NULL;)
    {
        if(errno==ENOENT)
        {
            printf("û���ҵ����ݿ��ļ�\"default.admin\"�����������ļ���");
            fclose(fopen("default.admin","wb"));
            read_data=fopen("default.admin","r+b");
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
    fseek(read_data,0,SEEK_END);    //�����ļ�βλ��
    if(ftell(read_data)==init_pos)  //�ļ���
    {
        admin=new Admin(Hash("password"));   //TODO:new:admin
        fseek(read_data,0,SEEK_SET);    //�����ļ�ָ��
    }
    else
    {
        size_t size=ftell(read_data)-init_pos;
        char* buffer=new char[size];    //NOTE:new:buffer
        fseek(read_data,0,SEEK_SET);    //�����ļ�ָ��
        size_t read_size=fread(buffer,1,size,read_data);
        if(read_size!=size)
        {
            printf("Failed to read database.\n%d bytes should be read, but only %d bytes were read.",size,read_size);
            Pause();
            return -1;
        }
        admin=new Admin(buffer,size);   //TODO:new:admin
        delete[] buffer;                //NOTE:delete:buffer
        fseek(read_data,0,SEEK_SET);    //�����ļ�ָ��
    }

    for(;go_on;)
    {
        system("cls");
        printf("****************************��ӭʹ��ѧ���ɼ�����ϵͳ****************************");
        char login_name[20]={'\0'};     //19λ��uint64_t���͵�����
        char password_char[25]={'\0'};  //24�ֽ����뾭��Hash��Ϊ64λ��������
        printf("������������������:");
        fgets(login_name,20,stdin);
        for(int i=0;i<20;++i)
        {
            login_name[19-i]=(login_name[19-i]=='\n'||login_name[19-i]=='\r')?'\0':login_name[19-i];
        }
        if(login_name[0]=='\0')
        {
            printf("�û�������Ϊ�գ���Q���˳������������������롣\n");
            Wait();
            char quit=getch();
            if(quit=='Q'||quit=='q')
            {
                break;
            }
            continue;
        }
        printf("��������������:");
        for(int i=0;i<24;++i)
        {
            char get=getch();
            switch(get)
            {
            case'\r':
                password_char[i]='\0';
                i=24;
                putch('\n');
                Wait(); //�����������֮��ȴ�����ֹ�����ƽ�
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
        bool number=true;   //�ж��������id�����û���
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
            if(id==admin->id_)  //����Ա��¼
            {
                if(Hash(password_char)!=admin->hash_)
                {
                    printf("�û��������벻��ȷ����Q���˳������������������롣\n");
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
            else    //�����û���¼
            {
                if(admin->admin_id_set_.count(id)!=0)     //����Ѵ���
                {
                    teacher=admin->FindTeacher(id);
                    if(teacher==NULL)
                    {
                        student=admin->FindStudent(id);
                        if(student!=NULL)
                        {
                            if(Hash(password_char)!=student->hash_)
                            {
                                printf("�û��������벻��ȷ����Q���˳������������������롣\n");
                                Wait();
                                char quit=getch();
                                if(quit=='Q'||quit=='q')
                                {
                                    break;
                                }
                                continue;
                            }
                            student->Login(admin);
                            continue;
                        }
                    }
                    else
                    {
                        if(Hash(password_char)!=teacher->hash_)
                        {
                            printf("�û��������벻��ȷ����Q���˳������������������롣\n");
                            Wait();
                            char quit=getch();
                            if(quit=='Q'||quit=='q')
                            {
                                break;
                            }
                            continue;
                        }
                        teacher->Login(admin);
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
                printf("�û��������벻��ȷ����Q���˳������������������롣\n");
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
                    printf("�û��������벻��ȷ����Q���˳������������������롣\n");
                    Wait();
                    char quit=getch();
                    if(quit=='Q'||quit=='q')
                    {
                        break;
                    }
                    continue;
                }
                student->Login(admin);
                continue;
            }
        }
        else
        {
            if(Hash(password_char)!=teacher->hash_)
            {
                printf("�û��������벻��ȷ����Q���˳������������������롣\n");
                Wait();
                char quit=getch();
                if(quit=='Q'||quit=='q')
                {
                    break;
                }
                continue;
            }
            teacher->Login(admin);
            continue;
        }
        printf("�û��������벻��ȷ����Q���˳������������������롣\n");
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
    printf("���ڱ���...\r");
    Wait();
    delete[] buffer;                //NOTE:delete:buffer
    printf("��л����ʹ�ã��ټ�!");












    return 0;
}
