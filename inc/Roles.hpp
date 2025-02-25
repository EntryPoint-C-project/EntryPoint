
#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Roles {
public:
    static void Create(pqxx::connection &conn,  const std::string role_name); 

    static std::string  Read(pqxx::connection &conn, const int role_id); 

    static void Update(pqxx::connection &conn, const std::string old_role_name  , const std::string new_role_name ); 

    static void Remove(pqxx::connection &conn, const int role_id ); 
}; 