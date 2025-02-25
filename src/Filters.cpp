#include "inc/Filters.hpp"

static void Create(pqxx::connection &conn,  const std::string filter_name) {
    try {
        pqxx::work txn(conn) ; 
        std::string sql = "INSERT INTO Filters (filter_name) VALUE  ($1))"; 

        txn.exec_params(sql, filter_name) ; 
        txn.commit(); 
        std::cout << std::string("Новая запись в таблицу Filters была успешна добавлено , с содержанием ") + filter_name + "\n" ; 

    } catch(const std::exception &e){
        std::cout << "Произошла ошибка во время добавления нового фильтра : " << e.what() << std::endl; 
    }
}

static std::string  Read(pqxx::connection &conn, const int filter_id) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "SELECT filter_name FROM Filters WHERE filter_id = $1";
        pqxx::result res = txn.exec_params(sql , filter_id); 
        std::string filter_name = res[0][0].as<std::string>(); 
        txn.commit(); 
        std::cout << "Данные о Фильтре с ID: " << filter_id << " были успешно добавлены в вектор filter_id\n";
        return filter_name;

    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе filter_name для " <<  filter_id << std::endl; 
        return {}; 
    }
}




static void Update(pqxx::connection &conn, std::string old_filter_name  , std::string new_filter_name ) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "UPDATE Filters SET filter_name = $1 WHERE filter_name = $2";
        txn.exec_params(sql , new_filter_name , old_filter_name);
        txn.commit();
        std::cout << "Фильтр  поменял названин  с  " << old_filter_name << " --> " << new_filter_name << std::endl; 
    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе filter_id для " <<  old_filter_name << std::endl;
    }

}

static void Remove(pqxx::connection &conn, const int filter_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Filters WHERE filter_id = $1; ";

        txn.exec_params(sql,  filter_id);
        txn.commit();
        std::cout << "Фильтр с ID: " << filter_id << " был успешно удален из таблицы Filters" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении Фильтра с ID: " << filter_id <<  e.what() << std::endl;
    }

}
