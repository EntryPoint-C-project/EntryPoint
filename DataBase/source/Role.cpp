#include "Role.hpp"

int CreateRole(pqxx::transaction_base& txn , const std::string &role_name) {
    if ( role_name.empty() ) {
        fmt::print("Заполните все поля\n");
        throw std::invalid_argument("Заполните все поля");
    }
    
    try {
        std::string sql =  "INSERT INTO Role (role_name) VALUES ($1)  ReTURNING role_id";

        pqxx::result res = txn.exec_params(sql, role_name);
        int role_id ; 
        if ( !res.empty() ) {
            role_id = res[0]["role_id"].as<int>();
        }else {
            fmt::print("Запись уже существует с указанным role_name\n");
        }
        //txn.commit() ; 
        return role_id;

        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", role_name, e.what()) ;
        throw ; 
    }
}


std::string ReadRole(pqxx::transaction_base& txn , int role_id) {
    try {
        
        std::string sql =  "SELECT role_name FROM Role WHERE role_id = $1";
        pqxx::result res = txn.exec_params(sql, role_id);
        //txn.commit();
        std::string role_name = res[0]["role_name"].as<std::string>();
        return role_name;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", role_id, e.what()) ;
        throw ; 
    }
}

void UpdateRole(pqxx::transaction_base& txn, int role_id, std::string new_role_name) {
    try {
        
        std::string sql =  "UPDATE Role SET role_name = $1 WHERE role_id = $2";
        txn.exec_params(sql, new_role_name, role_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", role_id, e.what()) ;
        throw ; 
    }
}

void DeleteRole(pqxx::transaction_base& txn, int role_id) {
    try {
        
        std::string sql =  "DELETE FROM Role WHERE role_id = $1";
        txn.exec_params(sql, role_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при удалении {}: {}", role_id, e.what()) ;
        throw ; 
    }
}

int  ReadRoleId(pqxx::transaction_base& txn , const std::string &role_name) {
    try {
        
        std::string sql =  "SELECT role_id FROM Role WHERE role_name = $1";
        pqxx::result res = txn.exec_params(sql, role_name);
        if ( res.empty() ) {
            CreateRole(txn, role_name);
            res = txn.exec_params(sql, role_name);
            fmt::print("Запись создана , и добавленно в таблицу Role новое запись : {}\n"  , role_name);
        }
        //txn.commit();
        int role_id = res[0]["role_id"].as<int>();
        return role_id;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", role_name, e.what()) ;
        throw ; 
    }
}