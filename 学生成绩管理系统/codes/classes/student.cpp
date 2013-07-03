#include<cstring>

#include"student.h"

using namespace std;

Student::Student(const char* buffer,size_t size):User(NULL,0,0)
{
    ReadFrom(buffer,size);
}

size_t Student::WriteTo(char* buffer,size_t size)
{
    if(buffer==NULL)
    {
        return MAX_NAME_LENGTH+sizeof(uint64_t)*2+sizeof(size_t)+sizeof(Score)*score_vector_.size();
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

    size_t score_vector_size=score_vector_.size();
    for(size_t i=0;i<sizeof(size_t);++i)
    {
        buffer[i]=((char*)(&score_vector_size))[i];
    }
    buffer+=sizeof(size_t);

    for(vector<Score>::iterator iter=score_vector_.begin();iter!=score_vector_.end();++iter)
    {
        for(size_t i=0;i<sizeof(Score);++i)
        {
            buffer[i]=((char*)(&(*iter)))[i];
        }
        buffer+=sizeof(Score);
    }
    return MAX_NAME_LENGTH+sizeof(uint64_t)*2+sizeof(size_t)+sizeof(Score)*score_vector_size;
}

size_t Student::ReadFrom(const char* buffer,size_t size)
{
    if(size<MAX_NAME_LENGTH+sizeof(uint64_t)*2+sizeof(size_t))
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

    size_t score_vector_size;
    for(size_t i=0;i<sizeof(size_t);++i)
    {
        ((char*)(&score_vector_size))[i]=buffer[i];
    }
    buffer+=sizeof(size_t);

    score_vector_.clear();
    for(size_t i=0;i<score_vector_size;++i)
    {
        score_vector_.push_back(Score(buffer,MAX_SUBJECT_NAME_LENGTH+sizeof(double)+sizeof(uint64_t)));
        buffer+=sizeof(Score);
    }
    return MAX_NAME_LENGTH+sizeof(uint64_t)*2+sizeof(size_t)+sizeof(Score)*score_vector_size;
}

int Student::Login(Admin* admin)
{
    printf("!!!!!");
    Pause();
    return 0;
}
