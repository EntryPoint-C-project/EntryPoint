
#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Students {
public:
    static void Create(pqxx::connection &conn,  int person_id , int program_id , std::string info); 

    static int  ReadProgramId(pqxx::connection &conn, const int student_id); 

    static int  ReadPersonId(pqxx::connection &conn, const int student_id); 

    static std::string ReadInfo(pqxx::connection &conn, const int student_id); 

    static void UpdateProgramId(pqxx::connection &conn, int student_id  , int old_program_id , int new_program_id); 

    static void UpdateInfo(pqxx::connection &conn, int student_id  , std::string old_info , std::string new_info); 

    static void Remove(pqxx::connection &conn, const int student_id ); 
}; 