#include "../include/CategoryTags.hpp"

void CategoryTags::loadFromRow(const pqxx::row &row) {
    category_id = row["category_id"].as<int>();
    tag_id = row["tag_id"].as<int>();
}

static void Create(pqxx::connection &conn, int category_id, int tag_id) {
    CategoryTags category_tag;
    category_tag.category_id = category_id;
    category_tag.tag_id = tag_id;
    BaseCrud<CategoryTags>::Create(conn, category_tag);
}

static void UpdateLinkingPlates(pqxx::connection &conn, std::pair <int , int> old_params_for_category, std::pair <int, int>  new_params_for_category) {
    BaseCrud<CategoryTags>::UpdateLinkingPlates(conn, old_params_for_category, new_params_for_category);
}

static void DeleteFromLinkingPlates(pqxx::connection &conn, std::pair <int , int> ids) {
    BaseCrud<CategoryTags>::DeleteFromLinkingPlates(conn, ids);
}