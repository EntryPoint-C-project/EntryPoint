
#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Programs {
public:
    static void Create(pqxx::connection &conn,  const std::string program_name); 

    static std::string  Read(pqxx::connection &conn, const int program_id); 

    static void Update(pqxx::connection &conn, std::string old_program_name  , std::string new_program_name ); 

    static void Remove(pqxx::connection &conn, const int program_id ); 
}; 