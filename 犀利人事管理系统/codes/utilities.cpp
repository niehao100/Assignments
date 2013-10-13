/*
 *  File Encoding: CP936/GBK
 *  Chi Blaok @ EE THU, All Rights Reserved.
 *
 */

#include<cstdlib>

#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>

#include<conio.h>

#include"utilities.h"

using namespace std;

Data data;
Type read_type;
Object object_struct;

int Input()
{
    for(;;)
    {
        cin.clear();
        cin.sync();
        system("cls");
        cout<<"               #,  #=  #:      #                             #\n                #  ##  #       #                             #\n                #  ##  #  ###  #  W##:  ###  Y=## ##B  ###   #\n                # # B ,R #   # #  #  # #   # I#  #  # #   #  #\n                :Y#  ##  ##### # #     #   # I;  #  # #####  #\n                 ##  ##  #     # iB  ; #   # I;  #  # #\n                 #   ##   #,#V #  #RB#  #:#i I+  #  #  #,#X .#\n";
        cout<<"��ѡ����¼���Ա�����:\n";
        cout<<"    1.ְԱ        Employee\n";
        cout<<"    2.����        Manager\n";
        cout<<"    3.���۾���    Salemanager\n";
        cout<<"    4.����Ա      Salesman\n";
        cout<<"    5.����Ա      Technician\n";
        cout<<"    B.�������˵�\n";
        char choice;
        choice=getch();
        fflush(stdin);
        if(choice=='1')
        {
            Employee* employee=new Employee;
            if(employee==NULL)
            {
                cerr<<"�ڴ�������\n";
                Pause();
            }
            else
            {
                cout<<"��ֱ�����Ա���ȼ�����н:";
                cin>>*employee;
                if(cin.fail())
                {
                    cerr<<"�Բ�������������������롣";
                    Wait();
                }
                else
                {
                    object_struct={kEmployee,employee};
                    data.push_back(object_struct);
                    cout<<"����ɹ���\n";
                    Wait();
                }
            }
        }
        else if(choice=='2')
        {
            Manager* manager=new Manager;
            if(manager==NULL)
            {
                cerr<<"�ڴ�������\n";
                Pause();
            }
            else
            {
                object_struct={kManager,manager};
                data.push_back(object_struct);
                cout<<"����ɹ���\n";
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
                cout<<"����û������Ա������¼�����۾���\n";
                Wait();
            }
            else
            {
                system("cls");
                cout<<"���г����еĵ�����Ա��\n";
                Wait();
                for(Data::iterator iter=salesmen.begin();iter!=salesmen.end();++iter)
                {
                    cout<<*((Salesman*)(iter->pointer))<<endl;
                }
                cout<<"����һ����������¼�����۾�������Ͻ������Ա����:";
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
                        cerr<<"�ڴ�������\n";
                        Pause();
                    }
                    else
                    {
                        object_struct={kSalemanager,salesmanager};
                        data.push_back(object_struct);
                        cout<<"����ɹ���\n";
                        Wait();
                    }
                    free(salesmen_array);
                }
                else
                {
                    cout<<"û���ҵ�ƥ��Ĺ��š�\n";
                    Wait();
                }
            }
        }
        else if(choice=='4')
        {
            Salesman* salesman=new Salesman;
            if(salesman==NULL)
            {
                cerr<<"�ڴ�������\n";
                Pause();
            }
            else
            {
                cout<<"�����������Ա���µ����۶�:";
                cin>>*salesman;
                if(cin.fail())
                {
                    cerr<<"�Բ�������������������롣";
                    Wait();
                }
                else
                {
                    object_struct={kSalesman,salesman};
                    data.push_back(object_struct);
                    cout<<"����ɹ���\n";
                    Wait();
                }
            }
        }
        else if(choice=='5')
        {
            Technician* technician=new Technician;
            if(technician==NULL)
            {
                cerr<<"�ڴ�������\n";
                Pause();
            }
            else
            {
                cout<<"��ֱ�ü���Ա���µĹ���ʱ��:";
                cin>>*technician;
                if(cin.fail())
                {
                    cerr<<"�Բ�������������������롣";
                    Wait();
                }
                else
                {
                    object_struct={kTechnician,technician};
                    data.push_back(object_struct);
                    cout<<"����ɹ���\n";
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
            cerr<<"�Բ�������������������롣";
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
        cout<<"��ѡ����ʹ�õĹ���;���������ַ����Կ�ʼ���빤��:\n";
        cout<<"    D.��ʾ��ǰ����Ա��\n";
        cout<<"    B.�������˵�\n";
        char choice;
        choice=getch();
        if(choice=='D'||choice=='d')
        {
            system("cls");
            if(data.empty())
            {
                cerr<<"���ݿա�\n";
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
                    cerr<<"���ݽṹ����\n";
                    cerr<<"���ͱ�ʶ:"<<hex<<(iter->type)<<endl;
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
                cerr<<"�Բ�������������������롣";
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
                                cerr<<"�����ظ���\n";
                            }
                            system("cls");
                            cout<<*(Employee*)(iter->pointer)<<endl\
                                <<"��ѡ�����޸ĵ�����:\n"\
                                <<"    1.�ȼ�\n    2.��н\n";
                            c=getch();
                            switch(c)
                            {
                            case '1':
                                int grade;
                                cout<<"�������޸ĺ�ĵȼ�:";
                                cin>>grade;
                                if(cin.fail())
                                {
                                    cerr<<"����������������롣\n";
                                }
                                else
                                {
                                    ((Employee*)iter->pointer)->set_grade(grade);
                                    cout<<"�޸ĳɹ���\n";
                                }
                                break;
                            case '2':
                                int pay;
                                cout<<"�������޸ĺ����н:";
                                cin>>pay;
                                if(cin.fail())
                                {
                                    cerr<<"����������������롣\n";
                                }
                                else
                                {
                                    ((Employee*)iter->pointer)->promote(pay,0);
                                    cout<<"�޸ĳɹ���\n";
                                }
                                break;
                            default:
                                cerr<<"����������������롣\n";
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
                                cerr<<"�����ظ���\n";
                            }
                            system("cls");

                            int pay;
                            cout<<"�������޸ĺ����н:";
                            cin>>pay;
                            if(cin.fail())
                            {
                                cerr<<"����������������롣\n";
                            }
                            else
                            {
                                ((Manager*)iter->pointer)->promote(pay,0);
                                cout<<"�޸ĳɹ���\n";
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
                                cerr<<"�����ظ���\n";
                            }
                            system("cls");
                            cout<<*(Salemanager*)(iter->pointer)<<endl\
                                <<"��ѡ�����޸ĵ�����:\n"\
                                <<"    1.�̶�����\n    2.���\n";
                            c=getch();
                            switch(c)
                            {
                            case '1':
                                int pay;
                                cout<<"�������޸ĺ�Ĺ̶�����:";
                                cin>>pay;
                                if(cin.fail())
                                {
                                    cerr<<"����������������롣\n";
                                }
                                else
                                {
                                    ((Salemanager*)iter->pointer)->promote(pay,0);
                                    cout<<"�޸ĳɹ���\n";
                                }
                                break;
                            case '2':
                                double percentage;
                                cout<<"�������޸ĺ�����:";
                                cin>>percentage;
                                if(cin.fail())
                                {
                                    cerr<<"����������������롣\n";
                                }
                                else
                                {
                                    ((Salemanager*)iter->pointer)->promote(0,percentage);
                                    cout<<"�޸ĳɹ���\n";
                                }
                                break;
                            default:
                                cerr<<"����������������롣\n";
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
                                cerr<<"�����ظ���\n";
                            }
                            system("cls");
                            cout<<*(Salesman*)(iter->pointer)<<endl\
                                <<"��ѡ�����޸ĵ�����:\n"\
                                <<"    1.���۶�\n    2.���\n";
                            c=getch();
                            switch(c)
                            {
                            case '1':
                                int sales;
                                cout<<"�������޸ĺ�����۶�:";
                                cin>>sales;
                                if(cin.fail())
                                {
                                    cerr<<"����������������롣\n";
                                }
                                else
                                {
                                    ((Salesman*)iter->pointer)->set_sales(sales);
                                    cout<<"�޸ĳɹ���\n";
                                }
                                break;
                            case '2':
                                double percentage;
                                cout<<"�������޸ĺ�����:";
                                cin>>percentage;
                                if(cin.fail())
                                {
                                    cerr<<"����������������롣\n";
                                }
                                else
                                {
                                    ((Salesman*)iter->pointer)->promote(0,percentage);
                                    cout<<"�޸ĳɹ���\n";
                                }
                                break;
                            default:
                                cerr<<"����������������롣\n";
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
                                cerr<<"�����ظ���\n";
                            }
                            system("cls");
                            cout<<*(Technician*)(iter->pointer)<<endl\
                                <<"��ѡ�����޸ĵ�����:\n"\
                                <<"    1.����ʱ��\n    2.ʱн\n";
                            c=getch();
                            switch(c)
                            {
                            case '1':
                                int hours;
                                cout<<"�������޸ĺ�����۶�:";
                                cin>>hours;
                                if(cin.fail())
                                {
                                    cerr<<"����������������롣\n";
                                }
                                else
                                {
                                    ((Technician*)iter->pointer)->set_working_hours(hours);
                                    cout<<"�޸ĳɹ���\n";
                                }
                                break;
                            case '2':
                                double pay;
                                cout<<"�������޸ĺ��ʱн:";
                                cin>>pay;
                                if(cin.fail())
                                {
                                    cerr<<"����������������롣\n";
                                }
                                else
                                {
                                    ((Technician*)iter->pointer)->promote(pay,0);
                                    cout<<"�޸ĳɹ���\n";
                                }
                                break;
                            default:
                                cerr<<"����������������롣\n";
                            }
                            found=true;
                            Wait();
                        }
                        break;
                    default:
                        cerr<<"���ݽṹ����\n";
                        cerr<<"���ͱ�ʶ:"<<hex<<(iter->type)<<endl;
                    }
                }
                if(!found)
                {
                    cerr<<"�Բ���û���ҵ�ƥ��Ĺ��š�";
                    Wait();
                }
            }
        }
        else
        {
            cerr<<"�Բ�������������������롣";
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
        cout<<"��ѡ����ʹ�õĹ���;���������ַ����Կ�ʼ���빤��:\n";
        cout<<"    D.��ʾ��ǰ����Ա��\n";
        cout<<"    B.�������˵�\n";
        char choice;
        choice=getch();
        if(choice=='D'||choice=='d')
        {
            system("cls");
            if(data.empty())
            {
                cerr<<"���ݿա�\n";
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
                    cerr<<"���ݽṹ����\n";
                    cerr<<"���ͱ�ʶ:"<<hex<<(iter->type)<<endl;
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
                cerr<<"�Բ�������������������롣";
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
                                cerr<<"�����ظ���\n";
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
                                cerr<<"�����ظ���\n";
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
                                cerr<<"�����ظ���\n";
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
                                cerr<<"�����ظ���\n";
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
                                cerr<<"�����ظ���\n";
                            }
                            cout<<*(Technician*)(iter->pointer)<<endl;
                            found=true;
                            Pause();
                        }
                        break;
                    default:
                        cerr<<"���ݽṹ����\n";
                        cerr<<"���ͱ�ʶ:"<<hex<<(iter->type)<<endl;
                    }
                }
                if(!found)
                {
                    cerr<<"�Բ���û���ҵ�ƥ��Ĺ��š�";
                    Wait();
                }
            }
        }
        else
        {
            cerr<<"�Բ�������������������롣";
            Wait();
        }
    }
    return 0;
}

