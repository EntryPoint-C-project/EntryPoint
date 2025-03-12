#include "../inc/FilterExcludes.hpp"

void FilterExcludes::loadFromRow(const pqxx::row &row) {
    filter_id = row["filter_id"].as<int>();
    tag_id = row["tag_id"].as<int>();
}

static void Create(pqxx::connection &conn, int filter_id, int tag_id) {
    FilterExcludes filter_excludes;
    filter_excludes.filter_id = filter_id;
    filter_excludes.tag_id = tag_id;
    BaseCrud<FilterExcludes>::Create(conn, filter_excludes);
}

static std::vector<FilterExcludes> ReadTag(pqxx::connection &conn, int filter_id) {
    return BaseCrud<FilterExcludes>::Read(conn , filter_id);
}

static std::vector<FilterExcludes> ReadFilter(pqxx::connection &conn, int filter_id ) {
    return BaseCrud<FilterExcludes>::Read(conn , filter_id);
}

static void Update(pqxx::connection &conn, int filter_id, std::vector<std::string> new_params_for_filter_excludes) {
    FilterExcludes updated_filter_excludes;
    updated_filter_excludes.filter_id = filter_id;
    updated_filter_excludes.tag_id = std::stoi(new_params_for_filter_excludes[0]);
    BaseCrud<FilterExcludes>::Update(conn, filter_id, updated_filter_excludes);
}

static void Delete(pqxx::connection &conn, int filter_id) {
    BaseCrud<FilterExcludes>::Delete(conn, filter_id);
}
