#include "CreateAllTables.hpp"
#include "ForTableInternal.hpp"

void CreateAllTables(pqxx::connection &conn  ) {
    try {
        pqxx::work txn(conn); 
        std::string filename = "CreateAllTable.sql";
        std::string sql = ReturnSqlRequesInFile(filename); 

        txn.exec(sql); 
        txn.commit(); 
        std::cout << "Таблица создана успешно." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Ошибка при создании таблицы -->  " << e.what() << std::endl;
    }

}

