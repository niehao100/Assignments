#include<cerrno>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>

#include"admin.h"
#include"score.h"
#include"student.h"
#include"teacher.h"
#include"user.h"

using namespace std;

inline uint64_t GenerateRandomPassword(char pwd[21])
{
    for(int i=0;i<20;++i)
    {
        pwd[i]=char(double(rand())/RAND_MAX*(0x7F-0x21))+0x21;
    }
    pwd[20]='\0';
    return Hash(pwd);
}

Admin::Admin(const char* buffer,size_t size):
    User(NULL,0,0),Student(NULL,0,0,vector<Score>()),Teacher(NULL,0,0),teacher_vector_(),student_vector_(),admin_id_set_()
{
    if(ReadFrom(buffer,size)==0)
    {
        errno=EIO;
        perror("Initialization error");
        Pause();
    }
}

size_t Admin::WriteTo(char* buffer,size_t size)
{
    char* buffer_init=buffer;
    if(buffer==NULL)
    {
        buffer+=sizeof(uint64_t);
        buffer+=sizeof(vector<Teacher>::size_type);

        for(vector<Teacher>::iterator iter=teacher_vector_.begin();iter!=teacher_vector_.end();++iter)
        {

            buffer+=sizeof(size_t);
            buffer+=iter->WriteTo(NULL,0);
        }

        buffer+=sizeof(vector<Student>::size_type);

        for(vector<Student>::iterator iter=student_vector_.begin();iter!=student_vector_.end();++iter)
        {
            buffer+=sizeof(size_t);
            buffer+=iter->WriteTo(NULL,0);
        }
    }
    else
    {
        if(sizeof(uint64_t)+sizeof(vector<Teacher>::size_type)+teacher_vector_.size()*(sizeof(size_t))+student_vector_.size()*(sizeof(size_t))>size)
        {
            return 0;
        }
        for(size_t i=0;i<sizeof(uint64_t);++i)
        {
            buffer[i]=((char*)(&hash_))[i];
        }
        buffer+=sizeof(uint64_t);

        vector<Teacher>::size_type teacher_vector_size=teacher_vector_.size();
        for(size_t i=0;i<sizeof(teacher_vector_size);++i)
        {
            buffer[i]=((char*)(&teacher_vector_size))[i];
        }
        buffer+=sizeof(teacher_vector_size);

        for(vector<Teacher>::iterator iter=teacher_vector_.begin();iter!=teacher_vector_.end();++iter)
        {
            size_t write_size=iter->WriteTo(NULL,0);
            for(size_t i=0;i<sizeof(size_t);++i)
            {
                buffer[i]=((char*)(&write_size))[i];
            }
            buffer+=sizeof(size_t);

            iter->WriteTo(buffer,iter->WriteTo(NULL,0));
            buffer+=iter->WriteTo(NULL,0);
        }

        vector<Student>::size_type student_vector_size=student_vector_.size();
        for(size_t i=0;i<sizeof(student_vector_size);++i)
        {
            buffer[i]=((char*)(&student_vector_size))[i];
        }
        buffer+=sizeof(student_vector_size);

        for(vector<Student>::iterator iter=student_vector_.begin();iter!=student_vector_.end();++iter)
        {
            size_t write_size=iter->WriteTo(NULL,0);
            for(size_t i=0;i<sizeof(size_t);++i)
            {
                buffer[i]=((char*)(&write_size))[i];
            }
            buffer+=sizeof(size_t);

            iter->WriteTo(buffer,iter->WriteTo(NULL,0));
            buffer+=iter->WriteTo(NULL,0);
        }
    }
    return buffer-buffer_init;
}

