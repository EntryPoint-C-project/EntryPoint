#include "inc/Programs.hpp"

static void Create(pqxx::connection &conn,  const std::string program_name) {
    try {
        pqxx::work txn(conn) ; 
        std::string sql = "INSERT INTO Programs (program_name) VALUE  ($1))"; 

        txn.exec_params(sql, program_name) ; 
        txn.commit(); 
        std::cout << std::string("Новая запись в таблицу Programs была успешна добавлено , с содержанием ") + program_name + "\n" ; 

    } catch(const std::exception &e){
        std::cout << "Произошла ошибка во время добавления новой программы : " << e.what() << std::endl; 
    }
}

static std::string  Read(pqxx::connection &conn, const int program_id) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "SELECT program_name FROM Programs WHERE program_id = $1";
        pqxx::result res = txn.exec_params(sql , program_id); 
        std::string program_name = res[0][0].as<std::string>(); 
        txn.commit(); 
        std::cout << "Данные о программах с ID: " << program_id << " были успешно добавлены в вектор vec_program_id\n";
        return program_name;

    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе program_name для " <<  program_id << std::endl; 
        return {}; 
    }
}



static void Update(pqxx::connection &conn, std::string old_program_name  , std::string new_program_name ) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "UPDATE Programs SET program_name = $1 WHERE program_name = $2";
        txn.exec_params(sql , new_program_name , old_program_name);
        txn.commit();
        std::cout << "Программа  поменяла названин  с  " << old_program_name << " --> " << new_program_name << std::endl; 
    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе program_id для " <<  old_program_name << std::endl;
    }

}

static void Remove(pqxx::connection &conn, const int program_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Programs WHERE program_id = $1; ";

        txn.exec_params(sql,  program_id);
        txn.commit();
        std::cout << "Программа с ID: " << program_id << " была успешно удалена из таблицы Programs" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении программы с ID: " << program_id <<  e.what() << std::endl;
    }

}
