
#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Categories {
public:
    static void Create(pqxx::connection &conn,  const std::string category_name , const int filter_id , bool required); 

    static std::string  ReadCategoryName(pqxx::connection &conn, const int category_id); 

    static int  ReadFilterId(pqxx::connection &conn, const int category_id); 

    static bool ReadRequired(pqxx::connection &conn, const int category_id);

    static void UpdateCategoryName(pqxx::connection &conn, std::string old_category_name  , std::string new_category_name ); 

    static void UpdateFilterId(pqxx::connection &conn, std::string category_name , int old_filter_id  , int new_filter_id ); 

    static void UpdateRequired(pqxx::connection &conn, int category_id , bool old_required  , bool new_required ); 

    static void Remove(pqxx::connection &conn, const int category_id ); 
}; 