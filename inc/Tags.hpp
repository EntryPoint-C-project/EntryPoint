
#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Tags {
public:
    static void Create(pqxx::connection &conn,  const std::string tag_name); 

    static std::string  Read(pqxx::connection &conn, const int tag_id); 

    static void Update(pqxx::connection &conn, std::string old_tag_name  , std::string new_tag_name ); 

    static void Remove(pqxx::connection &conn, const int tag_id ); 
}; 