#include<cstdlib>
#include<cstring>
#include<ctime>

#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>

#include<conio.h>

#include"manager.h"
#include"technician.h"
#include"salesman.h"
#include"salemanager.h"

using namespace std;

enum Type
{
    kEmployee=1,
    kManager=2,
    kSalemanager=3,
    kSalesman=4,
    kTechnician=5
}read_type;

struct Object
{
    Type type;
    void* pointer;
}object_struct;

int Input();
int Modify();
int Search();

int LoadData(const char* filename="save.dat");
int SaveData(const char* filename="save.dat");

vector<Object> data;
typedef vector<Object> Data;

inline void Pause()
{
    fflush(stdin);
    cin.clear();
    cin.sync();
    getch();

}
inline void Wait()
{
    fflush(stdin);
    cin.clear();
    cin.sync();
    time_t start,current;
    time(&start);
    for(time(&current);current-start<1.0;time(&current));
}

int main()
{
    #ifdef _MSC_VER
    #include<cstdlib>
    system("title GNU C++ please!");
    cerr<<"全部代码使用Code::Blocks测试通过.\n如果出现问题请您首先考虑使用标准的GCC.\nAll codes tested in Code::Blocks with minGW successfully.\nIf anything goes wrong, consider standard GCC first.\n";
    system("pause");
    system("cls");
    #endif

    system("title 犀利人事管理系统");
    cout<<"       00000000000000000000000000                   100          000\n       00000000000000000000000001              00000000          100\n       001                    00        00000000000000            00\n\
       001                    00         00000 000                00\n       00000000000000000000000001              000         000    00\n       00            000                       000         000    00\n       00    000     000      000              000         000    00\n       00    100000  000  00000001     000000000000000000  000    00\n       00        0   000   00          000000000000000000  000    00\n       00         0  000   0                   000         000    00\n       00  00000000  000  000000              00000        000    00\n       00   001               000            0000000       000    00\n      000      000   000                    0000000000     000    00\n      000     000    000                   1001000 0000    000    00\n      000    00000000000000000000          000 000  1000   000    00\n      00    000      000                 0000  000   1     000    00\n     000    00       000                0000   000         000    00\n     000             000               0000    000                00\n     00   0000000000000000000000000     00     000                00\n    000              000                       000                00\n   0000              000                       000               000\n    00               000                       000            000000\n                     000                       000            0000\n";
    if(LoadData())
    {
        Pause();
        return -1;
    }
    Wait();
    Wait();
    for(;;)
    {
        system("cls");
        cout<<"               #,  #=  #:      #                             #\n                #  ##  #       #                             #\n                #  ##  #  ###  #  W##:  ###  Y=## ##B  ###   #\n                # # B ,R #   # #  #  # #   # I#  #  # #   #  #\n                :Y#  ##  ##### # #     #   # I;  #  # #####  #\n                 ##  ##  #     # iB  ; #   # I;  #  # #\n                 #   ##   #,#V #  #RB#  #:#i I+  #  #  #,#X .#\n";
        cout<<"请选择欲使用的功能:\n";
        cout<<"    1.数据录入\n";
        cout<<"    2.数据修改\n";
        cout<<"    3.数据查询\n";
        cout<<"    Q.退出\n";

        fflush(stdin);
        switch(getch())
        {
        case '1':
            Input();
            break;
        case '2':
            Modify();
            break;
        case '3':
            Search();
            break;
        case 'Q':case 'q':
            SaveData();
            for(Data::iterator iter=data.begin();iter!=data.end();++iter)
            {
                switch(iter->type)
                {
                case kEmployee:
                    delete ((Employee*)(iter->pointer));
                    break;
                case kManager:
                    delete ((Manager*)(iter->pointer));
                    break;
                case kSalemanager:
                    delete ((Salemanager*)(iter->pointer));
                    break;
                case kSalesman:
                    delete ((Salesman*)(iter->pointer));
                    break;
                case kTechnician:
                    delete ((Technician*)(iter->pointer));
                    break;
                default:
                    cerr<<"数据结构错误。\n";
                    Pause();
                    break;
                }
            }
            cout<<"感谢您的使用，再见。\n";
            Wait();
            system("cls");
            return 0;
        default:
            cerr<<"对不起，输入错误；请重新输入。";
            Wait();
            break;
        }
        fflush(stdin);
    }
    SaveData();
    for(Data::iterator iter=data.begin();iter!=data.end();++iter)
    {
        switch(iter->type)
        {
        case kEmployee:
            delete ((Employee*)(iter->pointer));
            break;
        case kManager:
            delete ((Manager*)(iter->pointer));
            break;
        case kSalemanager:
            delete ((Salemanager*)(iter->pointer));
            break;
        case kSalesman:
            delete ((Salesman*)(iter->pointer));
            break;
        case kTechnician:
            delete ((Technician*)(iter->pointer));
            break;
        default:
            cerr<<"数据结构错误。\n";
            Pause();
            break;
        }
    }
    system("cls");
    return 0;
}

