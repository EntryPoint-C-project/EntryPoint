#pragma once
#include <fmt/core.h>
#include <fmt/printf.h>

#include <fstream>
#include <iostream>
#include <pqxx/pqxx>
#include <sstream>
#include <vector>

std::string ReadFileWithSql(const std::string& file_path);
void CreateAllTable(pqxx::transaction_base& txn);
void DeleteAllTable(pqxx::transaction_base& txn);
void DeleteTable(pqxx::transaction_base& txn, const std::string& table_name);