#include "PersonFilterAccess.hpp"

static void Create(pqxx::connection &conn, const int person_id , const int filter_id ){
    try{
        pqxx::work txn(conn) ;
        std::string sql = "INSERT INTO Person_Filter_Access (person_id, filter_id) VALUES ($1, $2);";
        txn.exec_params(sql, person_id, filter_id);
        txn.commit();
        std::cout << "Person_Filter_Access от person_id " << person_id << " и filter_id " << filter_id << " был успешно создан\n";
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при создании записи в таблице Person_Filter_Access: " << e.what() << std::endl;
    }
}

static std::vector <int>  ReadFilterId(pqxx::connection &conn, const int person_id){
    try {
        pqxx::work txn(conn); 
        std::string sql = "SELECT filter_id FROM Person_Filter_Access WHERE person_id = $1";
        pqxx::result res = txn.exec_params(sql , person_id); 
        
        std::vector <int> vec_filter_id; 
        for (auto row : res) {
            vec_filter_id.push_back(row[0].as<int>());
        }
        txn.commit(); 
        std::cout << "Данные о фильтрах пользователя с ID: " << person_id << " были успешно добавлены в вектор vec_filter_id\n";
        return vec_filter_id;
    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе filter_id для " <<  person_id << std::endl; 
        return {};
    }
}

static std::vector <int>  ReadPersonId(pqxx::connection &conn, const int filter_id){
    try {
        pqxx::work txn(conn); 
        std::string sql = "SELECT person_id FROM Person_Filter_Access WHERE filter_id = $1";
        pqxx::result res = txn.exec_params(sql , filter_id); 
        
        std::vector <int> vec_person_id; 
        for (auto row : res) {
            vec_person_id.push_back(row[0].as<int>());
        }
        txn.commit(); 
        std::cout << "Данные о пользователях с ID: " << filter_id << " были успешно добавлены в вектор vec_person_id\n";
        return vec_person_id;
    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе person_id для " <<  filter_id << std::endl; 
        return {};
    }
}

static void Update(pqxx::connection &conn, const int old_person_id , const int old_filter_id , const int new_person_id , const int new_filter_id ){
    try {
        Remove(conn, old_person_id, old_filter_id);
        Create(conn , new_person_id , new_filter_id);
        std::cout << "Изменения : " << old_person_id << " --> " << new_person_id << " , " << old_filter_id << " --> " << new_filter_id << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при обновлении Person_Filter_Access: " << e.what() << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int person_id , const int filter_id ){
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Person_Filter_Access WHERE person_id = $1 AND filter_id = $2;";
        txn.exec_params(sql, person_id, filter_id);
        txn.commit();
        std::cout << "Person_Filter_Access от person_id " << person_id << " и filter_id " << filter_id << " был успешно удален\n";
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении Person_Filter_Access: " << e.what() << std::endl; 
    }
}