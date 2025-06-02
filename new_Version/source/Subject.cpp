#include "Subject.hpp"

int CreateSubject(pqxx::transaction_base& txn , const std::string &subject_name) {
    if ( subject_name.empty() ) {
        fmt::print("Заполните все поля\n");
        throw std::invalid_argument("Заполните все поля");
    }
    
    try {
        std::string sql =  "INSERT INTO subjects (subject_name) VALUES ($1)  ReTURNING subject_id";

        pqxx::result res = txn.exec_params(sql, subject_name);
        int subject_id ; 
        if ( !res.empty() ) {
            subject_id = res[0]["subject_id"].as<int>();
        }else {
            fmt::print("Запись уже существует с указанным subject_name\n");
        }
        //txn.commit() ; 
        return subject_id;

        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", subject_name, e.what()) ;
        throw ; 
    }
}

int ReadSubjectId(pqxx::transaction_base& txn , const std::string &subject_name) {
    try {
        
        std::string sql =  "SELECT subject_id FROM subjects WHERE subject_name = $1";
        pqxx::result res = txn.exec_params(sql, subject_name);
        //txn.commit();
        int subject_id = res[0]["subject_id"].as<int>();
        return subject_id;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", subject_name, e.what()) ;
        throw ; 
    }
}

std::string ReadSubject(pqxx::transaction_base& txn , int subject_id) { //TODO : нужно чтобы все они встречались один раз --> сделать unique
    try {
        
        std::string sql =  "SELECT subject_name FROM subjects WHERE subject_id = $1";
        pqxx::result res = txn.exec_params(sql, subject_id);
        //txn.commit();
        std::string subject_name = res[0]["subject_name"].as<std::string>();
        return subject_name;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", subject_id, e.what()) ;
        throw ; 
    }
}

void UpdateSubject(pqxx::transaction_base& txn, int subject_id, std::string new_subject_name) {
    try {
        
        std::string sql =  "UPDATE subjects SET subject_name = $1 WHERE subject_id = $2";
        txn.exec_params(sql, new_subject_name, subject_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", subject_id, e.what()) ;
        throw ; 
    }
}

void DeleteSubject(pqxx::transaction_base& txn, int subject_id) {
    try {
        
        std::string sql =  "DELETE FROM subjects WHERE subject_id = $1";
        txn.exec_params(sql, subject_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при удалении {}: {}", subject_id, e.what()) ;
        throw ; 
    }
}

bool IsThereARecordSubject(pqxx::transaction_base& txn, int subject_id) {
    try {
        std::string sql =  " SELECt EXISTS("
                           "SELECT 1 FROM subjects WHERE subject_id = $1"
                           ")";
        pqxx::result res = txn.exec_params(sql, subject_id);
        return res[0][0].as<bool>();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", subject_id, e.what()) ;
        throw ;
    }
}

