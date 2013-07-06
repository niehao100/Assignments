#include<cstring>

#include<set>

#include"user.h"

using namespace std;


User::User(const char* name,uint64_t id,uint64_t password):id_(id),hash_(password)
{
    if(name==NULL)
    {
        name_[0]='\0';
        strcpy(name_+1,"NAME_IS_NULL");
        return;
    }
    if(strlen(name)>=MAX_NAME_LENGTH)
    {
        name_[0]='\0';
        strcpy(name_+1,"NAME_TOO_LONG");
        id_=0;
        hash_=0;
    }
    else
    {
        if(id==0)
        {
            name_[0]='\0';
            strcpy(name_+1,"ID_IS_ZERO");
            id_=0;
            hash_=0;
        }
        else
        {
            strcpy(name_,name);

        }
    }
}

User::~User()
{
}

bool User::Identify(const char* password)
{
    return hash_==Hash(password);
}
