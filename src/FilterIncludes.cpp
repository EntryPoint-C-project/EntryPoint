#include "FilterIncludes.hpp"

static void Create(pqxx::connection &conn, const int filter_id , const int   tag_id ){
    try {
        pqxx::work txn(conn);
        std::string sql = "INSERT INTO Filter_Includes(filter_id, tag_id) VALUES ($1, $2);";
        txn.exec_params(sql, filter_id, tag_id);
        txn.commit();
        std::cout << "Filter_Includes от filter_id " << filter_id << " и tag_id " << tag_id << " был успешно создан\n";
    } catch (const std::exception &e) {
        std::cerr << " Произошла ошибка при добавлении в Filter_Includes: " << e.what() << "\n";
    }
}

static std::vector <int>  ReadTagId(pqxx::connection &conn, const int filter_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT tag_id FROM Filter_Includes WHERE filter_id = $1;";
        pqxx::result result = txn.exec_params(sql, filter_id);
        std::vector<int> tag_ids;
        for (const auto &row : result) {
            tag_ids.push_back(row[0].as<int>());
        }
        txn.commit();
        std::cout << "Данные о тегах фильтра с ID: " << filter_id << " были успешно добавлены в вектор tag_ids\n";
        return tag_ids;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении tag_id: " << e.what() << std::endl;
        return {};
    }
}

static std::vector <int>  ReadFiltertId(pqxx::connection &conn, const int tag_id) {
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT filter_id FROM Filter_Includes WHERE tag_id = $1;";
        pqxx::result result = txn.exec_params(sql, tag_id);
        std::vector<int> filter_ids;
        for (const auto &row : result) {
            filter_ids.push_back(row[0].as<int>());
        }
        txn.commit();
        std::cout << "Данные о фильтрах тега с ID: " << tag_id << " были успешно добавлены в вектор filter_ids\n";
        return filter_ids;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении filter_id: " << e.what() << std::endl;
        return {};
    }
}

static void Update(pqxx::connection &conn, const int old_filter_id , const int old_tag_id , const int new_filter_id , const int new_tag_id ){
    try {
        Remove(conn, old_filter_id, old_tag_id);
        Create(conn , new_filter_id , new_tag_id);
        std::cout << "Изменения : " << old_filter_id << " --> " << new_filter_id << " , " << old_tag_id << " --> " << new_tag_id << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при обновлении Filter_Includes: " << e.what() << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int filter_id , const int tag_id ) {
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Filter_Includes WHERE filter_id = $1 AND tag_id = $2;";
        txn.exec_params(sql, filter_id, tag_id);
        txn.commit();
        std::cout << "Filter_Includes от filter_id " << filter_id << " и tag_id " << tag_id << " был успешно удален\n";
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении Filter_Includes: " << e.what() << std::endl; 
    }
}