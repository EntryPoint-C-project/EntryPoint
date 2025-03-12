#include "../inc/PersonFilterAccess.hpp"

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

static std::vector<PersonFilterAccess> ReadFilters(pqxx::connection &conn , int person_id) {
    return BaseCrud<PersonFilterAccess>::Read(conn, person_id);
}

static std::vector<PersonFilterAccess> ReadPerson(pqxx::connection &conn , int filter_id) {
    return BaseCrud<PersonFilterAccess>::Read(conn, filter_id);
}

static void Update(pqxx::connection &conn, int person_id, std::vector<std::string> new_params_for_person_filter_access) {
    PersonFilterAccess updated_person_filter_access;
    updated_person_filter_access.person_id = person_id;
    updated_person_filter_access.filter_id = std::stoi(new_params_for_person_filter_access[0]);
    BaseCrud<PersonFilterAccess>::Update(conn, person_id, updated_person_filter_access);
}

static void Delete(pqxx::connection &conn, int person_id) {
    BaseCrud<PersonFilterAccess>::Delete(conn, person_id);
}   