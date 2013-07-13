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
            for(size_t i=0;i<sizeof(write_size);++i)
            {
                buffer[i]=((char*)(&write_size))[i];
            }
            buffer+=sizeof(write_size);

            buffer+=iter->WriteTo(buffer,iter->WriteTo(NULL,0));
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
            for(size_t i=0;i<sizeof(write_size);++i)
            {
                buffer[i]=((char*)(&write_size))[i];
            }
            buffer+=sizeof(write_size);

            buffer+=iter->WriteTo(buffer,iter->WriteTo(NULL,0));
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
        size_t read_size=0;
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
        printf("*******************************您的身份是:管理员********************************");
        if(init)
        {
            printf("欢迎您的使用！");
            Wait();
            init=false; //只显示一次欢迎信息;
        }
        putchar('\r');
        printf("请选择欲使用的功能:                     \n    1.添加用户\n    2.修改用户信息\n    3.删除已有用户\n    4.修改管理员登录密码\n    B.退出登录\n    Q.退出程序\n");
        char choice=getch();

        switch(choice)
        {
        case'1':    //添加用户

            for(bool stop=false;!stop;)
            {
                system("cls");
                printf("*******************************您的身份是:管理员********************************");
                printf("请选择输入的设备:\n    1.从格式化文件读取\n    2.从键盘输入\n    B.返回上一层菜单\n    Q.退出程序\n");
                choice=getch();
                FILE* input_file=NULL,*output_file=NULL;
                char input_line[MAX_NAME_LENGTH+20+20];  //多预留20个字符空间
                char t_or_s='\0';

                char input_name[MAX_NAME_LENGTH];
                uint64_t input_id;
                char random_password[21];
                int counter=0;
                time_t time_ptr;

                switch(choice)
                {
                case'1':
                    printf("T.老师\tS.学生");
                    t_or_s=getch();
                    putchar('\r');
                    if(t_or_s!='T'&&t_or_s!='t'&&t_or_s!='S'&&t_or_s!='s')
                    {
                        printf("输入错误。                                       \n");
                        Wait();
                        break;
                    }
                    printf("请输入文件的完整路径:");
                    char path[MAX_PATH+1];
                    gets(path);
                    input_file=fopen(path,"r");
                    if(input_file==NULL)
                    {
                        if(errno==ENOENT)
                        {
                            printf("文件不存在!\n");
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
                                //初始密码随机产生
                                if(AddTeacher(Teacher(input_name,input_id,GenerateRandomPassword(random_password))))
                                {
                                    //保存至initial_password.of.txt
                                    fprintf(output_file,"%s\t%llu\t%s\n",input_name,input_id,random_password);
                                    ++counter;
                                }
                            }
                            if(counter>0)
                            {

                                printf("成功读取%d条用户信息；已将初始密码保存至\"initial_password.of.txt\"\n",counter);
                            }
                            else
                            {
                                printf("没有读取任何用户信息。");
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
                                //初始密码随机产生
                                if(AddStudent(Student(input_name,input_id,GenerateRandomPassword(random_password),vector<Score>())))
                                {
                                    //保存至initial_password.of.txt
                                    fprintf(output_file,"%s\t%llu\t%s\n",input_name,input_id,random_password);
                                    ++counter;
                                }
                            }
                            if(counter>0)
                            {

                                printf("成功读取%d条用户信息；已将初始密码保存至\"initial_password.of.txt\"\n",counter);
                            }
                            else
                            {
                                printf("没有读取任何用户信息。");
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
                    printf("T.老师\tS.学生");
                    t_or_s=getch();
                    putchar('\r');
                    if(t_or_s!='T'&&t_or_s!='t'&&t_or_s!='S'&&t_or_s!='s')
                    {
                        printf("输入错误。                                       \n");
                        Wait();
                        break;
                    }

                    printf("请输入姓名:   ");
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

                    printf("请输入编号:");
                    if(scanf("%llu",&input_id)==0)
                    {
                        printf("输入错误。");
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
                        printf("编号重复。");
                        Wait();
                        Wait();
                        break;
                    }

                    printf("请输入密码，直接回车则使用随机初始化密码:");
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
                            printf("已保存。\n");
                            //保存至initial_password.of.txt
                            fprintf(output_file,"%s\t%llu\t%s\n",input_name,input_id,random_password);
                            fprintf(output_file,"Generated @ %s\n",ctime(&time_ptr));
                            Wait();
                        }
                        break;
                    case's':case'S':
                        if(AddStudent(Student(input_name,input_id,GenerateRandomPassword(random_password),vector<Score>())))
                        {
                            printf("已保存。\n");
                            //保存至initial_password.of.txt
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
        case'2':    //修改用户信息
            for(bool stop=false;!stop;)
            {
                system("cls");
                printf("*******************************您的身份是:管理员********************************");
                printf("请选择要修改的项目:\n    1.修改用户姓名\n    2.修改用户编号\n    3.重置用户密码\n    4.以用户身份登录\n    B.返回上一层菜单\n    Q.退出程序\n");

                char choice=getch();
                uint64_t input_id=0,new_id=0;
                char input_name[MAX_NAME_LENGTH];
                char random_password[21];
                FILE* output_file=NULL;
                time_t time_ptr;


                switch(choice)
                {
                case'1':    //修改用户姓名
                    printf("请输入用户编号:");
                    if(scanf("%llu",&input_id)==0)
                    {
                        printf("输入错误。");
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
                        printf("编号不存在。");
                        Wait();
                        Wait();
                        break;
                    }
                    else
                    {
                        printf("    请注意，用户名重复将可能导致无法使用姓名登录系统，届时只能使用编号登录。\n请输入新的用户名:");
                        fflush(stdin);
                        if(fgets(input_name,MAX_NAME_LENGTH,stdin)==NULL)
                        {
                            perror("Failed to read the name");
                            Pause();
                            break;
                        }

                        for(int i=0;i<MAX_NAME_LENGTH;++i)      //fgets会将换行读进去
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
                            printf("修改成功。");
                            Wait();
                            break;
                        }
                        if(FindStudent(input_id)!=NULL)
                        {
                            strcpy(FindStudent(input_id)->name_,input_name);
                            printf("修改成功。");
                            Wait();
                            break;
                        }
                        break;
                    }
                    break;
                case'2':    //修改用户编号
                    printf("请输入用户原有的编号:");
                    if(scanf("%llu",&input_id)==0)
                    {
                        printf("输入错误。");
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
                        printf("编号不存在。");
                        Wait();
                        Wait();
                        break;
                    }
                    else
                    {
                        printf("    请注意，编号不可以重复。\n请输入新的用户编号:");
                        fflush(stdin);
                        if(scanf("%llu",&new_id)==0)
                        {
                            printf("输入错误。");
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
                            printf("编号重复。");
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
                                printf("修改成功。");
                                Wait();
                                break;
                            }
                            if(FindStudent(input_id)!=NULL)
                            {
                                Student* student_ptr=FindStudent(input_id);
                                admin_id_set_.erase(student_ptr->id_);
                                student_ptr->id_=new_id;
                                admin_id_set_.insert(student_ptr->id_);
                                printf("修改成功。");
                                Wait();
                                break;
                            }
                            break;
                        }
                        break;
                    }
                    break;

                case'3':    //重置用户密码
                    printf("请输入用户编号:");
                    if(scanf("%llu",&input_id)==0)
                    {
                        printf("输入错误。");
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
                        printf("编号不存在。");
                        Wait();
                        Wait();
                        break;
                    }
                    else
                    {
                        printf("请输入密码，直接回车则使用随机初始化密码:");
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

                        printf("已保存。\n");
                        //保存至initial_password.of.txt
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

                case'4':    //以用户身份登录
                    printf("请输入用户编号:");
                    if(scanf("%llu",&input_id)==0)
                    {
                        printf("输入错误。");
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
                        printf("编号不存在。");
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
                    printf("输入错误。");
                    Wait();
                    break;
                }
            }
            break;
        case'3':    //删除已有用户
            for(;;)
            {
                uint64_t input_id=0;

                printf("请输入用户编号:");
                if(scanf("%llu",&input_id)==0)
                {
                    printf("输入错误。");
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
                    printf("编号不存在。");
                    Wait();
                    Wait();
                    break;
                }
                else
                {
                    if(DeleteTeacher(input_id)||DeleteStudent(input_id))
                    {
                        printf("删除成功。");
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

        case'4':    //修改管理员登录密码
            {
                printf("请输入原来的密码:");
                char password_char[25]={'\0'};  //24字节密码经过Hash变为64位整数储存
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
