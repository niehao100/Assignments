/*
 *  File Encoding: CP936/GBK
 *  Chi Blaok @ EE THU, All Rights Reserved.
 *
 */

#include<cstdlib>
#include<cstring>

#include<iostream>
#include<vector>

#include<conio.h>

#include"classes\manager.h"
#include"classes\technician.h"
#include"classes\salesman.h"
#include"classes\salemanager.h"
#include"utilities.h"

using namespace std;

extern Data data;

int main()
{
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
        cout<<"    4.数据删除\n";
        cout<<"    5.数据统计\n";
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
        case '4':
            Delete();
            break;
        case '5':
            Statistic();
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
