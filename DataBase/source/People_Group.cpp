#include "People_Group.hpp"

int CreatePeopleGroup(pqxx::transaction_base& txn , const std::string &people_group_name) {
    if ( people_group_name.empty() ) {
        fmt::print("Заполните все поля\n");
        throw std::invalid_argument("Заполните все поля");
    }
    try {
        std::string sql =  "INSERT INTO people_group (people_group_name) VALUES ($1)  ReTURNING people_group_id";

        pqxx::result res = txn.exec_params(sql, people_group_name);
        int people_group_id ; 
        if ( !res.empty() ) {
            people_group_id = res[0]["people_group_id"].as<int>();
        }else {
            fmt::print("Запись уже существует с указанным people_group_name\n");
        }
        //txn.commit() ; 
        return people_group_id;

        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", people_group_name, e.what()) ;
        throw ; 
    }
}


std::string ReadPeopleGroup(pqxx::transaction_base& txn , int people_group_id) {
    try {

        std::string sql =  "SELECT people_group_name FROM people_group WHERE people_group_id = $1";
        pqxx::result res = txn.exec_params(sql, people_group_id);
        //txn.commit();
        std::string people_group_name = res[0]["people_group_name"].as<std::string>();
        return people_group_name;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", people_group_id, e.what()) ;
        throw ; 
    }
}

void UpdatePeopleGroup(pqxx::transaction_base& txn, int people_group_id, std::string new_people_group_name) {
    try {

        std::string sql =  "UPDATE people_group SET people_group_name = $1 WHERE people_group_id = $2";
        txn.exec_params(sql, new_people_group_name, people_group_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", people_group_id, e.what()) ;
        throw ; 
    }
}

void DeletePersonGroup(pqxx::transaction_base& txn, int people_group_id) {
    try {
        std::string sql =  "DELETE FROM people_group WHERE people_group_id = $1";
        txn.exec_params(sql, people_group_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при удалении {}: {}", people_group_id, e.what()) ;
        throw ; 
    }
}

bool IsThereARecordPeopleGroup(pqxx::transaction_base& txn, std::string people_group_name) {
    try {
        std::string sql =  " SELECt EXISTS("
                           "SELECT 1 FROM people_group WHERE people_group_name = $1"
                           ")";
        pqxx::result res = txn.exec_params(sql, people_group_name);
        return res[0][0].as<bool>();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", people_group_name, e.what()) ;
        throw ;
    }
}

int ReadPeopleGroupId(pqxx::transaction_base& txn , std::string people_group_name) {
    try {
        
        std::string sql =  "SELECT people_group_id FROM people_group WHERE people_group_name = $1";
        pqxx::result res = txn.exec_params(sql, people_group_name);
        //txn.commit();
        int people_group_id = res[0]["people_group_id"].as<int>();
        return people_group_id;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", people_group_name, e.what()) ;
        throw ; 
    }
}