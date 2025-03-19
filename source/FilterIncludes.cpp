#include "../include/FilterIncludes.hpp"


void FilterInludes::loadFromRow(const pqxx::row &row) {
    tag_id = row["tag_id"].as<int>();
    tag_id = row["tag_id"].as<int>();
}

static void Create(pqxx::connection &conn, int filter_id , int tag_id) {
    FilterInludes filter_includes;
    filter_includes.tag_id = filter_id;
    filter_includes.tag_id = tag_id;
    BaseCrud<FilterInludes>::Create(conn, filter_includes);
}


static void Update(pqxx::connection &conn, int tag_id, std::vector<std::string> new_params_for_filter_includes) {
    FilterInludes updated_filter_includes;
    updated_filter_includes.tag_id = tag_id;
    updated_filter_includes.tag_id = std::stoi(new_params_for_filter_includes[0]);
    BaseCrud<FilterInludes>::Update(conn, tag_id, updated_filter_includes);
}

static void Delete(pqxx::connection &conn, int tag_id) {
    BaseCrud<FilterInludes>::Delete(conn, tag_id);
}