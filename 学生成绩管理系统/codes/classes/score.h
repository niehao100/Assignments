#ifndef SCORE_H_
#define SCORE_H_

#define MAX_SUBJECT_NAME_LENGTH 48

#include<cstdint>
#include<cstdlib>

class Score
{
public:
    Score(const char* subject,double mark,uint64_t teacher);
    Score(const char* buffer,size_t size);
    ~Score();

    size_t WriteTo(char* buffer,size_t size);
    size_t ReadFrom(const char* buffer,size_t size);
protected:
    char subject_[MAX_SUBJECT_NAME_LENGTH];
    double mark_;
    uint64_t teacher_;
};
#endif // SCORE_H_
