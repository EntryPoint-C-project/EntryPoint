#include "../inc/Roles.hpp"


void Roles::loadFromRow(const pqxx::row &row) {
    role_id = row["role_id"].as<int>();
    role_name = row["role_name"].as<std::string>();
}






void Roles::Create(pqxx::connection &conn , const std::string &role_name) {
    Roles role; 
    role.role_name = role_name;
    BaseCrud<Roles>::Create(conn, role);
}

std::vector<Roles> Roles::Read(pqxx::connection &conn) {
    return BaseCrud<Roles>::Read(conn);
}

void Roles::Update(pqxx::connection &conn, int role_id, std::vector<std::string> new_params_for_role) {
    Roles update_role;
    update_role.role_name = new_params_for_role[0]; 
    BaseCrud<Roles>::Update(conn, role_id, update_role);
}

void Roles::Delete(pqxx::connection &conn, int role_id) {
    BaseCrud<Roles>::Delete(conn, role_id);
}