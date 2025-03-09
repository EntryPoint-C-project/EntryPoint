
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

        std::string sql = "CREATE TABLE Filter_Excludes ("
            "filter_id INT REFERENCES Filters(filter_id) ON DELETE CASCADE NOT NULL,"
            "subject_id INT REFERENCES Subjects(subject_id) ON DELETE CASCADE NOT NULL,"
            "PRIMARY KEY (filter_id, subject_id)"
        ");" ;

        txn.exec(sql);
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}