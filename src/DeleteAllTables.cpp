#include "DeleteAllTables.hpp"
#include "ForTableInternal.hpp"

void DropAllTables(pqxx::connection &conn ){
    try{
        pqxx::work txn(conn) ; 
        std::string filename = "DropAllTable.sql" ; 
        std::string sql = ReturnSqlRequesInFile(filename); 

        txn.exec(sql); 
        txn.commit(); 
        std::cout << "Все таблицы были успешно удалены\n";  
    }
    catch (const std::exception &e) {
        std::cerr << "Ошибка при Удалении таблицы --> " << e.what() << std::endl;
    }
    

}