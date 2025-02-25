#include "PeopleSubject.hpp"

static void Create(pqxx::connection &conn, const int person_id , const int   subject_id ) {
    try{
        pqxx::work txn(conn);
        std::string sql = "INSERT INTO People_Subject (person_id, subject_id) VALUES ($1, $2);";
        txn.exec_params(sql, person_id, subject_id);
        txn.commit();
        std::cout << "People_Subject от person_id " << person_id << " и subject_id " << subject_id << " был успешно создан\n";
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при создании записи в таблице People_Subject: " << e.what() << std::endl;
    }
}

static std::vector <int>  ReadSubjectId(pqxx::connection &conn, const int person_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT subject_id FROM People_Subject WHERE person_id = $1;";
        pqxx::result result = txn.exec_params(sql, person_id);
        std::vector<int> subject_ids;
        for (const auto &row : result) {
            subject_ids.push_back(row[0].as<int>());
        }
        txn.commit();
        std::cout << "Данные о предметах пользователя с ID: " << person_id << " были успешно добавлены в вектор subject_ids\n";
        return subject_ids;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении subject_id: " << e.what() << std::endl;
        return {};
    }
}

static std::vector <int>  ReadPersonId(pqxx::connection &conn, const int subject_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT person_id FROM People_Subject WHERE subject_id = $1;";
        pqxx::result result = txn.exec_params(sql, subject_id);
        std::vector<int> person_ids;
        for (const auto &row : result) {
            person_ids.push_back(row[0].as<int>());
        }
        txn.commit();
        std::cout << "Данные о пользователях предмета с ID: " << subject_id << " были успешно добавлены в вектор person_ids\n";
        return person_ids;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении person_id: " << e.what() << std::endl;
        return {};
    }
}

static void Update(pqxx::connection &conn, const int old_person_id , const int old_subject_id , const int new_person_id , const int new_subject_id ) {
    try {
        Remove(conn, old_person_id, old_subject_id);
        Create(conn , new_person_id , new_subject_id);
        std::cout << "Изменения : " << old_person_id << " --> " << new_person_id << " , " << old_subject_id << " --> " << new_subject_id << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при обновлении People_Subject: " << e.what() << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int person_id , const int subject_id ){
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM People_Subject WHERE person_id = $1 AND subject_id = $2;";
        txn.exec_params(sql, person_id, subject_id);
        txn.commit();
        std::cout << "People_Subject от person_id " << person_id << " и subject_id " << subject_id << " был успешно удален\n";
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении People_Subject: " << e.what() << std::endl; 
    }
}
