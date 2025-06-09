#include "Subject_Offer.hpp"

int CreateSubjectOffer(pqxx::transaction_base& txn , int people_group_id, int program_id, int course_id) {
    if ( people_group_id < 1 || program_id < 1 || course_id < 1 ) {
        fmt::print("Заполните все поля\n");
        throw std::invalid_argument("Заполните все поля");
    }
    
    try {
        std::string sql =  "INSERT INTO subject_offer (people_group_id, program_id, course_id) VALUES ($1, $2, $3)  ReTURNING offer_id";

        pqxx::result res = txn.exec_params(sql, people_group_id, program_id, course_id);
        int offer_id ; 
        if ( !res.empty() ) {
            offer_id = res[0]["offer_id"].as<int>();
        }else {
            fmt::print("Запись уже существует с указанным people_group_id, program_id, course_id\n");
        }
        //txn.commit() ; 
        return offer_id;

    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", people_group_id, e.what()) ;
        throw ; 
    }

}



std::tuple < int , int , int > ReadSubjectOffer(pqxx::transaction_base& txn , int offer_id) {
    try {
        
        std::string sql =  "SELECT people_group_id, program_id, course_id FROM subject_offer WHERE offer_id = $1";
        pqxx::result res = txn.exec_params(sql, offer_id);
        //txn.commit();
        int people_group_id = res[0]["people_group_id"].as<int>();
        int program_id = res[0]["program_id"].as<int>();
        int course_id = res[0]["course_id"].as<int>();
        return {people_group_id, program_id, course_id};
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", offer_id, e.what()) ;
        throw ; 
    }
}

void UpdateSubjectOffer(pqxx::transaction_base& txn, int offer_id, int people_group_id, int program_id, int course_id) {
    try {
        
        std::string sql =  "UPDATE subject_offer SET people_group_id = $1, program_id = $2, course_id = $3 WHERE offer_id = $4";
        txn.exec_params(sql, people_group_id, program_id, course_id, offer_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", offer_id, e.what()) ;
        throw ; 
    }
}

void Delete_Subject_Offer(pqxx::transaction_base& txn, int offer_id) {
    try {
        
        std::string sql =  "DELETE FROM subject_offer WHERE offer_id = $1";
        txn.exec_params(sql, offer_id);
        //txn.commit();
    } catch (const std::exception &e) {
        txn.abort();
        fmt::print("Ошибка при удалении {}: {}", offer_id, e.what()) ;
        throw ; 
    }
}

bool IsThereARecordOffer(pqxx::transaction_base& txn, int people_group_id, int program_id, int course_id) {
    try {
        std::string sql =  " SELECt EXISTS("
                           "SELECT 1 FROM subject_offer WHERE people_group_id = $1 AND program_id = $2 AND course_id = $3"
                           ")";
        pqxx::result res = txn.exec_params(sql, people_group_id, program_id, course_id);
        return res[0][0].as<bool>();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", people_group_id, e.what()) ;
        throw ;
    }
}


int GetOfferId(pqxx::transaction_base& txn, int people_group_id, int program_id, int course_id) {
    try {
        std::string sql =  " SELECt offer_id FROM subject_offer WHERE people_group_id = $1 AND program_id = $2 AND course_id = $3";
        pqxx::result res = txn.exec_params(sql, people_group_id, program_id, course_id);
        return res[0]["offer_id"].as<int>();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", people_group_id, e.what()) ;
        throw ;
    }
}