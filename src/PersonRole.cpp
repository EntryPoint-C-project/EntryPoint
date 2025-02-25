#include "inc/PersonRole.hpp"



static void Create(pqxx::connection &conn, const int person_id, const int role_id) {
    try{
        pqxx::work txn(conn) ; 
        std::string sql_insert_information_in_person_role= "INSERT INTO Person_Role (person_id , role_id) VALUES ($1 , $2)"; 

        txn.exec_params(sql_insert_information_in_person_role ,person_id , role_id ); 
        txn.commit(); 
        std::cout<< std::string("Пользователь с ID: " ) + std::to_string(person_id) + std::string(" и ID роли: ") + std::to_string(role_id) + std::string( " был успешно добавлен в таблицу Person_Role"); 
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при добавлении к " << person_id << " с ролью : " << role_id << e.what() << std::endl;
    }
}

static std::vector<int> ReadRolesByPersonId(pqxx::connection &conn, const int person_id) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "SELECT role_id FROM Person_Role WHERE person_id = $1";
        pqxx::result res = txn.exec_params(sql , person_id); 
        
        std::vector <int> vec_role_id; 
        for (auto row : res) {
            vec_role_id.push_back(row[0].as<int>());
        }
        txn.commit(); 
        std::cout << "Данные о ролях пользователя с ID: " << person_id << " были успешно добавлены в вектор vec_role_id\n";
        return vec_role_id;
    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе role_id для " <<  person_id << std::endl; 
        return {}; 
    }
}

static std::vector<int> ReadPersonsByRoleId(pqxx::connection &conn, const int role_id) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "SELECT person_id FROM Person_Role WHERE role_id = $1";
        pqxx::result res = txn.exec_params(sql , role_id); 
        
        std::vector <int> vec_person_id; 
        for (auto row : res) {
            vec_person_id.push_back(row[0].as<int>());
        }
        txn.commit(); 
        std::cout << "Данные о пользователях с ID: " << role_id << " были успешно добавлены в вектор vec_person_id\n";
        return vec_person_id;
    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при выводе person_id для " <<  role_id << std::endl;
        return {}; 
    }
}

static bool ReadInformationAboutPersonId(pqxx::connection &conn , const int person_id) {
    try {
        pqxx::work txn(conn); 
        std::string sql = "SELECT EXISTS ( SELECT 1 FROM Person_Role WHERE person_id = $1);";
        pqxx::result res = txn.exec_params(sql , person_id); 
        
        txn.commit(); 
        bool contains = res[0][0].as<bool>();
        if (contains){
            std::cout << "Пользователь  с ID: " << person_id << " был найдене внутри Person_Role\n";
        }else {
            std::cout << "Пользователь  с ID: " << person_id << " Не найден  внутри Person_Role\n";
        }
        return contains;
    }catch (const std::exception &e){
        std::cout << "Произошла ошибка при чтении  " <<  person_id  << " : "<< std::endl;
        return false; 
    }
}



static void Update(pqxx::connection &conn, const int old_person_id, const int old_role_id,  const int new_person_id, const int new_role_id) {
    try {
        Remove(conn, old_person_id, old_role_id);
        Create(conn , new_person_id , new_role_id);
        std::cout << "Изменения : " << old_person_id << " --> " << new_person_id << " , " << old_role_id << " --> " << new_role_id << std::endl;
    }catch (const std::exception &e){
        std::cout << "Произшошла ошибка при изменении " << old_person_id << " --> " << new_person_id << " , " << old_role_id << " --> " << new_role_id << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int person_id, const int role_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Person_Role WHERE person_id = $1 AND role_id = $2; ";

        txn.exec_params(sql, person_id , role_id);
        txn.commit();
        std::cout << "Программа с ID: " << person_id << " и ID роли: " << role_id << " была успешно удалена из таблицы Person_Role" << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении к " << person_id << " с ролью : " << role_id << e.what() << std::endl;
    }

}
