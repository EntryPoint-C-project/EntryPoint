#include "../include/Categories.hpp"


void Categories::loadFromRow(const pqxx::row &row) {
    category_id = row["category_id"].as<int>();
    category_name = row["category_name"].as<std::string>();
    filter_id = row["filter_id"].as<int>();
    required = row["required"].as<bool>();
}

static void Create(pqxx::connection &conn, const std::string &category_name , const int filter_id , bool required) {
    Categories category;
    category.category_name = category_name;
    category.filter_id = filter_id;
    category.required = required;
    BaseCrud<Categories>::Create(conn, category);
}

static std::vector<Categories> Read(pqxx::connection &conn, int category_id) {
    return BaseCrud<Categories>::Read(conn , category_id);
}

static void Update(pqxx::connection &conn, int category_id, std::vector<std::string> new_params_for_category) {
    Categories category;
    category.category_id = category_id;
    category.category_name = new_params_for_category[0];
    category.filter_id = std::stoi(new_params_for_category[1]);
    category.required = std::stoi(new_params_for_category[2]);

    BaseCrud<Categories>::Update(conn, category_id, category);
}

static void Delete(pqxx::connection &conn, int category_id) {
    BaseCrud<Categories>::Delete(conn, category_id);
}
