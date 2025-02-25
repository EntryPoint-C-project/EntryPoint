#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Person_Filter_Access {
public:
    static void Create(pqxx::connection &conn, const int person_id , const int filter_id ); 

    static std::vector <int>  ReadFilterId(pqxx::connection &conn, const int person_id); 

    static std::vector <int>  ReadPersonId(pqxx::connection &conn, const int filter_id); 

    static void Update(pqxx::connection &conn, const int old_person_id , const int old_filter_id , const int new_person_id , const int new_filter_id ); 

    static void Remove(pqxx::connection &conn, const int person_id , const int filter_id ); 
}; 