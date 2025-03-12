
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <iostream>
#include <vector>

int main() {
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";

    try {
        // Подключение к БД
        pqxx::connection conn(conn_str);
        pqxx::work txn(conn); 
        if (!conn.is_open()) {
            throw std::runtime_error("Connection failed");
        }
        fmt::print("✓ Подключено к: {}\n", conn.dbname());

        std::string sql =  "CREATE TABLE Feedback_URL (\n"
            "result_id INT REFERENCES Result(result_id) ON DELETE CASCADE NOT NULL,\n"
            "request_id INT REFERENCES Feedback_Request(request_id) ON DELETE CASCADE NOT NULL,\n"
            "PRIMARY KEY (result_id, request_id)\n"
            ");";
        txn.exec(sql ); 
        txn.commit(); 
        fmt::print("Создалась)))") ;
    }catch( const std::exception &e){
        fmt::print("произошла ошибка : {}\n", e.what());
    }
    return 0 ; 
}