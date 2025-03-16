#include "../include/Tags.hpp"

void Tags::loadFromRow(const pqxx::row &row) {
    tag_id = row["tag_id"].as<int>();
    tag_name = row["tag_name"].as<std::string>();
}

static void Create(pqxx::connection &conn, const std::string &tag_name) {
    Tags tag;
    tag.tag_name = tag_name;
    BaseCrud<Tags>::Create(conn, tag);
}

static std::vector<Tags> Read(pqxx::connection &conn , int tag_id) {
    return BaseCrud<Tags>::Read(conn , tag_id);
}

static void Update(pqxx::connection &conn, int tag_id, std::vector<std::string> new_params_for_tag) {
    Tags tag;
    tag.tag_id = tag_id;
    tag.tag_name = new_params_for_tag[0];
    BaseCrud<Tags>::Update(conn, tag_id, tag);
}

static void Delete(pqxx::connection &conn, int tag_id) {
    BaseCrud<Tags>::Delete(conn, tag_id);
}