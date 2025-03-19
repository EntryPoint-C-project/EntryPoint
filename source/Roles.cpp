#include "../include/Roles.hpp"


void Roles::loadFromRow(const pqxx::row &row) {
    role_id = row["role_id"].as<int>();
    role_name = row["role_name"].as<std::string>();
}


static void Create(pqxx::connection &conn , const std::string &role_name) {
    Roles role; 
    role.role_name = role_name;
    BaseCrud<Roles>::Create(conn, role);
}

static Roles Read(pqxx::connection &conn , int role_id) {
    return BaseCrud<Roles>::Read(conn , role_id);
}

static void Update(pqxx::connection &conn, int role_id, std::vector<std::string> new_params_for_role) {
    Roles update_role;
    update_role.role_name = new_params_for_role[0]; 
    BaseCrud<Roles>::Update(conn, role_id, update_role);
}

static void Delete(pqxx::connection &conn, int role_id) {
    BaseCrud<Roles>::Delete(conn, role_id);
}