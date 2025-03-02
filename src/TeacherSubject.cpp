#include "TeacherSubject.hpp"

static void Create(pqxx::connection &conn, const int teacher_id , const int   subject_id ){
    try{
        pqxx::work txn(conn);
        std::string sql = "INSERT INTO Teacher_Subject (teacher_id, subject_id) VALUES ($1, $2);";
        txn.exec_params(sql, teacher_id, subject_id);
        txn.commit();
        std::cout << "Teacher_Subject от teacher_id " << teacher_id << " и subject_id " << subject_id << " был успешно создан\n";
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при создании записи в таблице Teacher_Subject: " << e.what() << std::endl;
    }
}

static std::vector <int>  ReadSubjectId(pqxx::connection &conn, const int teacher_id){
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT subject_id FROM Teacher_Subject WHERE teacher_id = $1;";
        pqxx::result result = txn.exec_params(sql, teacher_id);
        std::vector<int> subject_ids;
        for (const auto &row : result) {
            subject_ids.push_back(row[0].as<int>());
        }
        txn.commit();
        std::cout << "Данные о предметах учителя с ID: " << teacher_id << " были успешно добавлены в вектор subject_ids\n";
        return subject_ids;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении subject_id: " << e.what() << std::endl;
        return {};
    }
}

static std::vector <int>  ReadTeacherId(pqxx::connection &conn, const int subject_id){
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT teacher_id FROM Teacher_Subject WHERE subject_id = $1;";
        pqxx::result result = txn.exec_params(sql, subject_id);
        std::vector<int> teacher_ids;
        for (const auto &row : result) {
            teacher_ids.push_back(row[0].as<int>());
        }
        txn.commit();
        std::cout << "Данные о учителях предмета с ID: " << subject_id << " были успешно добавлены в вектор teacher_ids\n";
        return teacher_ids;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении teacher_id: " << e.what() << std::endl;
        return {};
    }
}

static void Update(pqxx::connection &conn, const int old_teacher_id , const int old_subject_id , const int new_teacher_id , const int new_subject_id ){
    try{
        Remove(conn, old_teacher_id, old_subject_id);
        Create(conn , new_teacher_id , new_subject_id);
        std::cout << "Изменения : " << old_teacher_id << " --> " << new_teacher_id << " , " << old_subject_id << " --> " << new_subject_id << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при обновлении Teacher_Subject: " << e.what() << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int teacher_id , const int subject_id ){
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Teacher_Subject WHERE teacher_id = $1 AND subject_id = $2;";
        txn.exec_params(sql, teacher_id, subject_id);
        txn.commit();
        std::cout << "Teacher_Subject от teacher_id " << teacher_id << " и subject_id " << subject_id << " был успешно удален\n";
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении Teacher_Subject: " << e.what() << std::endl; 
    }
}