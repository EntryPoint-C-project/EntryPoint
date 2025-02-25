#include "Feedback_Participants.hpp"

static void Create(pqxx::connection &conn,  int student_id , int feedback_id , std::string student_feedback) {
    try {
        pqxx::work txn(conn);
        std::string sql = "INSERT INTO Feedback_Participants (student_id, feedback_id, student_feedback) VALUES ($1, $2, $3)";
        txn.exec_params(sql, student_id, feedback_id, student_feedback);
        txn.commit();
        std::cout << "Студент с ID: " << student_id << " и идентификатором: " << feedback_id << " был успешно добавлен в таблицу Feedback_Participants." << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при добавлении студента с ID: " << student_id << ". Ошибка: " << e.what() << std::endl;
    }
}

static std::string  ReadFeedback(pqxx::connection &conn, const int student_id ,const int feedback_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT student_feedback FROM Feedback_Participants WHERE student_id = $1 AND feedback_id = $2";
        pqxx::result res = txn.exec_params(sql, student_id, feedback_id);
        std::string student_feedback = res[0][0].as<std::string>();
        txn.commit();
        std::cout << "student_feedback " << student_feedback<< " был успешно прочитан\n";
        return student_feedback; 
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении из таблицы Feedback_Participants: " << e.what() << std::endl;
    }
}

static void Update(pqxx::connection &conn, std::string old_feedback  , std::string new_feedback ,const  int student_id ,const  int feedback_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "UPDATE Feedback_Participants SET student_feedback = $1 WHERE student_id = $2 AND feedback_id = $3;";
        auto result = txn.exec_params(sql, new_feedback, student_id, feedback_id);
        
        if(result.affected_rows() > 0) {
            txn.commit();
            std::cout << "Feedback изменен с " << old_feedback  << " на " << new_feedback << " для student_id="  << student_id << std::endl;
        } else {    
            std::cout << "Не удалось обновить: не совпадает old_feedback " << "или student_id не найден" << std::endl;
        }
    } 
    catch (const std::exception &e) {
        std::cout << "Ошибка при изменении Feedback: " << e.what() << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int student_id ,const int feedback_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Feedback_Participants WHERE student_id = $1 AND feedback_id = $2";
        txn.exec_params(sql, student_id, feedback_id);
        txn.commit();
        std::cout << "Пользователь с ID: " << student_id << " был успешно удален из таблицы Feedback_Participants." << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении пользователя с ID: " << student_id << ". Ошибка: " << e.what() << std::endl;
    }
}