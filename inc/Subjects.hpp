
#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Subjects {
public:
    static void Create(pqxx::connection &conn,  const std::string subject_name); 

    static std::string  Read(pqxx::connection &conn, const int subject_id); 

    static void Update(pqxx::connection &conn, std::string old_subject_name  , std::string new_subject_name ); 

    static void Remove(pqxx::connection &conn, const int subject_id ); 
}; 