size_t Admin::ReadFrom(const char* buffer,size_t size)
{
    const char* buffer_init=buffer;
    if(size<sizeof(uint64_t)+sizeof(vector<Teacher>::size_type)+sizeof(vector<Student>::size_type))
    {
        return 0;
    }

    for(size_t i=0;i<sizeof(uint64_t);++i)
    {
        ((char*)(&hash_))[i]=buffer[i];
    }
    buffer+=sizeof(uint64_t);

    vector<Teacher>::size_type teacher_vector_size;
    for(size_t i=0;i<sizeof(teacher_vector_size);++i)
    {
        ((char*)(&teacher_vector_size))[i]=buffer[i];
    }
    buffer+=sizeof(teacher_vector_size);

    teacher_vector_.clear();
    for(size_t iter=0;iter<teacher_vector_size;++iter)
    {
        size_t read_size;
        for(size_t i=0;i<sizeof(read_size);++i)
        {
            ((char*)(&read_size))[i]=buffer[i];
        }
        buffer+=sizeof(read_size);

        AddTeacher(Teacher(buffer,read_size));
        buffer+=read_size;
    }

    vector<Student>::size_type student_vector_size;
    for(size_t i=0;i<sizeof(student_vector_size);++i)
    {
        ((char*)(&student_vector_size))[i]=buffer[i];
    }
    buffer+=sizeof(student_vector_size);

    student_vector_.clear();
    for(size_t iter=0;iter<student_vector_size;++iter)
    {
        size_t read_size;
        for(size_t i=0;i<sizeof(read_size);++i)
        {
            ((char*)(&read_size))[i]=buffer[i];
        }
        buffer+=sizeof(read_size);

        AddStudent(Student(buffer,read_size));
        buffer+=read_size;
    }

    return buffer-buffer_init;
}

int Admin::AddTeacher(const Teacher& add)
{
    if(admin_id_set_.count(add.id_)!=0)
    {
        return 0;
    }
    teacher_vector_.push_back(add);
    admin_id_set_.insert(add.id_);
    return 1;
}

int Admin::AddStudent(const Student& add)
{
    if(admin_id_set_.count(add.id_)!=0)
    {
        return 0;
    }
    student_vector_.push_back(add);
    admin_id_set_.insert(add.id_);
    return 1;
}

int Admin::UpdateTeacher(const Teacher& update)
{
    if(admin_id_set_.count(update.id_)==0)
    {
        return 0;
    }
    for(vector<Teacher>::iterator iter=teacher_vector_.begin();iter!=teacher_vector_.end();++iter)
    {
        if(iter->id_==update.id_)
        {
            *iter=update;
            return 1;
        }
    }
    return 0;
}

int Admin::UpdateStudent(const Student& update)
{
    if(admin_id_set_.count(update.id_)==0)
    {
        return 0;
    }
    for(vector<Student>::iterator iter=student_vector_.begin();iter!=student_vector_.end();++iter)
    {
        if(iter->id_==update.id_)
        {
            *iter=update;
            return 1;
        }
    }
    return 0;
}

int Admin::DeleteTeacher(uint64_t del)
{
    if(admin_id_set_.count(del)==0)
    {
        return 0;
    }
    for(vector<Teacher>::iterator iter=teacher_vector_.begin();iter!=teacher_vector_.end();++iter)
    {
        if(iter->id_==del)
        {
            teacher_vector_.erase(iter);
            return 1;
        }
    }
    return 0;
}

int Admin::DeleteStudent(uint64_t del)
{
    if(admin_id_set_.count(del)==0)
    {
        return 0;
    }
    for(vector<Student>::iterator iter=student_vector_.begin();iter!=student_vector_.end();++iter)
    {
        if(iter->id_==del)
        {
            student_vector_.erase(iter);
            return 1;
        }
    }
    return 0;
}

