#include  "Feedback.hpp"

static void Create(pqxx::connection &conn, const int teacher_id , const int subject_id , std::string feedback_name) {
    try {
        pqxx::work txn(conn);
        std::string sql = "INSERT INTO Feedback (teacher_id, subject_id, feedback_name) VALUES ($1, $2, $3);";
        txn.exec_params(sql, teacher_id, subject_id, feedback_name);
        txn.commit();
        std::cout << "Feedback от teacher_id " << teacher_id << " и subject_id " << subject_id << " был успешно создан\n";
    } catch (const std::exception &e) {
        std::cerr << "Произошла ошибка при создании Feedback: " << e.what() << std::endl;
    }
}

static std::string  ReadFeedbackName(pqxx::connection &conn, const int feedback_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT feedback_name FROM Feedback WHERE feedback_id = $1;";
        pqxx::result res = txn.exec_params(sql, feedback_id);
        std::string feedback_name = res[0][0].as<std::string>();
        txn.commit();
        std::cout << "feedback_name " << feedback_name<< " был успешно прочитан\n";
        return feedback_name;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении из таблицы Feedback: " << e.what() << std::endl;
    }
}

static std::string  ReadTeacherAndSubjectId(pqxx::connection &conn, const int feedback_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT teacher_id, subject_id FROM Feedback WHERE feedback_id = $1;";
        pqxx::result res = txn.exec_params(sql, feedback_id);
        std::string teacher_id = res[0][0].as<std::string>();
        std::string subject_id = res[0][1].as<std::string>();
        std::string teacher_and_subject_id = teacher_id + " " + subject_id;
        txn.commit();
        std::cout << "teacher_id " << teacher_id<< " и subject_id " << subject_id << " были успешно прочитаны\n";
        return teacher_and_subject_id;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении из таблицы Feedback: " << e.what() << std::endl;
    }
}

static void UpdateFeedback(pqxx::connection &conn, const int teacher_id , const int subject_id , std::string old_feedback_name  , std::string new_feedback_name ){
    try {
        pqxx::work txn(conn);
        std::string sql = "UPDATE Feedback SET feedback_name = $1 WHERE feedback_name = $2 AND teacher_id = $3 AND subject_id = $4;";
        txn.exec_params(sql, new_feedback_name , old_feedback_name, teacher_id, subject_id);
        txn.commit();
        std::cout << "Feedback изменен с " << old_feedback_name  << " на " << new_feedback_name << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Произошла ошибка при изменении Feedback: " << e.what() << std::endl;
    }
} 

static void Remove(pqxx::connection &conn, const int feedback_id ){
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Feedback WHERE feedback_id = $1";
        txn.exec_params(sql, feedback_id);
        txn.commit();
        std::cout << "Feedback с ID: " << feedback_id << " был успешно удален из таблицы Feedback." << std::endl;
    } catch (const std::exception &e) { 
        std::cout << "Произошла ошибка при удалении Feedback с ID: " << feedback_id << ". Ошибка: " << e.what() << std::endl;
    }
}