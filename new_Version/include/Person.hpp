#pragma once 
#include <iostream>
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>

class People {
private: 
    int person_id; // pk 
    std::string first_name ;
    std::string last_name ;
    std::string tg_nick ;
    int access ; //fk
    int snils; 

public: 
    People( const std::string &first_name, const std::string &last_name, const std::string &tg_nick ,int access , int snils) :  first_name(first_name), last_name(last_name), tg_nick(tg_nick) , access(access) , snils(snils){}

    int GetPrimaryKey() const { return person_id; }
    std::string GetFirstName() const { return first_name; }
    std::string GetLastName() const { return last_name; }
    std::string GetTgNick() const { return tg_nick; }
    int GetAccess() const { return access; }
    int GetSnils() const { return snils; }
    void SetPrimaryKey(int id) { person_id = id; }

};

int CreatePerson(pqxx::transaction_base& txn , const std::string first_name , const std::string last_name, const std::string tg_nick , int access , int snils) ; 
std::tuple< std::string, std::string, std::string , int , int > ReadPerson(pqxx::transaction_base& txn , int person_id) ;//! исправить все места 
void DeletePerson(pqxx::transaction_base& txn, std::string tg_nick  ) ;    