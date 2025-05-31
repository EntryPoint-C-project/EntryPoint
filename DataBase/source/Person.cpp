#include <Person.hpp>



int  CreatePerson(pqxx::transaction_base& txn , const std::string first_name , const std::string last_name, const std::string tg_nick , int access)  {
    if ( first_name.empty() || last_name.empty() || tg_nick.empty() ) {
        fmt::print("Заполните все поля\n");
        throw std::invalid_argument("Заполните все поля");
    }


    try { 
        // todo : checker : 
        // todo: check(first_name, last_name, tg_nick)  --> std::tuple{role , his_params} , his_params = {course , group , program }

        std::string sql =  "INSERT INTO people (first_name, last_name, tg_nick, access) VALUES ($1, $2, $3, $4) ON CONFLICT (tg_nick) DO NOTHING RETURNING person_id";

        pqxx::result res = txn.exec_params(sql, first_name, last_name, tg_nick, access);
        int person_id  ;

        if (!res.empty() && !res[0]["person_id"].is_null()) {
            person_id = res[0]["person_id"].as<int>();
            // ...
        } else {
            fmt::print("Запись уже существует с указанным tg_nick\n");
            // throw std::invalid_argument("Запись уже существует с указанным tg_nick");
        }
        //txn.commit();
        return person_id; 
    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", first_name, e.what()) ;
        throw ; 
    }
}


std::tuple<std::string, std::string, std::string, int> ReadPerson(pqxx::transaction_base& txn, int person_id) {
    try {

        std::string sql = "SELECT first_name, last_name, tg_nick, access FROM people WHERE person_id = $1";
        pqxx::result res = txn.exec_params(sql, person_id);

        if (res.empty()) {
            throw std::runtime_error("Person not found with ID: " + std::to_string(person_id));
        }

        auto row = res[0];
        std::string first_name = row["first_name"].is_null() ? "" : row["first_name"].as<std::string>();
        std::string last_name  = row["last_name"].is_null()  ? "" : row["last_name"].as<std::string>();
        std::string tg_nick    = row["tg_nick"].is_null()    ? "" : row["tg_nick"].as<std::string>();
        int access = row["access"].as<int>();

        return {first_name, last_name, tg_nick, access};
    }catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", person_id, e.what()) ;
        throw ;
    }
}

void DeletePerson(pqxx::transaction_base& txn, int person_id) {
    try {

        std::string sql =  "DELETE FROM people WHERE person_id = $1";
        txn.exec_params(sql, person_id);
        //txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при удалении {}: {}", person_id, e.what()) ;
        throw ; 
    }
}