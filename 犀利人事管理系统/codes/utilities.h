/*
 *  File Encoding: CP936/GBK
 *  Chi Blaok @ EE THU, All Rights Reserved.
 *
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include<cstdio>
#include<cstdlib>
#include<ctime>

#include<iostream>
#include<vector>

#include<conio.h>

#include"classes\manager.h"
#include"classes\technician.h"
#include"classes\salesman.h"
#include"classes\salemanager.h"

int Input();
int Modify();
int Search();
int Statistic();

int LoadData(const char* filename="save.dat");
int SaveData(const char* filename="save.dat");

enum Type
{
    kEmployee=1,
    kManager=2,
    kSalemanager=3,
    kSalesman=4,
    kTechnician=5
};

struct Object
{
    Type type;
    void* pointer;
};

typedef std::vector<Object> Data;


inline void Pause()
{
    fflush(stdin);
    std::cin.clear();
    std::cin.sync();
    getch();
}

inline void Wait()
{
    fflush(stdin);
    std::cin.clear();
    std::cin.sync();
    time_t start,current;
    time(&start);
    for(time(&current);current-start<1.0;time(&current));
}

#endif//UTILITIES_H_
