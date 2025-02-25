
#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Filters {
public:
    static void Create(pqxx::connection &conn,  const std::string filter_name); 

    static std::string  Read(pqxx::connection &conn, const int filter_id); 

    static void Update(pqxx::connection &conn, std::string old_filter_name  , std::string new_filter_name ); 

    static void Remove(pqxx::connection &conn, const int filter_id ); 
}; 