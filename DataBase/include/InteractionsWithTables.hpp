#pragma once 
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

std::string ReadFileWithSql(const std::string& file_path) ; 
void CreateAllTable(pqxx::transaction_base& txn) ; 
void DeleteAllTable(pqxx::transaction_base& txn) ;
void DeleteTable(pqxx::transaction_base& txn , const std::string &table_name) ; 
