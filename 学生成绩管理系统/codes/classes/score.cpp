#include<cstring>

#include"score.h"
#include"user.h"

using namespace std;

Score::Score(const char* subject,double mark,uint64_t teacher):mark_(mark),teacher_(teacher)
{
    if(strlen(subject)>=MAX_SUBJECT_NAME_LENGTH)
    {
        subject_[0]='\0';
        strcpy(subject_+1,"SUBJECT_NAME_TOO_LONG");
        mark_=0;
        teacher_=0;
    }
    else
    {
        strcpy(subject_,subject);
        mark_=mark;
        teacher_=teacher;
    }
}

Score::Score(const char* buffer,size_t size):mark_(),teacher_()
{
    ReadFrom(buffer,size);
}

Score::Score(const Score& score):mark_(score.mark_),teacher_(score.teacher_)
{
    for(size_t i=0;i<MAX_SUBJECT_NAME_LENGTH;++i)
    {
        subject_[i]=score.subject_[i];
    }
}

Score::~Score(){}

size_t Score::WriteTo(char* buffer,size_t size)
{
    if(size!=MAX_SUBJECT_NAME_LENGTH+sizeof(mark_)+sizeof(teacher_))
    {
        subject_[0]='\0';
        strcpy(subject_+1,"BINARY_DATA_ERROR");
        mark_=0;
        teacher_=0;
        return 0;
    }
    strncpy(buffer,subject_,MAX_SUBJECT_NAME_LENGTH);
    buffer+=MAX_SUBJECT_NAME_LENGTH;
    for(size_t i=0;i<sizeof(mark_);++i)
    {
        buffer[i]=((char*)&mark_)[i];
    }
    buffer+=sizeof(mark_);
    for(size_t i=0;i<sizeof(teacher_);++i)
    {
        buffer[i]=((char*)&teacher_)[i];
    }
    buffer+=sizeof(teacher_);
    return size;
}

size_t Score::ReadFrom(const char* buffer,size_t size)
{
    if(size!=MAX_SUBJECT_NAME_LENGTH+sizeof(mark_)+sizeof(teacher_))
    {
        subject_[0]='\0';
        strcpy(subject_+1,"BINARY_DATA_ERROR");
        mark_=0;
        teacher_=0;
        return 0;
    }

    strncpy(subject_,buffer,MAX_SUBJECT_NAME_LENGTH);
    buffer+=MAX_SUBJECT_NAME_LENGTH;

    for(size_t i=0;i<sizeof(mark_);++i)
    {
        ((char*)&mark_)[i]=buffer[i];
    }
    buffer+=sizeof(mark_);

    for(size_t i=0;i<sizeof(teacher_);++i)
    {
        ((char*)&teacher_)[i]=buffer[i];
    }
    buffer+=sizeof(teacher_);

    return size;
}
