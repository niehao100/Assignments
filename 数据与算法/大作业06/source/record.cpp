#include<cstdio>
#include"record.h"
Record* Record::Insert(Record* record,SortType type)
{
    if(kNumber==type)
    {
        record->number() < number() ?
            (number_left_ !=NULL ? number_left_ ->Insert(record,type) : number_left_ =record):
            (number_right_!=NULL ? number_right_->Insert(record,type) : number_right_=record);
        return record;
    }
    if(kScore==type)
    {
        if(record->total_score()> total_score())
        {
            score_left_ !=NULL ?  score_left_ ->Insert(record,type) :  score_left_ =record;
        }
        if(record->total_score()==total_score())
        {
            record->number() < number() ?
                (score_left_ !=NULL ? score_left_ ->Insert(record,type) : score_left_ =record):
                (score_right_!=NULL ? score_right_->Insert(record,type) : score_right_=record);
        }
        if(record->total_score()< total_score())
        {
            score_right_!=NULL ?  score_right_->Insert(record,type) :  score_right_=record;
        }
        return record;
    }
    return NULL;
}
int PrintByNumber(Record* record,FILE* output)
{
    record!=NULL ? PrintByNumber(record->  left(kNumber),output) : 0;
    record!=NULL && fprintf(output,"S%04d %d.%02d %d.%02d\n",
        record->number(),
        record->   math_score()/100,
        record->   math_score()%100,
        record->chinese_score()/100,
        record->chinese_score()%100);
    record!=NULL ? PrintByNumber(record-> right(kNumber),output) : 0;
    return 0;
}
int PrintByScore(Record* record,FILE* output)
{
    record!=NULL ? PrintByScore(record->  left(kScore),output) : 0;
    if(record!=NULL && record->number()!=-1)
    fprintf(output,"S%04d %d.%02d %d.%02d\n",
        record->number(),
        record->   math_score()/100,
        record->   math_score()%100,
        record->chinese_score()/100,
        record->chinese_score()%100);
    record!=NULL ? PrintByScore(record-> right(kScore),output) : 0;
    return 0;
}
int SearchAndPrint(Record* record,int minimum_total_score,int number_begin,int number_end,FILE* output)
{
    record!=NULL ? SearchAndPrint(record->  left(kScore),minimum_total_score,number_begin,number_end,output) : 0;
    if(record!=NULL && record->number()!=-1 && record->number()>=number_begin && record->number()<number_end && record->total_score()>=minimum_total_score*100)
    {
        fprintf(output,"S%04d %d.%02d %d.%02d\n",
            record->number(),
            record->   math_score()/100,
            record->   math_score()%100,
            record->chinese_score()/100,
            record->chinese_score()%100);
    }
    record!=NULL ? SearchAndPrint(record-> right(kScore),minimum_total_score,number_begin,number_end,output) : 0;
    return 0;
}
int Nullify(Record* record,int number,int math_score,int chinese_score)
{
    record!=NULL ? Nullify(record->  left(kScore),number,math_score,chinese_score) : 0;
    if(record!=NULL && record->number()==number && record->math_score()==math_score && record->chinese_score()==chinese_score)
    {
        record->set_number(-1);
    }
    record!=NULL ? Nullify(record-> right(kScore),number,math_score,chinese_score) : 0;
    return 0;
}