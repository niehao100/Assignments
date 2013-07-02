#include<cstring>

#include<set>

#include"user.h"

using namespace std;

set<uint64_t> User::id_set_;

User::User(const char* name,uint64_t id,uint64_t password)
{
    if(name==NULL)
    {
        name_[0]='\0';
        strcpy(name_+1,"NAME_IS_NULL");
        id_=id;
        hash_=password;
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
        if(User::id_set_.count(id)!=0)
        {
            name_[0]='\0';
            strcpy(name_+1,"ID_EXISTS");
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
                id_=id;
                User::id_set_.insert(id);
                hash_=password;

            }
        }
    }
}

User::~User()
{
    User::id_set_.erase(id_);
}

bool User::Identify(const char* password)
{
    return hash_==Hash(password);
}
