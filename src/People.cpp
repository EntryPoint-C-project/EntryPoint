#include "../inc/People.hpp"


void People::loadFromRow(const pqxx::row &row) {
    person_id = row["person_id"].as<int>();
    first_name = row["first_name"].as<std::string>();
    last_name = row["last_name"].as<std::string>();
    tg_nick = row["tg_nick"].as<std::string>();
}

static void Create(pqxx::connection &conn, const std::string &first_name, const std::string &last_name, const std::string &tg_nick) {
    People person;
    person.first_name = first_name;
    person.last_name = last_name;
    person.tg_nick = tg_nick;
    BaseCrud<People>::Create(conn, person);
}

static std::vector<People> Read(pqxx::connection &conn , int person_id) {
    return BaseCrud<People>::Read(conn , person_id);
}

static void Update(pqxx::connection &conn, int person_id, std::vector<std::string> new_params_for_person) {
    People updated_person;
    updated_person.person_id = person_id;
    updated_person.first_name = new_params_for_person[0];
    updated_person.last_name = new_params_for_person[1];
    updated_person.tg_nick = new_params_for_person[2];
    
    BaseCrud<People>::Update(conn, person_id, updated_person);
}

static void Delete(pqxx::connection &conn, int person_id) {
    BaseCrud<People>::Delete(conn, person_id);
}