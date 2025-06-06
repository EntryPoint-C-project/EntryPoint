#include <Person.hpp>



int  CreatePerson(pqxx::transaction_base& txn , const std::string first_name , const std::string last_name, const std::string tg_nick , int access ,int snils)  {
    if ( first_name.empty() || last_name.empty() || tg_nick.empty() ||snils ==0 ) {
        fmt::print("Заполните все поля\n");
        throw std::invalid_argument("Заполните все поля");
    }


    try { 


        std::string sql =  "INSERT INTO people (first_name, last_name, tg_nick, access , snils) VALUES ($1, $2, $3, $4 , $5) ON CONFLICT (tg_nick) DO NOTHING RETURNING person_id";

        pqxx::result res = txn.exec_params(sql, first_name, last_name, tg_nick, access , snils);
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


std::tuple<std::string, std::string, std::string, int , int > ReadPerson(pqxx::transaction_base& txn, int person_id) {
    try {

        std::string sql = "SELECT first_name, last_name, tg_nick, access , snils FROM people WHERE person_id = $1";
        pqxx::result res = txn.exec_params(sql, person_id);

        if (res.empty()) {
            throw std::runtime_error("Person not found with ID: " + std::to_string(person_id));
        }

        auto row = res[0];
        std::string first_name = row["first_name"].is_null() ? "" : row["first_name"].as<std::string>();
        std::string last_name  = row["last_name"].is_null()  ? "" : row["last_name"].as<std::string>();
        std::string tg_nick    = row["tg_nick"].is_null()    ? "" : row["tg_nick"].as<std::string>();
        int access = row["access"].as<int>();
        int snils = row["snils"].as<int>();

        return {first_name, last_name, tg_nick, access , snils};
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