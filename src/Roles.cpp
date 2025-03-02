#include "inc/Roles.hpp"

static void Create(pqxx::connection &conn , const std::string role_name) {
    try {
        pqxx::work txn(conn) ; 
        std::string sql_for_insert_role_name = "INSERT INTO Roles (role_name) VALUE  ($1))"; 

        txn.exec_params(sql_for_insert_role_name, role_name) ; 
        txn.commit(); 
        std::cout << std::string("Новая запись в таблицу Roles была успешна добавлено , с содержанием ") + role_name + "\n" ; 

    } catch(const std::exception &e){
        std::cout << "Произошла ошибка во время добавления новой персонажа с ролью  : " << e.what() << std::endl; 
    }
}

static std::string  Read(pqxx::connection &conn, const int role_id) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "SELECT role_name FROM Roles WHERE role_id = $1";
        pqxx::result res = txn.exec_params(sql , role_id); 
        std::string role_name = res[0][0].as<std::string>(); 
        txn.commit(); 
        std::cout << "Данные о ролях пользователя с ID: " << role_id << " были успешно добавлены в вектор vec_role_id\n";
        return role_name;

    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе role_name для " <<  role_id << std::endl; 
        return {}; 
    }
}



static void Update(pqxx::connection &conn, const std::string old_role_name  ,const  std::string new_role_name ) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "UPDATE Roles SET role_name = $1 WHERE role_name = $2";
        txn.exec_params(sql , new_role_name , old_role_name);
        txn.commit();
        std::cout << "Роль сменилась с  " << old_role_name << " --> " << new_role_name << std::endl; 
    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе role_id для " <<  old_role_name << std::endl;
    }

}

static void Remove(pqxx::connection &conn, const int role_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Roles WHERE role_id = $1; ";

        txn.exec_params(sql,  role_id);
        txn.commit();
        std::cout << "Роль с ID: " << role_id << " была успешно удалена из таблицы Roles" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении роли с ID: " << role_id <<  e.what() << std::endl;
    }

}
