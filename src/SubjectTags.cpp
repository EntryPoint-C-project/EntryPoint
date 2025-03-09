#include "SubjectTags.hpp"

static void Create(pqxx::connection &conn, const int subject_id , const int   tag_id ){
    try {
        pqxx::work txn(conn);
        std::string sql = "INSERT INTO Subject_Tags(subject_id, tag_id) VALUES ($1, $2);";
        auto result = txn.exec_params(sql, subject_id, tag_id);
        txn.commit();
        std::cout << "Subject_Tags от subject_id " << subject_id << " и tag_id " << tag_id << " был успешно создан\n";
    } catch (const std::exception &e) {
        std::cout << "Ошибка при добавлении: " << e.what() << std::endl;

    }
}

static std::vector <int>  ReadTagId(pqxx::connection &conn, const int subject_id){
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT tag_id FROM Subject_Tags WHERE subject_id = $1;";
        pqxx::result result = txn.exec_params(sql, subject_id);
        std::vector<int> tag_ids;
        for (const auto &row : result) {
            tag_ids.push_back(row[0].as<int>());
        }
        txn.commit();
        std::cout << "Данные о тегах предмета с ID: " << subject_id << " были успешно добавлены в вектор tag_ids\n";
        return tag_ids;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении tag_id: " << e.what() << std::endl;
        return {};
    }
}

static std::vector <int>  ReadSubjectId(pqxx::connection &conn, const int tag_id){
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT subject_id FROM Subject_Tags WHERE tag_id = $1;";
        pqxx::result result = txn.exec_params(sql, tag_id);
        std::vector<int> subject_ids;
        for (const auto &row : result) {
            subject_ids.push_back(row[0].as<int>());
        }
        txn.commit();
        std::cout << "Данные о предметах тега с ID: " << tag_id << " были успешно добавлены в вектор subject_ids\n";
        return subject_ids;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении subject_id: " << e.what() << std::endl;
        return {};
    }
}

static void Update(pqxx::connection &conn, const int old_subject_id , const int old_tag_id , const int new_subject_id , const int new_tag_id ){
    try {
        Remove(conn, old_subject_id, old_tag_id);
        Create(conn , new_subject_id , new_tag_id);
        std::cout << "Изменения : " << old_subject_id << " --> " << new_subject_id << " , " << old_tag_id << " --> " << new_tag_id << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Ошибка при изменении: " << e.what() << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int subject_id , const int tag_id ){
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Subject_Tags WHERE subject_id = $1 AND tag_id = $2;";
        txn.exec_params(sql, subject_id, tag_id);
        txn.commit();
        std::cout << "Subject_Tags от subject_id " << subject_id << " и tag_id " << tag_id << " был успешно удален\n";
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении Subject_Tags: " << e.what() << std::endl; 
    }
}