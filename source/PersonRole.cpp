#include "../include/PersonRole.hpp"

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


static void UpdateLinkingPlates(pqxx::connection &conn, std::pair<int ,int > ids, std::pair<int , int> new_params_for_person_role) {
    BaseCrud<PersonRole>::UpdateLinkingPlates(conn, ids, new_params_for_person_role);
}


static void DeleteFromLinkingPlates(pqxx::connection &conn, std::pair<int , int> ids) {
    BaseCrud<PersonRole>::DeleteFromLinkingPlates(conn, ids);
}