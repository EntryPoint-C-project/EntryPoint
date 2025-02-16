
#ifndef FUNCTIONS_FOR_CREATE_ALL_TABLES_
#define FUNCTIONS_FOR_CREATE_ALL_TABLES_
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pqxx/pqxx>
#include <utility>
#include <iomanip>



std::string ReturnSqlRequesInFile( std::string &filename) ; 

void DropAllTables(pqxx::connection &conn , std::string &filename); 

void CreateAllTables(pqxx::connection &conn , std::string &filename ) ;

void CheckSubtableExsitence(pqxx::work &txn, const std::string &sql) ; 

void CheckTableExistence(pqxx::connection &conn) ; 
#endif //FUNCTIONS_FOR_CREATE_ALL_TABLES_
