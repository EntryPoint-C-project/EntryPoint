#include "inc/People.hpp"

static void Create(pqxx::connection &conn,  const std::string first_name , const std::string last_name , const std::string tg_nick) {
    try {
        pqxx::work txn(conn);
        std::string sql_for_insert_people = "INSERT INTO People (first_name, last_name, tg_nick) VALUES ($1, $2, $3) ;";
        txn.exec_params(sql_for_insert_people , first_name , last_name , tg_nick); 

        txn.commit(); 
        std::cout << "Был успешно добавлен человек под ником " << tg_nick << std::endl; 
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка с добавлением " << tg_nick << " Название ошибки: " << e.what() << std::endl;
    }
}


static std::string  ReadAllInformation(pqxx::connection &conn, const int person_id) {// first_name , last_name , tg_nick 
    try {
        pqxx::work txn(conn);
        std::string sql_for_select_people = "SELECT first_name, last_name, tg_nick FROM People WHERE person_id = $1 ;";
        pqxx::result res = txn.exec_params(sql_for_select_people , person_id);
        std::string first_name = res[0][0].c_str();
        std::string last_name = res[0][1].c_str();
        std::string tg_nick = res[0][2].c_str();

        std::string result =  first_name + last_name +  tg_nick;
        txn.commit();
        std::cout << "Был успешно прочитан человек под ником " << tg_nick << std::endl;
        return result;
    }catch (const std::exception &e) {
        std::cout  << "Произошла ошибка при чтении из таблицы People: " << e.what() << std::endl;
    }
}

static int ReadPersonId(pqxx::connection &conn , std::string tg_nick ) {
    try {
        pqxx::work txn(conn);
        std::string sql_for_select_people = "SELECT person_id FROM People WHERE tg_nick = $1 ;";
        pqxx::result res = txn.exec_params(sql_for_select_people , tg_nick);
        int person_id = res[0][0].as<int>();

        txn.commit();
        std::cout << "Был успешно прочитан человек под айди " << person_id << " под ником " << tg_nick  << std::endl;
        return person_id;
    }catch (const std::exception &e) {
        std::cout  << "Произошла ошибка при чтении из таблицы People: " << e.what() << std::endl;
    }
}






static void Update(pqxx::connection &conn, std::string old_tg_nick  , std::string new_tg_nick ) {
    try {
        pqxx::work txn(conn);
        std::string sql_for_update_people = "UPDATE People SET tg_nick = $1 WHERE tg_nick = $2 ;";
        txn.exec_params(sql_for_update_people , new_tg_nick , old_tg_nick);
        txn.commit();
        std::cout << "Был успешно обновлен человек под ником " << old_tg_nick << std::endl;
    }catch(const std::exception &e) {
        std::cout  << "Произошла ошибка при обновлении в таблице People: " << e.what() << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int person_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql_for_delete_people = "DELETE FROM People WHERE person_id = $1 ; ";
        txn.exec_params(sql_for_delete_people , person_id);
        txn.commit();
        std::cout << "Был успешно удален человек под ником " << person_id << std::endl;
    }catch(const std::exception &e) {
        std::cout  << "Произошла ошибка при удалении в таблице People: " << e.what() << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int tg_nick ) {
    try {
        pqxx::work txn(conn);
        std::string sql_for_delete_people = "DELETE FROM People WHERE tg_nick = $1; ";
        txn.exec_params(sql_for_delete_people , tg_nick);
        txn.commit();
        std::cout << "Был успешно удален человек под ником " << tg_nick << std::endl;
    }catch(const std::exception &e) {
        std::cout  << "Произошла ошибка при удалении в таблице People: " << e.what() << std::endl;
    }
}
