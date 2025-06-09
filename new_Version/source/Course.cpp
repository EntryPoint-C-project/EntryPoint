#include "Course.hpp"

int CreateCourse(pqxx::transaction_base& txn , const std::string &course_name) {
    if ( course_name.empty() ) {
        fmt::print("Заполните все поля\n");
        throw std::invalid_argument("Заполните все поля");
    }
    try {
        std::string sql =  "INSERT INTO Course (course_name) VALUES ($1)  ReTURNING course_id";

        pqxx::result res = txn.exec_params(sql, course_name);
        int course_id ; 
        if ( !res.empty() ) {
            course_id = res[0]["course_id"].as<int>();
        }else {
            fmt::print("Запись уже существует с указанным course_name\n");
        }
        //txn.commit() ; 
        return course_id;

        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", course_name, e.what()) ;
        throw ; 
    }
}


std::string ReadCourse(pqxx::transaction_base& txn , int course_id) {
    try {
        std::string sql =  "SELECT course_name FROM Course WHERE course_id = $1";
        pqxx::result res = txn.exec_params(sql, course_id);
        //txn.commit();
        std::string course_name = res[0]["course_name"].as<std::string>();
        return course_name;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", course_id, e.what()) ;
        throw ; 
    }
}

void UpdateCourse(pqxx::transaction_base& txn, int course_id, std::string cew_Course_name) {
    try {
        std::string sql =  "UPDATE Course SET course_name = $1 WHERE course_id = $2";
        txn.exec_params(sql, cew_Course_name, course_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", course_id, e.what()) ;
        throw ; 
    }
}

void DeleteCourse(pqxx::transaction_base& txn, int course_id) {
    try {
        std::string sql =  "DELETE FROM Course WHERE course_id = $1";
        txn.exec_params(sql, course_id);
        //txn.commit();
    } catch (const std::exception &e) {
        txn.abort();
        fmt::print("Ошибка при удалении {}: {}", course_id, e.what()) ;
        throw ; 
    }
}

bool IsThereARecordCourse(pqxx::transaction_base& txn, std::string course_name) {
    try {
        std::string sql =  " SELECt EXISTS("
                           "SELECT 1 FROM Course WHERE course_name = $1"
                           ")";
        pqxx::result res = txn.exec_params(sql, course_name);
        return res[0][0].as<bool>();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", course_name, e.what()) ;
        throw ;
    }
}

int ReadCourseId(pqxx::transaction_base& txn ,  std::string course_name) {
    try {
        
        std::string sql =  "SELECT course_id FROM Course WHERE course_name = $1";
        pqxx::result res = txn.exec_params(sql, course_name);
        //txn.commit();
        int course_id = res[0]["course_id"].as<int>();
        return course_id;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", course_name, e.what()) ;
        throw ; 
    }
}