int Input()
{
    for(;;)
    {
        cin.clear();
        cin.sync();
        system("cls");
        cout<<"               #,  #=  #:      #                             #\n                #  ##  #       #                             #\n                #  ##  #  ###  #  W##:  ###  Y=## ##B  ###   #\n                # # B ,R #   # #  #  # #   # I#  #  # #   #  #\n                :Y#  ##  ##### # #     #   # I;  #  # #####  #\n                 ##  ##  #     # iB  ; #   # I;  #  # #\n                 #   ##   #,#V #  #RB#  #:#i I+  #  #  #,#X .#\n";
        cout<<"请选择欲录入的员工类别:\n";
        cout<<"    1.职员        Employee\n";
        cout<<"    2.经理        Manager\n";
        cout<<"    3.销售经理    Salemanager\n";
        cout<<"    4.销售员      Salesman\n";
        cout<<"    5.技术员      Technician\n";
        cout<<"    B.返回主菜单\n";
        char choice;
        choice=getch();
        fflush(stdin);
        if(choice=='1')
        {
            Employee* employee=new Employee;
            if(employee==NULL)
            {
                cerr<<"内存分配错误。\n";
                Pause();
            }
            else
            {
                cout<<"请分别输入员工等级和月薪:";
                cin>>*employee;
                if(cin.fail())
                {
                    cerr<<"对不起，输入错误；请重新输入。";
                    Wait();
                }
                else
                {
                    object_struct={kEmployee,employee};
                    data.push_back(object_struct);
                    cout<<"输入成功。\n";
                    Wait();
                }
            }
        }
        else if(choice=='2')
        {
            Manager* manager=new Manager;
            if(manager==NULL)
            {
                cerr<<"内存分配错误。\n";
                Pause();
            }
            else
            {
                object_struct={kManager,manager};
                data.push_back(object_struct);
                cout<<"输入成功。\n";
                Wait();
            }
        }
        else if(choice=='3')
        {
            Data salesmen;
            for(Data::iterator iter=data.begin();iter!=data.end();++iter)
            {
                if(iter->type==kSalesman)
                {
                    salesmen.push_back(*iter);
                }
            }
            if(salesmen.size()==0)
            {
                cout<<"现在没有销售员，不能录用销售经理。\n";
                Wait();
            }
            else
            {
                system("cls");
                cout<<"将列出现有的的销售员。\n";
                Wait();
                for(Data::iterator iter=salesmen.begin();iter!=salesmen.end();++iter)
                {
                    cout<<*((Salesman*)(iter->pointer))<<endl;
                }
                cout<<"请在一行内输入欲录用销售经理所管辖的销售员工号:";
                string temp_str;
                getline(cin,temp_str);
                vector<Salesman*> salesmen_pointer;
                size_t length_salesmen=0;
                for(istringstream istrin(temp_str);;)
                {
                    int num;
                    istrin>>num;
                    if(istrin.fail())
                    {
                        break;
                    }
                    for(Data::iterator iter=salesmen.begin();iter!=salesmen.end();++iter)
                    {
                        if(num==((Salesman*)(iter->pointer))->individual_emp_no())
                        {
                            salesmen_pointer.push_back((Salesman*)(iter->pointer));
                            length_salesmen+=sizeof(*((Salesman*)(iter->pointer)));
                        }
                    }
                }
                if(length_salesmen>0)
                {
                    Salesman* salesmen_array=(Salesman*)malloc(length_salesmen);
                    size_t position=0;
                    for(vector<Salesman*>::iterator iter=salesmen_pointer.begin();
                        iter!=salesmen_pointer.end();++iter)
                    {
                        for(size_t i=0;i<sizeof(**iter);++i)
                        {
                            *((char*)salesmen_array+position+i)=*((char*)(*iter)+i);
                        }
                        position+=sizeof(**iter);
                    }
                    Salemanager* salesmanager=new Salemanager(salesmen_array,salesmen_pointer.size());
                    if(salesmanager==NULL)
                    {
                        cerr<<"内存分配错误。\n";
                        Pause();
                    }
                    else
                    {
                        object_struct={kSalemanager,salesmanager};
                        data.push_back(object_struct);
                        cout<<"输入成功。\n";
                        Wait();
                    }
                    free(salesmen_array);
                }
                else
                {
                    cout<<"没有找到匹配的工号。\n";
                    Wait();
                }
            }
        }
        else if(choice=='4')
        {
            Salesman* salesman=new Salesman;
            if(salesman==NULL)
            {
                cerr<<"内存分配错误。\n";
                Pause();
            }
            else
            {
                cout<<"请输入该销售员本月的销售额:";
                cin>>*salesman;
                if(cin.fail())
                {
                    cerr<<"对不起，输入错误；请重新输入。";
                    Wait();
                }
                else
                {
                    object_struct={kSalesman,salesman};
                    data.push_back(object_struct);
                    cout<<"输入成功。\n";
                    Wait();
                }
            }
        }
        else if(choice=='5')
        {
            Technician* technician=new Technician;
            if(technician==NULL)
            {
                cerr<<"内存分配错误。\n";
                Pause();
            }
            else
            {
                cout<<"请分别该技术员本月的工作时长:";
                cin>>*technician;
                if(cin.fail())
                {
                    cerr<<"对不起，输入错误；请重新输入。";
                    Wait();
                }
                else
                {
                    object_struct={kTechnician,technician};
                    data.push_back(object_struct);
                    cout<<"输入成功。\n";
                    Wait();

                }
            }
        }
        else if(choice=='B'||choice=='b')
        {
            return 0;
        }
        else
        {
            cerr<<"对不起，输入错误；请重新输入。";
            Wait();
        }
    }
    return 0;
}
int Modify()
{
    for(;;)
    {
        cin.clear();
        cin.sync();
        system("cls");
        cout<<"               #,  #=  #:      #                             #\n                #  ##  #       #                             #\n                #  ##  #  ###  #  W##:  ###  Y=## ##B  ###   #\n                # # B ,R #   # #  #  # #   # I#  #  # #   #  #\n                :Y#  ##  ##### # #     #   # I;  #  # #####  #\n                 ##  ##  #     # iB  ; #   # I;  #  # #\n                 #   ##   #,#V #  #RB#  #:#i I+  #  #  #,#X .#\n";
        cout<<"请选择欲修改的员工编号:\n";
        cout<<"    D.显示当前所有员工\n";
        cout<<"    B.返回主菜单\n";
        char choice;
        choice=getch();
        if(choice=='D'||choice=='d')
        {
            system("cls");
            if(data.empty())
            {
                cerr<<"数据空。\n";
            }
            for(Data::iterator iter=data.begin();iter!=data.end();++iter)
            {
                switch(iter->type)
                {
                case kEmployee:
                    cout<<*((Employee*)iter->pointer)<<endl;
                    break;
                case kManager:
                    cout<<*((Manager*)iter->pointer)<<endl;
                    break;
                case kSalemanager:
                    cout<<*((Salemanager*)iter->pointer)<<endl;
                    break;
                case kSalesman:
                    cout<<*((Salesman*)iter->pointer)<<endl;
                    break;
                case kTechnician:
                    cout<<*((Technician*)iter->pointer)<<endl;
                    break;
                default:
                    cerr<<"数据结构错误。\n";
                    cerr<<"类型标识:"<<hex<<(iter->type)<<endl;
                }
            }
            Pause();
        }
        else if(choice=='B'||choice=='b')
        {
            return 0;
        }
        else if(choice>='0'&&choice<='9')
        {
            int num;
            cin>>num;
            if(cin.fail())
            {
                cerr<<"对不起，输入错误；请重新输入。";
                Wait();
            }
            else
            {
                bool found=false;
                for(Data::iterator iter=data.begin();iter!=data.end();++iter)
                {
                    char c;
                    switch(iter->type)
                    {
                    case kEmployee:
                        if(num==((Employee*)(iter->pointer))->individual_emp_no())
                        {
                            if(found)
                            {
                                cerr<<"工号重复。\n";
                            }
                            system("cls");
                            cout<<*(Employee*)(iter->pointer)<<endl\
                                <<"请选择欲修改的内容:\n"\
                                <<"    1.等级\n    2.月薪\n";
                            c=getch();
                            switch(c)
                            {
                            case '1':
                                int grade;
                                cout<<"请输入修改后的等级:";
                                cin>>grade;
                                if(cin.fail())
                                {
                                    cerr<<"输入错误，请重新输入。\n";
                                }
                                else
                                {
                                    ((Employee*)iter->pointer)->set_grade(grade);
                                    cout<<"修改成功。\n";
                                }
                                break;
                            case '2':
                                int pay;
                                cout<<"请输入修改后的月薪:";
                                cin>>pay;
                                if(cin.fail())
                                {
                                    cerr<<"输入错误，请重新输入。\n";
                                }
                                else
                                {
                                    ((Employee*)iter->pointer)->promote(pay,0);
                                    cout<<"修改成功。\n";
                                }
                                break;
                            default:
                                cerr<<"输入错误，请重新输入。\n";
                            }
                            found=true;
                            Wait();
                        }
                        break;
                    case kManager:
                        if(num==((Manager*)(iter->pointer))->individual_emp_no())
                        {
                            if(found)
                            {
                                cerr<<"工号重复。\n";
                            }
                            system("cls");

                            int pay;
                            cout<<"请输入修改后的月薪:";
                            cin>>pay;
                            if(cin.fail())
                            {
                                cerr<<"输入错误，请重新输入。\n";
                            }
                            else
                            {
                                ((Manager*)iter->pointer)->promote(pay,0);
                                cout<<"修改成功。\n";
                            }

                            found=true;
                            Wait();
                        }
                        break;
                    case kSalemanager:
                        if(num==((Salemanager*)(iter->pointer))->individual_emp_no())
                        {
                            if(found)
                            {
                                cerr<<"工号重复。\n";
                            }
                            system("cls");
                            cout<<*(Salemanager*)(iter->pointer)<<endl\
                                <<"请选择欲修改的内容:\n"\
                                <<"    1.固定工资\n    2.提成\n";
                            c=getch();
                            switch(c)
                            {
                            case '1':
                                int pay;
                                cout<<"请输入修改后的固定工资:";
                                cin>>pay;
                                if(cin.fail())
                                {
                                    cerr<<"输入错误，请重新输入。\n";
                                }
                                else
                                {
                                    ((Salemanager*)iter->pointer)->promote(pay,0);
                                    cout<<"修改成功。\n";
                                }
                                break;
                            case '2':
                                double percentage;
                                cout<<"请输入修改后的提成:";
                                cin>>percentage;
                                if(cin.fail())
                                {
                                    cerr<<"输入错误，请重新输入。\n";
                                }
                                else
                                {
                                    ((Salemanager*)iter->pointer)->promote(0,percentage);
                                    cout<<"修改成功。\n";
                                }
                                break;
                            default:
                                cerr<<"输入错误，请重新输入。\n";
                            }
                            found=true;
                            Wait();
                        }
                        break;
                    case kSalesman:
                        if(num==((Salesman*)(iter->pointer))->individual_emp_no())
                        {
                            if(found)
                            {
                                cerr<<"工号重复。\n";
                            }
                            system("cls");
                            cout<<*(Salesman*)(iter->pointer)<<endl\
                                <<"请选择欲修改的内容:\n"\
                                <<"    1.销售额\n    2.提成\n";
                            c=getch();
                            switch(c)
                            {
                            case '1':
                                int sales;
                                cout<<"请输入修改后的销售额:";
                                cin>>sales;
                                if(cin.fail())
                                {
                                    cerr<<"输入错误，请重新输入。\n";
                                }
                                else
                                {
                                    ((Salesman*)iter->pointer)->set_sales(sales);
                                    cout<<"修改成功。\n";
                                }
                                break;
                            case '2':
                                double percentage;
                                cout<<"请输入修改后的提成:";
                                cin>>percentage;
                                if(cin.fail())
                                {
                                    cerr<<"输入错误，请重新输入。\n";
                                }
                                else
                                {
                                    ((Salesman*)iter->pointer)->promote(0,percentage);
                                    cout<<"修改成功。\n";
                                }
                                break;
                            default:
                                cerr<<"输入错误，请重新输入。\n";
                            }
                            found=true;
                            Wait();
                        }
                        break;
                    case kTechnician:
                        if(num==((Technician*)(iter->pointer))->individual_emp_no())
                        {
                            if(found)
                            {
                                cerr<<"工号重复。\n";
                            }
                            system("cls");
                            cout<<*(Technician*)(iter->pointer)<<endl\
                                <<"请选择欲修改的内容:\n"\
                                <<"    1.工作时长\n    2.时薪\n";
                            c=getch();
                            switch(c)
                            {
                            case '1':
                                int hours;
                                cout<<"请输入修改后的销售额:";
                                cin>>hours;
                                if(cin.fail())
                                {
                                    cerr<<"输入错误，请重新输入。\n";
                                }
                                else
                                {
                                    ((Technician*)iter->pointer)->set_working_hours(hours);
                                    cout<<"修改成功。\n";
                                }
                                break;
                            case '2':
                                double pay;
                                cout<<"请输入修改后的时薪:";
                                cin>>pay;
                                if(cin.fail())
                                {
                                    cerr<<"输入错误，请重新输入。\n";
                                }
                                else
                                {
                                    ((Technician*)iter->pointer)->promote(pay,0);
                                    cout<<"修改成功。\n";
                                }
                                break;
                            default:
                                cerr<<"输入错误，请重新输入。\n";
                            }
                            found=true;
                            Wait();
                        }
                        break;
                    default:
                        cerr<<"数据结构错误。\n";
                        cerr<<"类型标识:"<<hex<<(iter->type)<<endl;
                    }
                }
                if(!found)
                {
                    cerr<<"对不起，没有找到匹配的工号。";
                    Wait();
                }
            }
        }
        else
        {
            cerr<<"对不起，输入错误；请重新输入。";
            Wait();
        }
    }
    return 0;
}
int Search()
{
    for(;;)
    {
        cin.clear();
        cin.sync();
        system("cls");
        cout<<"               #,  #=  #:      #                             #\n                #  ##  #       #                             #\n                #  ##  #  ###  #  W##:  ###  Y=## ##B  ###   #\n                # # B ,R #   # #  #  # #   # I#  #  # #   #  #\n                :Y#  ##  ##### # #     #   # I;  #  # #####  #\n                 ##  ##  #     # iB  ; #   # I;  #  # #\n                 #   ##   #,#V #  #RB#  #:#i I+  #  #  #,#X .#\n";
        cout<<"请选择欲查询的员工编号:\n";
        cout<<"    D.显示当前所有员工\n";
        cout<<"    B.返回主菜单\n";
        char choice;
        choice=getch();
        if(choice=='D'||choice=='d')
        {
            system("cls");
            if(data.empty())
            {
                cerr<<"数据空。\n";
            }
            for(Data::iterator iter=data.begin();iter!=data.end();++iter)
            {
                switch(iter->type)
                {
                case kEmployee:
                    cout<<*((Employee*)iter->pointer)<<endl;
                    break;
                case kManager:
                    cout<<*((Manager*)iter->pointer)<<endl;
                    break;
                case kSalemanager:
                    cout<<*((Salemanager*)iter->pointer)<<endl;
                    break;
                case kSalesman:
                    cout<<*((Salesman*)iter->pointer)<<endl;
                    break;
                case kTechnician:
                    cout<<*((Technician*)iter->pointer)<<endl;
                    break;
                default:
                    cerr<<"数据结构错误。\n";
                    cerr<<"类型标识:"<<hex<<(iter->type)<<endl;
                }
            }
            Pause();
        }
        else if(choice=='B'||choice=='b')
        {
            return 0;
        }
        else if(choice>='0'&&choice<='9')
        {
            int num;
            cin>>num;
            if(cin.fail())
            {
                cerr<<"对不起，输入错误；请重新输入。";
                Wait();
            }
            else
            {
                bool found=false;
                for(Data::iterator iter=data.begin();iter!=data.end();++iter)
                {
                    switch(iter->type)
                    {
                    case kEmployee:
                        if(num==((Employee*)(iter->pointer))->individual_emp_no())
                        {
                            if(found)
                            {
                                cerr<<"工号重复。\n";
                            }
                            cout<<*(Employee*)(iter->pointer)<<endl;
                            found=true;
                            Pause();
                        }
                        break;
                    case kManager:
                        if(num==((Manager*)(iter->pointer))->individual_emp_no())
                        {
                            if(found)
                            {
                                cerr<<"工号重复。\n";
                            }
                            cout<<*(Manager*)(iter->pointer)<<endl;
                            found=true;
                            Pause();
                        }
                        break;
                    case kSalemanager:
                        if(num==((Salemanager*)(iter->pointer))->individual_emp_no())
                        {
                            if(found)
                            {
                                cerr<<"工号重复。\n";
                            }
                            cout<<*(Salemanager*)(iter->pointer)<<endl;
                            found=true;
                            Pause();
                        }
                        break;
                    case kSalesman:
                        if(num==((Salesman*)(iter->pointer))->individual_emp_no())
                        {
                            if(found)
                            {
                                cerr<<"工号重复。\n";
                            }
                            cout<<*(Salesman*)(iter->pointer)<<endl;
                            found=true;
                            Pause();
                        }
                        break;
                    case kTechnician:
                        if(num==((Technician*)(iter->pointer))->individual_emp_no())
                        {
                            if(found)
                            {
                                cerr<<"工号重复。\n";
                            }
                            cout<<*(Technician*)(iter->pointer)<<endl;
                            found=true;
                            Pause();
                        }
                        break;
                    default:
                        cerr<<"数据结构错误。\n";
                        cerr<<"类型标识:"<<hex<<(iter->type)<<endl;
                    }
                }
                if(!found)
                {
                    cerr<<"对不起，没有找到匹配的工号。";
                    Wait();
                }
            }
        }
        else
        {
            cerr<<"对不起，输入错误；请重新输入。";
            Wait();
        }
    }
    return 0;
}


