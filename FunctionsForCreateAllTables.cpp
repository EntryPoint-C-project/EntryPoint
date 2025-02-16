#include "FunctionsForCreateAllTables.hpp"



std::string ReturnSqlRequesInFile( std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть  файл: " + filename);
    }
    std::stringstream buffer;
    buffer << file.rdbuf(); 
    return buffer.str();
}

void DropAllTables(pqxx::connection &conn , std::string &filenname){
    try{
        pqxx::work txn(conn) ; 
        std::string filename = ""; 
        std::string sql = ReturnSqlRequesInFile(filename); 

        txn.exec(sql); 
        txn.commit(); 
        std::cout << "Все таблицы были успешно удалены\n";  
    }catch (const std::exception &e) {
        std::cerr << "Ошибка при Удалении таблицы: " << e.what() << std::endl;
    }

}

void CreateAllTables(pqxx::connection &conn , std::string &filename ) {
    try {
        pqxx::work txn(conn); 
        std::string filename = "CreateAllTable.sql";
        std::string sql = ReturnSqlRequesInFile(filename); 

        txn.exec(sql); 
        txn.commit(); 
        std::cout << "Таблица создана успешно." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Ошибка при создании таблицы: " << e.what() << std::endl;
    }

}

void CheckSubtableExsitence(pqxx::work &txn, const std::string &sql) {
    pqxx::result result = txn.exec(sql);

    if (result.size() > 0 && !result[0][0].is_null()) {
        std::cout << "Таблица существует в базе данных." << std::endl;
    } else {
        std::cout << "Таблица не существует." << std::endl;
    }
}

void CheckTableExistence(pqxx::connection &conn) {
    try {
        pqxx::work txn(conn);


        std::vector<std::string> sqlQueries = {
            "SELECT to_regclass('public.\"Programs\"');",
            "SELECT to_regclass('public.\"People\"');",
            "SELECT to_regclass('public.\"Roles\"');",
            "SELECT to_regclass('public.\"Students\"');",
            "SELECT to_regclass('public.\"Person_Role\"');",
            "SELECT to_regclass('public.\"Subjects\"');",
            "SELECT to_regclass('public.\"Teacher_Subject\"');",
            "SELECT to_regclass('public.\"People_Subject\"');",
            "SELECT to_regclass('public.\"Feedbacks\"');",
            "SELECT to_regclass('public.\"Feedback_Participants\"');",
            "SELECT to_regclass('public.\"Tags\"');",
            "SELECT to_regclass('public.\"Subject_Tags\"');",
            "SELECT to_regclass('public.\"Filters\"');",
            "SELECT to_regclass('public.\"Filter_Includes\"');",
            "SELECT to_regclass('public.\"Filter_Excludes\"');",
            "SELECT to_regclass('public.\"Catagories\"');",
            "SELECT to_regclass('public.\"Category_Tags\"');",
            "SELECT to_regclass('public.\"Person_Filter_Access\"');"
        };

        for (const auto &sql : sqlQueries) {
            CheckSubtableExsitence(txn, sql);
        }

    } catch (const std::exception &e) {
        std::cerr << "Ошибка при проверке существования таблицы: " << e.what() << std::endl;
    }
}