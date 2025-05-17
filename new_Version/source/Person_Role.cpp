#include "Person_Role.hpp"

std::pair<int,int> CreatePersonRole(pqxx::transaction_base& txn , int person_id, int role_id) {
    if (!person_id || !role_id) {
        fmt::print("Заполните все поля\n");
        throw std::invalid_argument("Заполните все поля");
    }

    try {
        std::string sql =  "INSERT INTO Person_Role (person_id, role_id) VALUES ($1, $2) ";
        txn.exec_params(sql, person_id, role_id);
        txn.commit();
        return std::make_pair(person_id, role_id);
    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", person_id, e.what()) ;
        throw ;   
    }
}

std::vector<int> ReadPersonId(pqxx::transaction_base& txn , int role_id) {
    try {

        std::string sql =  "SELECT person_id FROM Person_Role WHERE role_id = $1 GROUP BY person_id";
        pqxx::result res = txn.exec_params(sql, role_id);
        txn.commit();
        std::vector<int> person_ids;
        for (auto row : res) {
            person_ids.push_back(row["person_id"].as<int>());
        }
        return person_ids;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", role_id, e.what()) ;
        throw ; 
    }
}

std::vector<int> ReadRoleId(pqxx::transaction_base& txn , int person_id) {
    try {

        std::string sql =  "SELECT role_id FROM Person_Role WHERE person_id = $1 GROUP BY role_id";
        pqxx::result res = txn.exec_params(sql, person_id);
        txn.commit();
        std::vector<int> role_ids;
        for (auto row : res) {
            role_ids.push_back(row["role_id"].as<int>());
        }
        return role_ids;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", person_id, e.what()) ;
        throw ; 
    }
}

void UpdatePersonRole(pqxx::transaction_base& txn, int person_id, int role_id, int new_person_id, int new_role_id) {
    try {

        std::string sql =  "UPDATE Person_Role SET person_id = $1, role_id = $2 WHERE person_id = $3 AND role_id = $4";
        txn.exec_params(sql, new_person_id, new_role_id, person_id, role_id);
        txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", person_id, e.what()) ;
        throw ; 
    }
}

void DeletePersonRole(pqxx::transaction_base& txn, int person_id, int role_id) {
    try {

        std::string sql =  "DELETE FROM Person_Role WHERE person_id = $1 AND role_id = $2";
        txn.exec_params(sql, person_id, role_id);
        txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при удалении {}: {}", person_id, e.what()) ;
        throw ; 
    }
}