int LoadData(const char* filename)
{
    ifstream fin(filename,ios::binary|ios::app|ios::in);
    if(fin.fail())
    {
        cerr<<"文件打开失败。\n";
        Wait();
        return -1;
    }
    data.clear();
    fin.seekg(0,ios::end);
    streampos current=fin.tellg();
    fin.seekg(0,ios::beg);
    if(fin.tellg()!=current)
    {
        fin.read((char*)(&(Employee::counter)),sizeof(Employee::counter));
        if(!fin.eof())
        {
            void* object=NULL;
            for(;;)
            {
                fin.read((char*)(&read_type),sizeof(read_type));
                switch(read_type)
                {
                case kEmployee:
                    object=new Employee(0,0,false);
                    ((Employee*)(object))->read_from(fin);
                    break;
                case kManager:
                    object=new Manager(false,false);
                    ((Manager*)(object))->read_from(fin);
                    break;
                case kSalemanager:
                    object=new Salemanager(NULL,0,false);
                    ((Salemanager*)(object))->read_from(fin);
                    break;
                case kSalesman:
                    object=new Salesman(0,false);
                    ((Salesman*)(object))->read_from(fin);
                    break;
                case kTechnician:
                    object=new Technician(0,false);
                    ((Technician*)(object))->read_from(fin);
                    break;
                default:
                    cerr<<"数据结构错误。\n";
                    Pause();
                    break;
                }
                object_struct={read_type,object};
                if(fin.eof())
                {
                    break;
                }
                if(fin.fail())
                {
                    cerr<<"读取文件错误。\n";
                    fin.close();
                    return -2;
                }
                data.push_back(object_struct);
            }
        }
        cout<<"读取文件成功。\n";
    }
    else
    {
        cout<<"创建文件成功。\n";
    }
    fin.close();
    return 0;
}
int SaveData(const char* filename)
{
    ofstream fout(filename,ios::binary|ios::out);
    if(fout.fail())
    {
        cerr<<"文件打开失败。\n";
        Wait();
        return -1;
    }
    fout.write((char*)(&(Employee::counter)),sizeof(Employee::counter));
    for(Data::iterator iter=data.begin();iter!=data.end();++iter)
    {
        if(fout.fail())
        {
            cerr<<"文件写入失败。\n";
            Wait();
            return -2;
        }
        fout.write((char*)(&(iter->type)),sizeof(iter->type));
        switch(iter->type)
        {
        case kEmployee:
            ((Employee*)(iter->pointer))->write_to(fout);
            break;
        case kManager:
            ((Manager*)(iter->pointer))->write_to(fout);
            break;
        case kSalemanager:
            ((Salemanager*)(iter->pointer))->write_to(fout);
            break;
        case kSalesman:
            ((Salesman*)(iter->pointer))->write_to(fout);
            break;
        case kTechnician:
            ((Technician*)(iter->pointer))->write_to(fout);
            break;
        default:
            cerr<<"数据结构错误。\n";
            Pause();
            break;
        }
    }
    cout<<"写入文件成功。\n";
    fout.close();
    return 0;
}
