#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Filter_Excludes {
public:
    static void Create(pqxx::connection &conn, const int filter_id , const int   tag_id ); 

    static std::vector <int>  ReadTagId(pqxx::connection &conn, const int filter_id); 

    static std::vector <int>  ReadFiltertId(pqxx::connection &conn, const int tag_id); 

    static void Update(pqxx::connection &conn, const int old_filter_id , const int old_tag_id , const int new_filter_id , const int new_tag_id ); 

    static void Remove(pqxx::connection &conn, const int filter_id , const int tag_id ); 
}; 