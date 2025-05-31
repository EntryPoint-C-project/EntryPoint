#pragma once 
#include <iostream>
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>


class Role {
private: 
    int role_id;
    std::string role_name;

public : 
    Role( std::string role_name) :  role_name(role_name){}

    void SetPrimaryKey(int id) { role_id = id; }
    int GetPrimaryKey() const { return role_id; }
    std::string GetRoleName() const { return role_name; }

}; 

int CreateRole(pqxx::transaction_base& txn , const std::string &role_name) ;
std::string ReadRole(pqxx::transaction_base& txn , int role_id) ;
void UpdateRole(pqxx::transaction_base& txn, int role_id, std::string new_role_name) ;
void  DeleteRole(pqxx::transaction_base& txn, int role_id) ;