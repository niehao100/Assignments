#include<cstring>

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

int Teacher::Login()
{
    printf("Wait!");
    getch();
    return 0;
}
