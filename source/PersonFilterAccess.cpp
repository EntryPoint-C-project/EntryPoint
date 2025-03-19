#include "../include/PersonFilterAccess.hpp"

void PersonFilterAccess::loadFromRow(const pqxx::row &row) {
    person_id = row["person_id"].as<int>();
    filter_id = row["filter_id"].as<int>();
}

static void Create(pqxx::connection &conn, int person_id, int filter_id) {
    PersonFilterAccess person_filter_access;
    person_filter_access.person_id = person_id;
    person_filter_access.filter_id = filter_id;
    BaseCrud<PersonFilterAccess>::Create(conn, person_filter_access);
}

static void UpdateLinkingPlates(pqxx::connection &conn, std::pair<int ,int > ids, std::pair<int , int> new_params_for_person_filter_access) {
    BaseCrud<PersonFilterAccess>::UpdateLinkingPlates(conn, ids, new_params_for_person_filter_access);
}

static void DeleteFromLinkingPlates(pqxx::connection &conn, std::pair<int , int> ids) {
    BaseCrud<PersonFilterAccess>::DeleteFromLinkingPlates(conn, ids);
}