int Statistic()
{
    int employee_counter=0,
        manager_counter=0,
        salemanager_counter=0,
        salesman_counter=0,
        technician_counter=0;
    for(Data::iterator iter=data.begin();iter!=data.end();++iter)
    {
        switch(iter->type)
        {
        case kEmployee:
            ++employee_counter;
            break;
        case kManager:
            ++manager_counter;
            break;
        case kSalemanager:
            ++salemanager_counter;
            break;
        case kSalesman:
            ++salesman_counter;
            break;
        case kTechnician:
            ++technician_counter;
            break;
        default:
            cerr<<"���ݽṹ����\n";
            cerr<<"���ͱ�ʶ:"<<hex<<(iter->type)<<endl;
            return -1;
        }
    }
    cin.clear();
    cin.sync();
    system("cls");
    cout<<"               #,  #=  #:      #                             #\n                #  ##  #       #                             #\n                #  ##  #  ###  #  W##:  ###  Y=## ##B  ###   #\n                # # B ,R #   # #  #  # #   # I#  #  # #   #  #\n                :Y#  ##  ##### # #     #   # I;  #  # #####  #\n                 ##  ##  #     # iB  ; #   # I;  #  # #\n                 #   ##   #,#V #  #RB#  #:#i I+  #  #  #,#X .#\n";
    cout<<"ͳ�ƽ������:\n"
        <<"    Employee:    "<<employee_counter<<endl
        <<"    Manager:     "<<manager_counter<<endl
        <<"    Salemanager: "<<salemanager_counter<<endl
        <<"    Salesman:    "<<salesman_counter<<endl
        <<"    Technician:  "<<technician_counter<<endl
        <<"�ܼ�:            "<<employee_counter+
                               manager_counter+
                               salemanager_counter+
                               salesman_counter+
                               technician_counter<<endl;
    Pause();
    return 0;
}

