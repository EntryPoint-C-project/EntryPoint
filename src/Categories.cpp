#include "Categories.hpp"


static void Create(pqxx::connection &conn,  const std::string category_name , const int filter_id , bool required) {
    try {
        pqxx::work txn(conn);
        std::string sql = "INSERT INTO Categories (category_name , filter_id , required) VALUE  ($1 , $2 , $3)"; 

        txn.exec_params(sql, category_name , filter_id , required) ; 
        txn.commit(); 
        std::cout << std::string("Новая запись в таблицу Categories была успешна добавлено , с содержанием ") + category_name + "\n" ;
    }catch (const std::exception &e){
        std::cout << "Произошла ошибка во время добавления новой категории : " << e.what() << std::endl; 
    }
}

static std::string  ReadCategoryName(pqxx::connection &conn, const int category_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT category_name FROM Categories WHERE category_id = $1";
        pqxx::result res  = txn.exec_params(sql, category_id);
        std::string category_name = res[0][0].as<std::string>();
        std::cout << "Категория с названием " << category_name << " была успешно прочитана\n";
        txn.commit(); 
        return category_name; 
    }catch (const std::exception &e){
        std::cout << "Произошла ошибка во время чтения категории : " << e.what() << std::endl;
    }
}

static int  ReadFilterId(pqxx::connection &conn, const int category_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT filter_id FROM Categories WHERE category_id = $1";
        pqxx::result res  = txn.exec_params(sql, category_id);
        int filter_id = res[0][0].as<int>();
        std::cout << "Фильтр с id " << filter_id << " был успешно прочитан\n";
        txn.commit(); 
        return filter_id; 
    }catch (const std::exception &e){
        std::cout << "Произошла ошибка во время чтения фильтра : " << e.what() << std::endl;
    }
}

static bool ReadRequired(pqxx::connection &conn, const int category_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT required FROM Categories WHERE category_id = $1";
        pqxx::result res  = txn.exec_params(sql, category_id);
        bool required = res[0][0].as<bool>();
        std::cout << "required " << required << " был успешно прочитан\n";
        txn.commit(); 
        return required; 
    }catch (const std::exception &e){
        std::cout << "Произошла ошибка во время чтения required : " << e.what() << std::endl;
    }
}

static void UpdateCategoryName(pqxx::connection &conn, std::string old_category_name  , std::string new_category_name ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "UPDATE Categories SET category_name = $1 WHERE category_name = $2";
        txn.exec_params(sql, new_category_name , old_category_name) ; 
        txn.commit(); 
        std::cout << "Запись в таблицу Categories с названием " << old_category_name << " была успешно обновлена\n";
    }catch (const std::exception &e){
        std::cout << "Произошла ошибка во время обновления записи в таблице Categories : " << e.what() << std::endl;
    }
}

static void UpdateFilterId(pqxx::connection &conn, std::string category_name , int old_filter_id  , int new_filter_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "UPDATE Categories SET filter_id = $1 WHERE category_name = $2 AND filter_id = $3";
        txn.exec_params(sql, new_filter_id , category_name , old_filter_id) ; 
        txn.commit(); 
        std::cout << "Запись в таблицу Categories с названием " << category_name << " была успешно обновлена\n";
    }catch (const std::exception &e){
        std::cout << "Произошла ошибка во время обновления записи в таблице Categories : " << e.what() << std::endl;
    }
} 

static void UpdateRequired(pqxx::connection &conn, int category_id , bool old_required  , bool new_required ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "UPDATE Categories SET required = $1 WHERE category_id = $2 AND required = $3";
        txn.exec_params(sql, new_required , category_id , old_required) ; 
        txn.commit(); 
        std::cout << "Запись в таблицу Categories с id " << category_id << " была успешно обновлена\n";
    }catch (const std::exception &e){
        std::cout << "Произошла ошибка во время обновления записи в таблице Categories : " << e.what() << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int category_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Categories WHERE category_id = $1; ";        
        txn.exec_params(sql,  category_id);
        txn.commit(); 
        std::cout << "Запись в таблицу Categories с id " << category_id << " была успешно удалена\n";
    }catch (const std::exception &e){
        std::cout << "Произошла ошибка во время удаления записи в таблице Categories : " << e.what() << std::endl;
    }
}