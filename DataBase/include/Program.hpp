#pragma once 
#include <iostream>
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>


class Program {
private: 
    int program_id;
    std::string program_name;

public : 
    Program( std::string program_name) :  program_name(program_name){}

    void SetPrimaryKey(int id) { program_id = id; }
    int GetPrimaryKey() const { return program_id; }
    std::string GetProgramName() const { return program_name; }


}; 
int CreateProgram(pqxx::transaction_base& txn , const std::string &program_name) ;
std::string ReadProgram(pqxx::transaction_base& txn , int program_id) ;
int ReadProgramId(pqxx::transaction_base& txn , std::string program_name) ;

bool IsThereARecordProgram(pqxx::transaction_base& txn, std::string program_name) ;
void UpdateProgram(pqxx::transaction_base& txn, int program_id, std::string new_program_name) ;
void  DeleteProgram(pqxx::transaction_base& txn, int program_id) ;