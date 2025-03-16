#pragma once 
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>



std::string ReadFileWithSql(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("No find file :  " + file_path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";

    try {
        pqxx::connection conn(conn_str);
        pqxx::work txn(conn); 
        if (!conn.is_open()) {
            throw std::runtime_error("Connection failed");
        }
        fmt::print("✓ Connected to: {}\n", conn.dbname());

        std::string sql =  ReadFileWithSql("CreateAllTable.sql");
        txn.exec(sql ); 
        txn.commit(); 
        fmt::print("All tables created)))") ; 
    }catch( const std::exception &e){
        fmt::print("Error: {}\n", e.what());
    }
    return 0 ; 
}