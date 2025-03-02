#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Category_Tags {
public:
    static void Create(pqxx::connection &conn, const int category_id , const int   tag_id ); 

    static std::vector <int>  ReadTagId(pqxx::connection &conn, const int category_id); 

    static std::vector <int>  ReadCategorytId(pqxx::connection &conn, const int tag_id); 

    static void Update(pqxx::connection &conn, const int old_category_id , const int old_tag_id , const int new_category_id , const int new_tag_id ); 

    static void Remove(pqxx::connection &conn, const int category_id , const int tag_id ); 
}; 