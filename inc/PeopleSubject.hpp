#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class People_Subject {
public:
    static void Create(pqxx::connection &conn, const int person_id , const int   subject_id ); 

    static std::vector <int>  ReadSubjectId(pqxx::connection &conn, const int person_id); 

    static std::vector <int>  ReadPersonId(pqxx::connection &conn, const int subject_id); 

    static void Update(pqxx::connection &conn, const int old_person_id , const int old_subject_id , const int new_person_id , const int new_subject_id ); 

    static void Remove(pqxx::connection &conn, const int person_id , const int subject_id ); 
}; 