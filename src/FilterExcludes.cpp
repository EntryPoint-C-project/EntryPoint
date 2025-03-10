#include "../inc/FilterExcludes.hpp"

void FilterExcludes::loadFromRow(const pqxx::row &row) {
    filter_id = row["filter_id"].as<int>();
    exclude_id = row["exclude_id"].as<int>();
}

static void Create(pqxx::connection &conn, int filter_id, int exclude_id) {
    FilterExcludes filter_excludes;
    filter_excludes.filter_id = filter_id;
    filter_excludes.exclude_id = exclude_id;
    BaseCrud<FilterExcludes>::Create(conn, filter_excludes);
}

static std::vector<FilterExcludes> Read(pqxx::connection &conn) {
    return BaseCrud<FilterExcludes>::Read(conn);
}

static void Update(pqxx::connection &conn, int filter_id, std::vector<std::string> new_params_for_filter_excludes) {
    FilterExcludes updated_filter_excludes;
    updated_filter_excludes.filter_id = filter_id;
    updated_filter_excludes.exclude_id = std::stoi(new_params_for_filter_excludes[0]);
    BaseCrud<FilterExcludes>::Update(conn, filter_id, updated_filter_excludes);
}

static void Delete(pqxx::connection &conn, int filter_id) {
    BaseCrud<FilterExcludes>::Delete(conn, filter_id);
}