int Delete()
{
    cin.clear();
    cin.sync();
    system("cls");
    cout<<"               #,  #=  #:      #                             #\n                #  ##  #       #                             #\n                #  ##  #  ###  #  W##:  ###  Y=## ##B  ###   #\n                # # B ,R #   # #  #  # #   # I#  #  # #   #  #\n                :Y#  ##  ##### # #     #   # I;  #  # #####  #\n                 ##  ##  #     # iB  ; #   # I;  #  # #\n                 #   ##   #,#V #  #RB#  #:#i I+  #  #  #,#X .#\n";
    cout<<"��������ɾ����Ա�����:\n";
    int num=0;
    cin>>num;
    if(cin.fail())
    {
        cerr<<"�Բ�������������������롣";
        Wait();
        return -1;
    }
    int found=0;
    for(Data::iterator iter=data.begin();iter!=data.end();++iter)
    {
        int emp_no=0;
        switch(iter->type)
        {
        case kEmployee:
            emp_no=((Employee*)(iter->pointer))->individual_emp_no();
            break;
        case kManager:
            emp_no=((Manager*)(iter->pointer))->individual_emp_no();
            break;
        case kSalemanager:
            emp_no=((Salemanager*)(iter->pointer))->individual_emp_no();
            break;
        case kSalesman:
            emp_no=((Salesman*)(iter->pointer))->individual_emp_no();
            break;
        case kTechnician:
            emp_no=((Technician*)(iter->pointer))->individual_emp_no();
            break;
        default:
            cerr<<"���ݽṹ����\n";
            cerr<<"���ͱ�ʶ:"<<hex<<(iter->type)<<endl;
            return -1;
        }
        if(emp_no==num)
        {
            delete (Employee*)(iter->pointer);
            data.erase(iter);
            ++found;
        }
        if(iter==data.end())
        {
            break;
        }
    }
    if(found>0)
    {
        if(found>1)
        {
            cerr<<"�����ظ����������ݽṹ��\n";
            Wait();
            return -3;
        }
        else
        {
            cout<<"ɾ���ɹ���\n";
            Wait();
            return 0;
        }
    }
    else
    {
        if(found==0)
        {
            cerr<<"δ�ҵ���Ӧ�����ݡ�\n";
            Wait();
            return -1;
        }
    }
    cerr<<"δ֪����\n";
    Wait();
    return -4;
}

