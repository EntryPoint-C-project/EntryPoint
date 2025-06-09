#include "Teaching_Assigment.hpp"

int CreateTeachingAssigment(pqxx::transaction_base& txn , int person_id, int offer_id, int subject_id) {
    if ( person_id < 1 || offer_id < 1 || subject_id < 1 ) {
        fmt::print("Заполните все поля\n");
        throw std::invalid_argument("Заполните все поля");
    }
    
    try {
        std::string sql =  "INSERT INTO Teaching_Assigment (person_id, offer_id, subject_id) VALUES ($1, $2, $3)  ReTURNING assignment_id";

        pqxx::result res = txn.exec_params(sql, person_id, offer_id, subject_id);
        int assignment_id ; 
        if ( !res.empty() ) {
            assignment_id = res[0]["assignment_id"].as<int>();
        }else {
            fmt::print("Запись уже существует с указанным person_id, offer_id, subject_id\n");
        }
        return assignment_id;

    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", person_id, e.what()) ;
        throw ; 
    }

}



std::tuple < int , int , int > ReadTeachingAssigment(pqxx::transaction_base& txn , int assignment_id) {
    try {
        
        std::string sql =  "SELECT person_id, offer_id, subject_id FROM Teaching_Assigment WHERE assignment_id = $1";
        pqxx::result res = txn.exec_params(sql, assignment_id);
        // //txn.commit();
        int person_id = res[0]["person_id"].as<int>();
        int offer_id = res[0]["offer_id"].as<int>();
        int subject_id = res[0]["subject_id"].as<int>();
        return {person_id, offer_id, subject_id};
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", assignment_id, e.what()) ;
        throw ; 
    }
}

std::vector< std::pair<int , int > > ReadInfoOnPersonId(pqxx::transaction_base& txn , int person_id) {
    try {
        
        std::string sql =  "SELECT offer_id, subject_id FROM Teaching_Assigment WHERE person_id = $1";
        pqxx::result res = txn.exec_params(sql, person_id);
        // //txn.commit();
        if (res.empty()) {
            fmt::print("Для person_id = {} нет данных в Teaching_Assigment\n", person_id);
        }
        std::vector< std::pair<int , int > > info;
        for (auto row : res) {
            int offer_id = row["offer_id"].is_null() ? -1 : row["offer_id"].as<int>();
            int subject_id = row["subject_id"].is_null() ? -1 : row["subject_id"].as<int>();
            info.emplace_back(offer_id, subject_id);
        }
        return info;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", person_id, e.what()) ;
        throw ;
    }
}

std::vector<std::pair <int, int> > ReadInfoOnOfferIdNoStudents(pqxx::transaction_base& txn , int offer_id) {
    try {
        
        std::string sql =  "SELECT person_id, subject_id FROM Teaching_Assigment WHERE offer_id = $1 AND subject_id != $2";
        int subject_id = ReadSubjectId(txn, "Student");
        pqxx::result res = txn.exec_params(sql, offer_id , subject_id);
        // //txn.commit();
        if (res.empty()) {
            fmt::print("Для offer_id = {} нет данных в Teaching_Assigment\n", offer_id);
        }
        std::vector<std::pair <int, int> > info;
        for (auto row : res) {
            int person_id = row["person_id"].is_null() ? -1 : row["person_id"].as<int>();
            int subject_id = row["subject_id"].is_null() ? -1 : row["subject_id"].as<int>();
            info.emplace_back(person_id, subject_id);
        }
        return info;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", offer_id, e.what()) ;
        throw ;
    }
}

void UpdateTeachingAssigment(pqxx::transaction_base& txn, int assignment_id, int person_id, int offer_id, int subject_id) {
    try {
        
        std::string sql =  "UPDATE Teaching_Assigment SET person_id = $1, offer_id = $2, subject_id = $3 WHERE assignment_id = $4";
        txn.exec_params(sql, person_id, offer_id, subject_id, assignment_id);
        // //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", assignment_id, e.what()) ;
        throw ; 
    }
}

void DeleteTeachingAssigment(pqxx::transaction_base& txn, int assignment_id) {
    try {
        
        std::string sql =  "DELETE FROM Teaching_Assigment WHERE assignment_id = $1";
        txn.exec_params(sql, assignment_id);
        // //txn.commit();
    } catch (const std::exception &e) {
        txn.abort();
        fmt::print("Ошибка при удалении {}: {}", assignment_id, e.what()) ;
        throw ; 
    }
}

bool IsThereARecordTeachingAssigment(pqxx::transaction_base& txn, int person_id , int offer_id , int subject_id) {
    try {
        
        std::string sql =  " SELECt EXISTS("
                           "SELECT 1 FROM Teaching_Assigment WHERE person_id = $1 AND offer_id = $2 AND subject_id = $3"
                           ")";
        pqxx::result res = txn.exec_params(sql, person_id, offer_id, subject_id);
        return res[0][0].as<bool>();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", person_id, e.what()) ;
        throw ;
    }
}

int GetTeachingAssigmentId( pqxx::transaction_base& txn ,int person_id , int offer_id , int subject_id){
    try {
        
        std::string sql =  "SELECT assignment_id FROM Teaching_Assigment WHERE person_id = $1 AND offer_id = $2 AND subject_id = $3";
        pqxx::result res = txn.exec_params(sql, person_id, offer_id, subject_id);
        // //txn.commit();
        return res[0]["assignment_id"].as<int>();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", person_id, e.what()) ;
        throw ; 
    }
}