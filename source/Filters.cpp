#include "../include/Filters.hpp"

void Filters::loadFromRow(const pqxx::row &row) {
    filter_id = row["filter_id"].as<int>();
    filter_name = row["filter_name"].as<std::string>();
}

static void Create(pqxx::connection &conn, const std::string &filter_name) {
    Filters filter;
    filter.filter_name = filter_name;
    BaseCrud<Filters>::Create(conn, filter);
}

static Filters Read(pqxx::connection &conn , int filter_id) {
    return BaseCrud<Filters>::Read(conn , filter_id);
}

static void Update(pqxx::connection &conn, int filter_id, std::vector<std::string> new_params_for_filter) {
    Filters filter;
    filter.filter_id = filter_id;
    filter.filter_name = new_params_for_filter[0];
    BaseCrud<Filters>::Update(conn, filter_id, filter);
}

static void Delete(pqxx::connection &conn, int filter_id) {
    BaseCrud<Filters>::Delete(conn, filter_id);
}