int LoadData(const char* filename)
{
    ifstream fin(filename,ios::binary|ios::app|ios::in);
    if(fin.fail())
    {
        cerr<<"�ļ���ʧ�ܡ�\n";
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
                    object=new Manager(false);
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
                    cerr<<"���ݽṹ����\n";
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
                    cerr<<"��ȡ�ļ�����\n";
                    fin.close();
                    return -2;
                }
                data.push_back(object_struct);
            }
        }
        cout<<"��ȡ�ļ��ɹ���\n";
    }
    else
    {
        cout<<"�����ļ��ɹ���\n";
    }
    fin.close();
    return 0;
}
int SaveData(const char* filename)
{
    ofstream fout(filename,ios::binary|ios::out);
    if(fout.fail())
    {
        cerr<<"�ļ���ʧ�ܡ�\n";
        Wait();
        return -1;
    }
    fout.write((char*)(&(Employee::counter)),sizeof(Employee::counter));
    for(Data::iterator iter=data.begin();iter!=data.end();++iter)
    {
        if(fout.fail())
        {
            cerr<<"�ļ�д��ʧ�ܡ�\n";
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
            cerr<<"���ݽṹ����\n";
            Pause();
            break;
        }
    }
    cout<<"д���ļ��ɹ���\n";
    fout.close();
    return 0;
}
