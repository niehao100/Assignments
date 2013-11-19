#ifndef RECORD_H_
#define RECORD_H_
#include<cstddef>
enum SortType
{
    kNumber,
    kScore,
    kBoth
};
class Record
{
public:
    Record(int number,int math_score,int chinese_score):
        number_left_(NULL),number_right_(NULL),score_left_(NULL),score_right_(NULL),\
        number_(number),math_score_(math_score),chinese_score_(chinese_score),total_score_(math_score+chinese_score){}
    ~Record(){delete number_left_;delete number_right_;}
    Record* Insert(Record*,SortType);

    int number() const {return number_;}
    int    math_score() const {return    math_score_;}
    int chinese_score() const {return chinese_score_;}
    int   total_score() const {return   total_score_;}

    void set_number(int number){number_=number;}
    void    set_math_score(int    math_score){   math_score_=   math_score;total_score_=math_score_+chinese_score_;}
    void set_chinese_score(int chinese_score){chinese_score_=chinese_score;total_score_=math_score_+chinese_score_;}
    
    Record* left (SortType type){return kNumber==type ? number_left_  : (kScore==type ? score_left_  : NULL);}
    Record* right(SortType type){return kNumber==type ? number_right_ : (kScore==type ? score_right_ : NULL);}
    
    void set_left (Record* left ,SortType type){kNumber==type &&(number_left_ =left) ;kScore==type &&(score_left_ =left) ;}
    void set_right(Record* right,SortType type){kNumber==type &&(number_right_=right);kScore==type &&(score_right_=right);}

private:
    Record* number_left_;
    Record* number_right_;
    Record* score_left_;
    Record* score_right_;
    int number_;
    int    math_score_;
    int chinese_score_;
    int   total_score_;
};

int PrintByScore(Record* record,FILE* output);
int PrintByNumber(Record* record,FILE* output);
int SearchAndPrint(Record* record,int minimum_total_score,int number_begin,int number_end,FILE* output);
int Nullify(Record* record,int number,int math_score,int chinese_score);
#endif//RECORD_H_