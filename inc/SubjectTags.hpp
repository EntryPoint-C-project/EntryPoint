#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Subject_Tags {
public:
    static void Create(pqxx::connection &conn, const int subject_id , const int   tag_id ); 

    static std::vector <int>  ReadTagId(pqxx::connection &conn, const int subject_id); 

    static std::vector <int>  ReadSubjectId(pqxx::connection &conn, const int tag_id); 

    static void Update(pqxx::connection &conn, const int old_subject_id , const int old_tag_id , const int new_subject_id , const int new_tag_id ); 

    static void Remove(pqxx::connection &conn, const int subject_id , const int tag_id ); 
}; 