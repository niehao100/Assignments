#ifndef ADMIN_H_
#define ADMIN_H_
#include"score.h"
#include"student.h"
#include"teacher.h"
#include"user.h"
class Admin:virtual public Student,virtual public Teacher
{
public:
    Admin(uint64_t password):
        User(NULL,0,password),Student(NULL,0,password,std::vector<Score>()),Teacher(NULL,0,password),teacher_vector_(),student_vector_(),admin_id_set_(){}
    Admin(const char* buffer,size_t size);
    ~Admin(){};
    virtual size_t WriteTo(char* buffer,size_t size);
    virtual size_t ReadFrom(const char* buffer,size_t size);

    int AddTeacher(const Teacher& add);
    int AddStudent(const Student& add);
    int UpdateTeacher(const Teacher& add);
    int UpdateStudent(const Student& add);
    int DeleteTeacher(const Teacher& del){return DeleteTeacher(del.id_);}
    int DeleteStudent(const Student& del){return DeleteStudent(del.id_);}
    int DeleteTeacher(uint64_t);
    int DeleteStudent(uint64_t);

    int Manage();
    Teacher* FindTeacher(char name[MAX_NAME_LENGTH]);
    Teacher* FindTeacher(uint64_t id);
    Student* FindStudent(char name[MAX_NAME_LENGTH]);
    Student* FindStudent(uint64_t id);

    std::vector<Teacher> teacher_vector_;
    std::vector<Student> student_vector_;
    std::set<uint64_t> admin_id_set_;
};
#endif // ADMIN_H_