int Admin::Manage()
{
    bool init=true;
    for(;;)
    {
        system("cls");
        printf("*******************************���������:����Ա********************************");
        if(init)
        {
            printf("��ӭ����ʹ�ã�");
            Wait();
            init=false; //ֻ��ʾһ�λ�ӭ��Ϣ;
        }
        putchar('\r');
        printf("��ѡ����ʹ�õĹ���:\n    1.����û�\n    2.�޸��û���Ϣ\n    3.ɾ�������û�\n    4.�޸Ĺ���Ա��¼����\n    B.�˳���¼\n    Q.�˳�����\n");
        char choice=getch();

        switch(choice)
        {
        case'1':    //����û�

            for(bool stop=false;!stop;)
            {
                system("cls");
                printf("*******************************���������:����Ա********************************");
                printf("��ѡ��������豸:\n    1.�Ӹ�ʽ���ļ���ȡ\n    2.�Ӽ�������\n    B.������һ��˵�\n    Q.�˳�����\n");
                choice=getch();
                FILE* input_file=NULL,*output_file=NULL;
                char input_line[MAX_NAME_LENGTH+20+20];  //��Ԥ��20���ַ��ռ�
                char t_or_s='\0';

                char input_name[MAX_NAME_LENGTH];
                uint64_t input_id;
                char random_password[21];
                int counter=0;
                time_t time_ptr;

                switch(choice)
                {
                case'1':
                    printf("T.��ʦ\tS.ѧ��");
                    t_or_s=getch();
                    putchar('\r');
                    if(t_or_s!='T'&&t_or_s!='t'&&t_or_s!='S'&&t_or_s!='s')
                    {
                        printf("�������                                       \n");
                        Wait();
                        break;
                    }
                    printf("�������ļ�������·��:");
                    char path[MAX_PATH+1];
                    gets(path);
                    input_file=fopen(path,"r");
                    if(input_file==NULL)
                    {
                        if(errno==ENOENT)
                        {
                            printf("�ļ�������!\n");
                            Wait();
                            break;
                        }
                        else
                        {
                            perror("Failed to open the file");
                            Wait();
                            Wait();
                            break;
                        }
                    }
                    else
                    {
                        output_file=fopen("initial_password.of.txt","a+");
                        if(output_file==NULL)
                        {
                            perror("Failed to open output file \"initial_password.of.txt\"");
                            Wait();
                            break;
                        }
                        srand(time(&time_ptr));
                        if(t_or_s=='t'||t_or_s=='T')
                        {
                            counter=0;
                            for(;fgets(input_line,MAX_NAME_LENGTH+20+20,input_file);)
                            {
                                sscanf(input_line,"%s%llu",input_name,&input_id);
                                //��ʼ�����������
                                if(AddTeacher(Teacher(input_name,input_id,GenerateRandomPassword(random_password))))
                                {
                                    //������initial_password.of.txt
                                    fprintf(output_file,"%s\t%llu\t%s\n",input_name,input_id,random_password);
                                    ++counter;
                                }
                            }
                            if(counter>0)
                            {

                                printf("�ɹ���ȡ%d���û���Ϣ���ѽ���ʼ���뱣����\"initial_password.of.txt\"\n",counter);
                            }
                            else
                            {
                                printf("û�ж�ȡ�κ��û���Ϣ��");
                            }
                            Wait();
                            Wait();
                        }
                        if(t_or_s=='s'||t_or_s=='S')
                        {
                            counter=0;
                            for(;fgets(input_line,MAX_NAME_LENGTH+20+20,input_file);)
                            {
                                sscanf(input_line,"%s%llu",input_name,&input_id);
                                //��ʼ�����������
                                if(AddStudent(Student(input_name,input_id,GenerateRandomPassword(random_password),vector<Score>())))
                                {
                                    //������initial_password.of.txt
                                    fprintf(output_file,"%s\t%llu\t%s\n",input_name,input_id,random_password);
                                    ++counter;
                                }
                            }
                            if(counter>0)
                            {

                                printf("�ɹ���ȡ%d���û���Ϣ���ѽ���ʼ���뱣����\"initial_password.of.txt\"\n",counter);
                            }
                            else
                            {
                                printf("û�ж�ȡ�κ��û���Ϣ��");
                            }
                            Wait();
                            Wait();
                        }
                        if(counter>0)
                        {
                            fprintf(output_file,"Generated @ %s\n",ctime(&time_ptr));
                        }
                        fclose(input_file);
                        fclose(output_file);

                    }
                    break;
                case'2':
                    printf("T.��ʦ\tS.ѧ��");
                    t_or_s=getch();
                    putchar('\r');
                    if(t_or_s!='T'&&t_or_s!='t'&&t_or_s!='S'&&t_or_s!='s')
                    {
                        printf("�������                                       \n");
                        Wait();
                        break;
                    }

                    printf("����������:   ");
                    putchar(8);
                    putchar(8);
                    putchar(8);
                    if(fgets(input_name,MAX_NAME_LENGTH,stdin)==NULL)
                    {
                        perror("Failed to read the name");
                        Pause();
                        break;
                    }

                    for(int i=0;i<MAX_NAME_LENGTH;++i)
                    {
                        if(input_name[MAX_NAME_LENGTH-1-i]=='\n')
                        {
                            input_name[MAX_NAME_LENGTH-1-i]='\0';
                            break;
                        }
                    }

                    printf("��������:");
                    if(scanf("%llu",&input_id)==0)
                    {
                        printf("�������");
                        Wait();
                        break;
                    }
                    if(ferror(stdin))
                    {
                        perror("Failed to read the id");
                        Pause();
                        break;
                    }

                    if(admin_id_set_.count(input_id)!=0)
                    {
                        printf("����ظ���");
                        Wait();
                        Wait();
                        break;
                    }

                    printf("���������룬ֱ�ӻس���ʹ�������ʼ������:");
                    fflush(stdin);
                    if(fgets(random_password,21,stdin)==NULL)
                    {
                        perror("Unexpected input error");
                        Pause();
                        break;
                    }
                    if(random_password[0]=='\n')
                    {
                        GenerateRandomPassword(random_password);
                    }
                    else
                    {
                        for(int i=0;i<21;++i)
                        {
                            if(random_password[21-1-i]=='\n')
                            {
                                random_password[21-1-i]='\0';
                                break;
                            }
                        }

                    }

                    output_file=fopen("initial_password.of.txt","a+");
                    time(&time_ptr);
                    switch(t_or_s)
                    {
                    case't':case'T':
                        if(AddTeacher(Teacher(input_name,input_id,GenerateRandomPassword(random_password))))
                        {
                            printf("�ѱ��档\n");
                            //������initial_password.of.txt
                            fprintf(output_file,"%s\t%llu\t%s\n",input_name,input_id,random_password);
                            fprintf(output_file,"Generated @ %s\n",ctime(&time_ptr));
                            Wait();
                        }
                        break;
                    case's':case'S':
                        if(AddStudent(Student(input_name,input_id,GenerateRandomPassword(random_password),vector<Score>())))
                        {
                            printf("�ѱ��档\n");
                            //������initial_password.of.txt
                            fprintf(output_file,"%s\t%llu\t%s\n",input_name,input_id,random_password);
                            fprintf(output_file,"Generated @ %s\n",ctime(&time_ptr));
                            Wait();
                        }
                        break;
                    default:
                        perror("Unexpected result");
                    }
                    fclose(output_file);

                    break;

                case'B':case'b':case 27:
                    stop=true;
                    break;
                case'Q':case'q':
                    extern bool go_on;
                    go_on=false;
                    return 0;
                }
            }
            break;
        case'2':    //�޸��û���Ϣ
            for(bool stop=false;!stop;)
            {
                system("cls");
                printf("*******************************���������:����Ա********************************");
                printf("��ѡ��Ҫ�޸ĵ���Ŀ:\n    1.�޸��û�����\n    2.�޸��û����\n    3.�����û�����\n    4.���û���ݵ�¼\n    B.������һ��˵�\n    Q.�˳�����\n");

                char choice=getch();
                uint64_t input_id=0,new_id=0;
                char input_name[MAX_NAME_LENGTH];
                char random_password[21];
                FILE* output_file=NULL;
                time_t time_ptr;


                switch(choice)
                {
                case'1':    //�޸��û�����
                    printf("�������û����:");
                    if(scanf("%llu",&input_id)==0)
                    {
                        printf("�������");
                        Wait();
                        break;
                    }
                    if(ferror(stdin))
                    {
                        perror("Failed to read the id");
                        Pause();
                        break;
                    }

                    if(admin_id_set_.count(input_id)==0)
                    {
                        printf("��Ų����ڡ�");
                        Wait();
                        Wait();
                        break;
                    }
                    else
                    {
                        printf("    ��ע�⣬�û����ظ������ܵ����޷�ʹ��������¼ϵͳ����ʱֻ��ʹ�ñ�ŵ�¼��\n�������µ��û���:");
                        fflush(stdin);
                        if(fgets(input_name,MAX_NAME_LENGTH,stdin)==NULL)
                        {
                            perror("Failed to read the name");
                            Pause();
                            break;
                        }

                        for(int i=0;i<MAX_NAME_LENGTH;++i)      //fgets�Ὣ���ж���ȥ
                        {
                            if(input_name[MAX_NAME_LENGTH-1-i]=='\n')
                            {
                                input_name[MAX_NAME_LENGTH-1-i]='\0';
                                break;
                            }
                        }

                        if(FindTeacher(input_id)!=NULL)
                        {
                            strcpy(FindTeacher(input_id)->name_,input_name);
                            printf("�޸ĳɹ���");
                            Wait();
                            break;
                        }
                        if(FindStudent(input_id)!=NULL)
                        {
                            strcpy(FindStudent(input_id)->name_,input_name);
                            printf("�޸ĳɹ���");
                            Wait();
                            break;
                        }
                        break;
                    }
                    break;
                case'2':    //�޸��û����
                    printf("�������û�ԭ�еı��:");
                    if(scanf("%llu",&input_id)==0)
                    {
                        printf("�������");
                        Wait();
                        break;
                    }
                    if(ferror(stdin))
                    {
                        perror("Failed to read the id");
                        Pause();
                        break;
                    }

                    if(admin_id_set_.count(input_id)==0)
                    {
                        printf("��Ų����ڡ�");
                        Wait();
                        Wait();
                        break;
                    }
                    else
                    {
                        printf("    ��ע�⣬��Ų������ظ���\n�������µ��û����:");
                        fflush(stdin);
                        if(scanf("%llu",&new_id)==0)
                        {
                            printf("�������");
                            Wait();
                            break;
                        }
                        if(ferror(stdin))
                        {
                            perror("Failed to read the id");
                            Pause();
                            break;
                        }

                        if(admin_id_set_.count(new_id)!=0)
                        {
                            printf("����ظ���");
                            Wait();
                            Wait();
                            break;
                        }
                        else
                        {

                            if(FindTeacher(input_id)!=NULL)
                            {
                                Teacher* teacher_ptr=FindTeacher(input_id);
                                admin_id_set_.erase(teacher_ptr->id_);
                                teacher_ptr->id_=new_id;
                                admin_id_set_.insert(teacher_ptr->id_);
                                printf("�޸ĳɹ���");
                                Wait();
                                break;
                            }
                            if(FindStudent(input_id)!=NULL)
                            {
                                Student* student_ptr=FindStudent(input_id);
                                admin_id_set_.erase(student_ptr->id_);
                                student_ptr->id_=new_id;
                                admin_id_set_.insert(student_ptr->id_);
                                printf("�޸ĳɹ���");
                                Wait();
                                break;
                            }
                            break;
                        }
                        break;
                    }
                    break;

                case'3':    //�����û�����
                    printf("�������û����:");
                    if(scanf("%llu",&input_id)==0)
                    {
                        printf("�������");
                        Wait();
                        break;
                    }
                    if(ferror(stdin))
                    {
                        perror("Failed to read the id");
                        Pause();
                        break;
                    }

                    if(admin_id_set_.count(input_id)==0)
                    {
                        printf("��Ų����ڡ�");
                        Wait();
                        Wait();
                        break;
                    }
                    else
                    {
                        printf("���������룬ֱ�ӻس���ʹ�������ʼ������:");
                        fflush(stdin);
                        if(fgets(random_password,21,stdin)==NULL)
                        {
                            perror("Unexpected input error");
                            Pause();
                            break;
                        }
                        if(random_password[0]=='\n')
                        {
                            GenerateRandomPassword(random_password);
                        }
                        else
                        {
                            for(int i=0;i<21;++i)
                            {
                                if(random_password[21-1-i]=='\n')
                                {
                                    random_password[21-1-i]='\0';
                                    break;
                                }
                            }

                        }

                        output_file=fopen("initial_password.of.txt","a+");
                        time(&time_ptr);

                        printf("�ѱ��档\n");
                        //������initial_password.of.txt
                        if(FindTeacher(input_id)!=NULL)
                        {
                            fprintf(output_file,"%s\t%llu\t%s\n",FindTeacher(input_id)->name_,input_id,random_password);
                            fprintf(output_file,"Generated @ %s\n",ctime(&time_ptr));
                            Wait();
                        }
                        if(FindStudent(input_id)!=NULL)
                        {
                            fprintf(output_file,"%s\t%llu\t%s\n",FindStudent(input_id)->name_,input_id,random_password);
                            fprintf(output_file,"Generated @ %s\n",ctime(&time_ptr));
                            Wait();
                        }

                        fclose(output_file);
                    }
                    break;

                case'4':    //���û���ݵ�¼
                    printf("�������û����:");
                    if(scanf("%llu",&input_id)==0)
                    {
                        printf("�������");
                        Wait();
                        break;
                    }
                    if(ferror(stdin))
                    {
                        perror("Failed to read the id");
                        Pause();
                        break;
                    }

                    if(admin_id_set_.count(input_id)==0)
                    {
                        printf("��Ų����ڡ�");
                        Wait();
                        Wait();
                        break;
                    }
                    else
                    {
                        if(FindTeacher(input_id)!=NULL)
                        {
                            FindTeacher(input_id)->Login(this);
                            break;
                        }
                        if(FindStudent(input_id)!=NULL)
                        {
                            FindStudent(input_id)->Login(this);
                            break;
                        }
                        break;
                    }
                    break;
                case'B':case'b':case 27:
                    stop=true;
                    break;
                case'Q':case'q':
                    extern bool go_on;
                    go_on=false;
                    return 0;
                default:
                    printf("�������");
                    Wait();
                    break;
                }
            }
            break;
        case'3':    //ɾ�������û�
            for(;;)
            {
                uint64_t input_id=0;

                printf("�������û����:");
                if(scanf("%llu",&input_id)==0)
                {
                    printf("�������");
                    Wait();
                    break;
                }
                if(ferror(stdin))
                {
                    perror("Failed to read the id");
                    Pause();
                    break;
                }
                fflush(stdin);
                if(admin_id_set_.count(input_id)==0)
                {
                    printf("��Ų����ڡ�");
                    Wait();
                    Wait();
                    break;
                }
                else
                {
                    if(DeleteTeacher(input_id)||DeleteStudent(input_id))
                    {
                        printf("ɾ���ɹ���");
                        Wait();
                        break;
                    }
                    else
                    {
                        perror("Unexpected result");
                        Pause();
                        break;
                    }
                }
            }
            break;

        case'4':    //�޸Ĺ���Ա��¼����
            {
                printf("������ԭ��������:");
                char password_char[25]={'\0'};  //24�ֽ����뾭��Hash��Ϊ64λ��������
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
        }
    }

    perror("Unexpected result");
    Pause();

    return 0;
}

Teacher* Admin::FindTeacher(char name[MAX_NAME_LENGTH])
{
    for(vector<Teacher>::iterator iter=teacher_vector_.begin();iter!=teacher_vector_.end();++iter)
    {
        if(strcmp(name,iter->name_)==0)
        {
            return &(*iter);
        }
    }
    return NULL;
}

Teacher* Admin::FindTeacher(uint64_t id)
{
    for(vector<Teacher>::iterator iter=teacher_vector_.begin();iter!=teacher_vector_.end();++iter)
    {
        if(id==iter->id_)
        {
            return &(*iter);
        }
    }
    return NULL;
}
Student* Admin::FindStudent(char name[MAX_NAME_LENGTH])
{
    for(vector<Student>::iterator iter=student_vector_.begin();iter!=student_vector_.end();++iter)
    {
        if(strcmp(name,iter->name_)==0)
        {
            return &(*iter);
        }
    }
    return NULL;
}
Student* Admin::FindStudent(uint64_t id)
{
    for(vector<Student>::iterator iter=student_vector_.begin();iter!=student_vector_.end();++iter)
    {
        if(id==iter->id_)
        {
            return &(*iter);
        }
    }
    return NULL;
}
