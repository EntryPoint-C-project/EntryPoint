#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Teacher_Subject {
public:
    static void Create(pqxx::connection &conn, const int teacher_id , const int   subject_id ); 

    static std::vector <int>  ReadSubjectId(pqxx::connection &conn, const int teacher_id); 

    static std::vector <int>  ReadTeacherId(pqxx::connection &conn, const int subject_id); 

    static void Update(pqxx::connection &conn, const int old_teacher_id , const int old_subject_id , const int new_teacher_id , const int new_subject_id ); 

    static void Remove(pqxx::connection &conn, const int teacher_id , const int subject_id ); 
}; 