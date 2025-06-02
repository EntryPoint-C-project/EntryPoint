#include "InteractionsWithTables.hpp"

std::string ReadFileWithSql(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("No find file :  " + file_path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void CreateAllTable(pqxx::transaction_base& txn) {
     try {

        // chdir("/path/to/directory");
        std::string sql =  ReadFileWithSql("CreateAllTable.sql");
        txn.exec(sql ); 
        // //txn.commit(); 
        fmt::print("All tables created)))") ; 
    }catch( const std::exception &e){
        fmt::print("Error: {}\n", e.what());
    }
}

void DeleteAllTable(pqxx::transaction_base& txn) {
    try {
        std::string sql =  ReadFileWithSql("DeleteAllTable.sql");
        txn.exec(sql ); 
        // //txn.commit(); 
        fmt::print("All tables deleted)))") ; 
    }catch( const std::exception &e){
        fmt::print("Error: {}\n", e.what());
    }
}

void DeleteTable(pqxx::transaction_base& txn, const std::string &table_name) {
    try {

        std::string sql = "DROP TABLE IF EXISTS " + table_name ;
        txn.exec(sql ); 
        //txn.commit(); 
        fmt::print("All tables deleted)))") ;

    }catch( const std::exception &e){
        fmt::print("Error: {}\n", e.what());
    }
}