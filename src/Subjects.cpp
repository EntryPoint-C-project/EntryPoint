#include "inc/Subjects.hpp"

static void Create(pqxx::connection &conn,  const std::string subject_name) {
    try {
        pqxx::work txn(conn) ; 
        std::string sql = "INSERT INTO Subjects (subject_name) VALUE  ($1))"; 

        txn.exec_params(sql, subject_name) ; 
        txn.commit(); 
        std::cout << std::string("Новая запись в таблицу Subjects была успешна добавлено , с содержанием ") + subject_name + "\n" ; 

    } catch(const std::exception &e){
        std::cout << "Произошла ошибка во время добавления новой программы : " << e.what() << std::endl; 
    }
}

static std::string  Read(pqxx::connection &conn, const int subject_id) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "SELECT subject_name FROM Subjects WHERE subject_id = $1";
        pqxx::result res = txn.exec_params(sql , subject_id); 
        std::string subject_name = res[0][0].as<std::string>(); 
        txn.commit(); 
        std::cout << "Данные о предмеих с ID: " << subject_id << " были успешно добавлены в вектор subject_id\n";
        return subject_name;

    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе subject_name для " <<  subject_id << std::endl; 
        return {}; 
    }
}



static void Update(pqxx::connection &conn, std::string old_subject_name  , std::string new_subject_name ) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "UPDATE Subjects SET subject_name = $1 WHERE subject_name = $2";
        txn.exec_params(sql , new_subject_name , old_subject_name);
        txn.commit();
        std::cout << "предмет  поменял названин  с  " << old_subject_name << " --> " << new_subject_name << std::endl; 
    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе subject_id для " <<  old_subject_name << std::endl;
    }

}

static void Remove(pqxx::connection &conn, const int subject_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Subjects WHERE subject_id = $1; ";

        txn.exec_params(sql,  subject_id);
        txn.commit();
        std::cout << "предмет с ID: " << subject_id << " был успешно удален из таблицы Subjects" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении предмета с ID: " << subject_id <<  e.what() << std::endl;
    }

}
