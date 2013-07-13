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
inline uint64_t GetId(const char* str="��������",FILE* file=stdin);

int Teacher::Login(Admin* admin)
{
    bool init=true;
    for(;;)
    {
        system("cls");
        printf("********************************���������:��ʦ*********************************");
        if(init)
        {
            printf("��ӭʹ�ã�%s��ʦ��",name_);
            Wait();
            init=false; //ֻ��ʾһ�λ�ӭ��Ϣ;
        }
        putchar('\r');
        printf("��ѡ����ʹ�õĹ���:                            \n    1.¼��ѧ���ɼ�\n    2.�޸�ѧ���ɼ�\n    3.ɾ��ѧ���ɼ�\n    4.�޸ĵ�¼����\n    B.�˳���¼\n    Q.�˳�����\n");
        char choice=getch();

        switch(choice)
        {
        case'1':    //¼��ѧ���ɼ�
        {
            system("cls");
            printf("********************************���������:��ʦ*********************************");
            printf("��Ҫ¼��Ŀ�Ŀ:");
            char input_subject[MAX_SUBJECT_NAME_LENGTH]={'\0'};
            if(GetString(input_subject,MAX_SUBJECT_NAME_LENGTH)==NULL)
            {
                printf("�������");
                Wait();
                break;
            }

            for(;;)
            {
                system("cls");
                printf("********************************���������:��ʦ*********************************");

                size_t star_num=80-10*2-strlen(input_subject);
                for(size_t i=0;i<star_num/2;++i)
                {
                    putchar('=');
                }
                printf("������¼�����%s�ĳɼ�",input_subject);
                for(size_t i=star_num/2;i<star_num;++i)
                {
                    putchar('=');
                }

                uint64_t input_id=GetId("������ѧ����ѧ��:");
                if(input_id==0)
                {
                    printf("�������\n");
                    printf("�˳�¼���𣿰�Q/Y/Esc�˳���");
                    char quit=getch();
                    if(quit=='q'||quit=='Q'||quit=='Y'||quit=='y'||quit==27)
                    {
                        break;
                    }
                    continue;
                }

                if(admin->FindStudent(input_id)==NULL)
                {
                    printf("ѧ��δ�ҵ���\n");
                    printf("�˳�¼���𣿰�Q/Y/Esc�˳���");
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
                        printf("��ѧ�����б��γ̵ĳɼ����ڡ�");
                        Wait();
                        break;
                    }
                    printf("���������:");
                    double input_mark=.0;
                    fflush(stdin);
                    scanf("%lf",&input_mark);
                    if(ferror(stdin))
                    {
                        printf("�������");
                        printf("�˳�¼���𣿰�Q/Y/Esc�˳���");
                        char quit=getch();
                        if(quit=='q'||quit=='Q'||quit=='Y'||quit=='y'||quit==27)
                        {
                            break;
                        }
                        continue;
                    }
                    fflush(stdin);
                    student->score_vector_.push_back(Score(input_subject,input_mark,id_));
                    printf("����ɹ���\n");
                    printf("�˳�¼���𣿰�Q/Y/Esc�˳���");
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

        case'2':    //�޸�ѧ���ɼ�
        {
            uint64_t input_id=GetId("������ѧ����ѧ��:");
            if(input_id==0)
            {
                printf("�������");
                Wait();
                break;
            }
            else
            {
                if(admin->FindStudent(input_id)==NULL)
                {
                    printf("ѧ��δ�ҵ���\n");
                    Wait();
                    break;
                }
                else
                {
                    printf("���������޸ĵĿ�Ŀ:");
                    char input_subject[MAX_SUBJECT_NAME_LENGTH]={'\0'};
                    if(GetString(input_subject,MAX_SUBJECT_NAME_LENGTH)==NULL)
                    {
                        printf("�������");
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
                                printf("�������޸ĺ�ķ���:");
                                double input_mark;
                                if(scanf("%lf",&input_mark)==0)
                                {
                                    printf("�������");
                                    Wait();
                                }
                                else
                                {
                                    iter->mark_=input_mark;
                                    printf("����ɹ���");
                                    Wait();
                                }

                            }
                        }
                        if(found==0)
                        {
                            printf("δ�ҵ��ÿ�Ŀ��");
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

        case'3':    //ɾ��ѧ���ɼ�
        {
            uint64_t input_id=GetId("������ѧ�����:");
            if(admin->FindStudent(input_id)==NULL)
            {
                printf("ѧ��δ�ҵ���");
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
                    printf("��ѧ���ļ�¼��û����¼��ĳɼ���");
                    Wait();
                    break;
                }
                else
                {
                    for(size_t i=0;i<found.size();++i)
                    {
                        printf("%4u.\t��Ŀ:%s\t����:%g\n",i+1,found[i].subject_,found[i].mark_);
                    }
                    size_t sub=0;
                    printf("��ѡ��Ҫɾȥ�Ŀ�Ŀ:");
                    if(scanf("%u",&sub)==0||sub==0||sub>found.size())
                    {
                        printf("�������");
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
                                printf("�ɹ�ɾ����Ŀ %s ��",found[sub-1].subject_);
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

        case'4':    //�޸ĵ�¼����
        {
            printf("������ԭ��������:");
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
                printf("�������");
                Wait();
                Wait();
                break;
            }

            printf("�������µ�����:");
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
            printf("���ٴ�����������ȷ��:");
            char password_check[25]={'\0'};  //24�ֽ����뾭��Hash��Ϊ64λ��������
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
                printf("�����޸ĳɹ���");
                Wait();
                Wait();
                break;
            }
            else
            {
                printf("������������벻����");
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
            printf("�������");
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
