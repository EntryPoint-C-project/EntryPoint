#include "Students.hpp"

static void Create(pqxx::connection &conn,  int person_id , int program_id , std::string info) {
    try {
        pqxx::work txn(conn);
        std::string sql =  "INSERT INTO Students (person_id, program_id, info) VALUES ($1, $2, $3)";
            
        txn.exec_params(sql, person_id, program_id, info);
        txn.commit();
        std::cout << "Пользователь с ID: " << person_id << " и ID программы: " << program_id << " был успешно добавлен в таблицу Students." << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при добавлении к " << person_id << " с программой: " << program_id << ". Ошибка: " << e.what() << std::endl;
    }
}

static int  ReadProgramId(pqxx::connection &conn, const int student_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT program_id FROM Students WHERE student_id = $1";
        pqxx::result res = txn.exec_params(sql, student_id);
        int program_id = res[0][0].as<int>();
        txn.commit();
        std::cout << "program_id " << program_id<< " был успешно прочитан\n";
        return program_id; 
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении из таблицы Students: " << e.what() << std::endl;
    }
}

static int  ReadPersonId(pqxx::connection &conn, const int student_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT person_id FROM Students WHERE student_id = $1";
        pqxx::result res = txn.exec_params(sql, student_id);
        int person_id = res[0][0].as<int>();
        txn.commit();
        std::cout << "person_id " << person_id<< " был успешно прочитан\n";
        return person_id; 
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении из таблицы Students: " << e.what() << std::endl;
    }
}

static std::string ReadInfo(pqxx::connection &conn, const int student_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT info FROM Students WHERE student_id = $1";
        pqxx::result res = txn.exec_params(sql, student_id);
        std::string info = res[0][0].as<std::string>();
        txn.commit();
        std::cout << "info " << info << " \n";
        return info; 
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении из таблицы Students: " << e.what() << std::endl;
    }
}

static void UpdateProgramId(pqxx::connection &conn, int student_id  , int old_program_id , int new_program_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "UPDATE Students SET program_id = $1 WHERE student_id = $2 AND program_id = $3;";
        auto result = txn.exec_params(sql, new_program_id, student_id, old_program_id);
        
        if(result.affected_rows() > 0) {
            txn.commit();
            std::cout << "Program ID изменен с " << old_program_id  << " на " << new_program_id << " для student_id="  << student_id << std::endl;
        } else {
            std::cerr << "Не удалось обновить: не совпадает old_program_id " << "или student_id не найден" << std::endl;
        }
    } 
    catch (const std::exception &e) {
        std::cout << "Ошибка при изменении Program ID: " << e.what() << std::endl;
    }
}

static void UpdateInfo(pqxx::connection &conn, int student_id  , std::string old_info , std::string new_info) {
    try {
        pqxx::work txn(conn);
        std::string sql = "UPDATE Students SET info = $1 WHERE student_id = $2 AND info = $3;";
        auto result = txn.exec_params(sql, new_info, student_id, old_info);
        
        if(result.affected_rows() > 0) {
            txn.commit();
            std::cout << "info изменен с " << old_info  << " на " << new_info << " для student_id="  << student_id << std::endl;
        } else {
            std::cerr << "Не удалось обновить: не совпадает old_info " << "или student_id не найден" << std::endl;
        }
    } 
    catch (const std::exception &e) {
        std::cout << "Ошибка при изменении info: " << e.what() << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int student_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Students WHERE student_id = $1";
        txn.exec_params(sql, student_id);
        txn.commit();
        std::cout << "Пользователь с ID: " << student_id << " был успешно удален из таблицы Students." << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении пользователя с ID: " << student_id << ". Ошибка: " << e.what() << std::endl;
    }
}
