#include "CategoryTags.hpp"

static void Create(pqxx::connection &conn, const int category_id , const int   tag_id ){
    try {
        pqxx::work txn(conn);
        std::string sql = "INSERT INTO Category_Tags(category_id, tag_id) VALUES ($1, $2);";
        txn.exec_params(sql, category_id, tag_id);
        txn.commit();
        std::cout << "Category_Tags от category_id " << category_id << " и tag_id " << tag_id << " был успешно создан\n";
    } catch (const std::exception &e) {
        std::cerr << " Произошла ошибка при добавлении в Category_Tags: " << e.what() << "\n";
    }
}

static std::vector <int>  ReadTagId(pqxx::connection &conn, const int category_id){
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT tag_id FROM Category_Tags WHERE category_id = $1;";
        pqxx::result result = txn.exec_params(sql, category_id);
        std::vector<int> tag_ids;
        for (const auto &row : result) {
            tag_ids.push_back(row[0].as<int>());
        }
        txn.commit();
        std::cout << "Данные о тегах категории с ID: " << category_id << " были успешно добавлены в вектор tag_ids\n";
        return tag_ids;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении tag_id: " << e.what() << std::endl;
        return {};
    }
}

static std::vector <int>  ReadCategorytId(pqxx::connection &conn, const int tag_id){
    try {
        pqxx::work txn(conn);
        std::string sql = "SELECT category_id FROM Category_Tags WHERE tag_id = $1;";
        pqxx::result result = txn.exec_params(sql, tag_id);
        std::vector<int> category_ids;
        for (const auto &row : result) {
            category_ids.push_back(row[0].as<int>());
        }
        txn.commit();
        std::cout << "Данные о категориях тега с ID: " << tag_id << " были успешно добавлены в вектор category_ids\n";
        return category_ids;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при чтении category_id: " << e.what() << std::endl;
        return {};
    }
}

static void Update(pqxx::connection &conn, const int old_category_id , const int old_tag_id , const int new_category_id , const int new_tag_id ){
    try {
        Remove(conn, old_category_id, old_tag_id);
        Create(conn , new_category_id , new_tag_id);
        std::cout << "Изменения : " << old_category_id << " --> " << new_category_id << " , " << old_tag_id << " --> " << new_tag_id << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при обновлении Category_Tags: " << e.what() << std::endl;
    }
}

static void Remove(pqxx::connection &conn, const int category_id , const int tag_id ){
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM Category_Tags WHERE category_id = $1 AND tag_id = $2;";
        txn.exec_params(sql, category_id, tag_id);
        txn.commit();
        std::cout << "Category_Tags от category_id " << category_id << " и tag_id " << tag_id << " был успешно удален\n";
    } catch (const std::exception &e) {
        std::cout << "Произошла ошибка при удалении Category_Tags: " << e.what() << std::endl; 
    }
}