
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
        fmt::print("✓ Connected to: {}\n", conn.dbname());

        std::string sql = 
            "DROP TABLE IF EXISTS "
                "Result_Request, "
                "Feedback_URL, "
                "Feedback_Request, "
                "People_Subject, "
                "Teacher_Subject, "
                "Students, "
                "Subjects, "
                "Person_Role, " 
                "Roles, "
                "People, "
                "Programs, " 
                "Tags, "
                "Subject_Tags, "
                "Filters, "
                "Filter_Includes, "
                "Filter_Excludes, "
                "Categories, "  
                "Category_Tags, " 
                "Person_Filter_Access, "
                "Feedbacks, "          
                "Feedback_Participants " 
            "CASCADE;"; 
        txn.exec(sql ); 
        txn.commit(); 
        fmt::print("all deleted )))") ; 
    }catch( const std::exception &e){
        fmt::print("Error: {}\n", e.what());
    }
    return 0 ; 
}