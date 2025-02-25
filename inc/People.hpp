#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class People {
public:
    static void Create(pqxx::connection &conn,  const std::string first_name , const std::string last_name , const std::string tg_nick); 

    static std::string  ReadAllInformation(pqxx::connection &conn, const int person_id); // first_name , last_name , tg_nick  

    static int ReadPersonId(pqxx::connection &conn , std::string tg_nick ); 

    static void Update(pqxx::connection &conn, std::string old_tg_nick  , std::string new_tg_nick ); 

    static void Remove(pqxx::connection &conn, const int person_id );

    static void Remove(pqxx::connection &conn, const int tg_nick ); 
}; 