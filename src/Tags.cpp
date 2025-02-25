#include "inc/Tags.hpp"

static void Create(pqxx::connection &conn,  const std::string tag_name) {
    try {
        pqxx::work txn(conn) ; 
        std::string sql = "INSERT INTO Tags (tag_name) VALUE  ($1))"; 

        txn.exec_params(sql, tag_name) ; 
        txn.commit(); 
        std::cout << std::string("Новая запись в таблицу Tags была успешна добавлено , с содержанием ") + tag_name + "\n" ; 

    } catch(const std::exception &e){
        std::cout << "Произошла ошибка во время добавления нового тэга : " << e.what() << std::endl; 
    }
}

static std::string  Read(pqxx::connection &conn, const int tag_id) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "SELECT tag_name FROM Tags WHERE tag_id = $1";
        pqxx::result res = txn.exec_params(sql , tag_id); 
        std::string tag_name = res[0][0].as<std::string>(); 
        txn.commit(); 
        std::cout << "Данные о тэге с ID: " << tag_id << " были успешно добавлены в вектор tag_id\n";
        return tag_name;

    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе tag_name для " <<  tag_id << std::endl; 
        return {}; 
    }
}



static void Update(pqxx::connection &conn, std::string old_tag_name  , std::string new_tag_name ) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "UPDATE Tags SET tag_name = $1 WHERE tag_name = $2";
        txn.exec_params(sql , new_tag_name , old_tag_name);
        txn.commit();
        std::cout << "Тэг  поменял названин  с  " << old_tag_name << " --> " << new_tag_name << std::endl; 
    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе tag_id для " <<  old_tag_name << std::endl;
    }

}

static void Remove(pqxx::connection &conn, const int tag_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Tags WHERE tag_id = $1; ";

        txn.exec_params(sql,  tag_id);
        txn.commit();
        std::cout << "Тэг с ID: " << tag_id << " был успешно удален из таблицы Tags" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении Тэга с ID: " << tag_id <<  e.what() << std::endl;
    }

}
