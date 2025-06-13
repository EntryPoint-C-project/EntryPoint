#include "SOP_Form.hpp"

int CreateSOPForm(pqxx::transaction_base& txn , int person_id, const std::string url, std::string tg_answer, std::string url_answer) {

    try {
        // Проверяем, есть ли уже запись для данного человека в таблице Sop_Form
        std::string sql = "SELECT sop_id FROM Sop_Form WHERE person_id = $1";
        pqxx::result res = txn.exec_params(sql, person_id);
        if (!res.empty()) {
            // Если запись уже существует, то просто вернём 0
            return 0;
        }

        // Если записи нет, то добавляем новую запись
        sql = "INSERT INTO SOP_Form (person_id, url_out_sop, sop_status ,  tg_answer, url_answer) VALUES ($1, $2, $3, $4, $5)  RETURNING sop_id";
        res = txn.exec_params(sql, person_id, url, "NOT_STARTED", tg_answer, url_answer);
        int sop_id ; 
        if ( !res.empty() ) {
            sop_id = res[0]["sop_id"].as<int>();
        }else { 
            fmt::print("Ошибка при создании записи\n");
        }
        return sop_id;

    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", url, e.what()) ;
        throw ; 
    }
}

 std::tuple < int , std::string , std::string , std::string , std::string > ReadSOPForm(pqxx::transaction_base& txn , int sop_id) {
    try {

        std::string sql =  "SELECT person_id, url_out_sop, sop_status ,  tg_answer, url_answer FROM SOP_Form WHERE sop_id = $1";
        pqxx::result res = txn.exec_params(sql, sop_id);
        //txn.commit();
        if ( !res.empty() ) {
            int person_id = res[0]["person_id"].as<int>();
            std::string url = res[0]["url_out_sop"].as<std::string>();
            std::string status = res[0]["sop_status"].as<std::string>();
            std::string tg_answer = res[0]["tg_answer"].as<std::string>();
            std::string url_answer = res[0]["url_answer"].as<std::string>();
            return std::make_tuple(person_id, url, status, tg_answer, url_answer);
        }
        return std::make_tuple(0, "", "", "", "");
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", sop_id, e.what()) ;
        throw ; 
    }
}

void UpdatePersonId(pqxx::transaction_base& txn, int sop_id, int new_person_id) {
    try {

        std::string sql =  "UPDATE SOP_Form SET person_id = $1 WHERE sop_id = $2";
        txn.exec_params(sql, new_person_id, sop_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", sop_id, e.what()) ;
        throw ; 
    }
}

void UpdateUrl(pqxx::transaction_base& txn, int sop_id, std::string new_url) {
    try {

        std::string sql =  "UPDATE SOP_Form SET url_out_sop = $1 WHERE sop_id = $2";
        txn.exec_params(sql, new_url, sop_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", sop_id, e.what()) ;
        throw ; 
    }
}

std::vector <int> ReadSubjectId(pqxx::transaction_base& txn ) {
    try {
        std::string sql =  "SELECT person_id FROM SOP_Form";
        pqxx::result res = txn.exec(sql);
        std::vector <int> subject_id;
        for ( auto row : res ) {
            subject_id.push_back(row["person_id"].as<int>());
        }
        return subject_id;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", "subject_id", e.what()) ;
        throw ;
    }
}

void UpdateStatus(pqxx::transaction_base& txn, int sop_id, std::string new_status) {
    try {
        if ( new_status != "NOT_STARTED" && new_status != "STARTED" && new_status != "PASSED" ) {
            fmt::print("Неверный статус\n");
            throw std::invalid_argument("Неверный статус");
        }
   
        std::string sql =  "UPDATE SOP_Form SET sop_status = $1 WHERE sop_id = $2";
        txn.exec_params(sql, new_status, sop_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", sop_id, e.what()) ;
        throw ; 
    }
}



void DeleteSOP_Form(pqxx::transaction_base& txn, int sop_id) {
    try {

        std::string sql =  "DELETE FROM SOP_Form WHERE sop_id = $1";
        txn.exec_params(sql, sop_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при удалении {}: {}", sop_id, e.what()) ;
        throw ; 
    }
}

void UpdateTgAnswer(pqxx::transaction_base& txn, int sop_id, std::string new_tg_answer) { // обновленные методы , для того , чтобы у нас была конкатенация ответов , а не просто замена одного на другое 
    try {
        std::string sql =  "UPDATE SOP_Form SET tg_answer = tg_answer || '\t' || $1 WHERE sop_id = $2";
        txn.exec_params(sql, new_tg_answer, sop_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", sop_id, e.what()) ;
        throw ; 
    }
}

void UpdateUrlAnswer(pqxx::transaction_base& txn, int sop_id, std::string new_url_answer) { // обновленные методы , для того , чтобы у нас была конкатенация ответов , а не просто замена одного на другое 
    try {
        std::string sql =  "UPDATE SOP_Form SET url_answer = url_answer || '\t' || $1 WHERE sop_id = $2";
        txn.exec_params(sql, new_url_answer, sop_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", sop_id, e.what()) ;
        throw ; 
    }
}

int ReadSopId(pqxx::transaction_base& txn , int person_id) {
    try {
        std::string sql =  "SELECT sop_id FROM SOP_Form WHERE person_id = $1";
        pqxx::result res = txn.exec_params(sql, person_id);
        if ( !res.empty() ) {
            return res[0]["sop_id"].as<int>();
        }
        return 0;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", person_id, e.what()) ;
        throw ; 
    }
}

void GetUrlAnswer(pqxx::transaction_base& txn, int person_id)  {
    try {
        std::string sql =  "SELECT url_answer FROM SOP_Form WHERE person_id = $1";
        pqxx::result res = txn.exec_params(sql, person_id);
        if ( !res.empty() ) {
            std::cout << res[0]["url_answer"].as<std::string>() << std::endl;
        }
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", person_id, e.what()) ;
        throw ; 
    }
}