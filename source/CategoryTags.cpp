#include "../inc/CategoryTags.hpp"

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

static std::vector<CategoryTags> ReadTag(pqxx::connection &conn, int category_id) {
    return BaseCrud<CategoryTags>::Read(conn, category_id );
}

static std::vector<CategoryTags> ReadCategory(pqxx::connection &conn, int tag_id) {
    return BaseCrud<CategoryTags>::Read(conn, tag_id);
}

static void Update(pqxx::connection &conn, int category_id, std::vector<std::string> new_params_for_category) {
    CategoryTags updated_category_tag;
    updated_category_tag.category_id = category_id;
    updated_category_tag.tag_id = std::stoi(new_params_for_category[0]);
    BaseCrud<CategoryTags>::Update(conn, category_id, updated_category_tag);
}

static void Delete(pqxx::connection &conn, int category_id) {
    BaseCrud<CategoryTags>::Delete(conn, category_id);
}

