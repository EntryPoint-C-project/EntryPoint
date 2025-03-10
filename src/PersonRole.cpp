#include "../inc/PersonRole.hpp"

void PersonRole::loadFromRow(const pqxx::row &row) {
    person_id = row["person_id"].as<int>();
    role_id = row["role_id"].as<int>();
}

static void Create(pqxx::connection &conn, int person_id, int role_id) {
    PersonRole person_role;
    person_role.person_id = person_id;
    person_role.role_id = role_id;
    BaseCrud<PersonRole>::Create(conn, person_role);
}

static std::vector<PersonRole> Read(pqxx::connection &conn) {
    return BaseCrud<PersonRole>::Read(conn);
}

static void Update(pqxx::connection &conn, int person_id, std::vector<std::string> new_params_for_person_role) {
    PersonRole updated_person_role;
    updated_person_role.person_id = person_id;
    updated_person_role.role_id = std::stoi(new_params_for_person_role[0]);
    BaseCrud<PersonRole>::Update(conn, person_id, updated_person_role);
}

static void Delete(pqxx::connection &conn, int person_id) {
    BaseCrud<PersonRole>::Delete(conn, person_id);
}