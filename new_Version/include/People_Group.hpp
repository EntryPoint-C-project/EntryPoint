#pragma once 
#include <iostream>
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>


class People_Group {
private: 
    int people_group_id;
    std::string people_group_name;

public : 
    People_Group( std::string people_group_name) :  people_group_name(people_group_name){}

    void SetPrimaryKey(int id) { people_group_id = id; }
    int GetPrimaryKey() const { return people_group_id; }
    std::string GetGroupName() const { return people_group_name; }

}; 

int CreatePeopleGroup(pqxx::transaction_base& txn , const std::string &people_group_name) ;
std::string ReadPeopleGroup(pqxx::transaction_base& txn , int people_group_id) ;

bool IsThereARecordPeopleGroup(pqxx::transaction_base& txn, std::string people_group_name) ;
void UpdatePeopleGroup(pqxx::transaction_base& txn, int people_group_id, std::string new_people_group_name) ;
void  DeletePersonGroup(pqxx::transaction_base& txn, int people_group_id) ;