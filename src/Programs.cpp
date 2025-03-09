#include "../inc/Programs.hpp"

void Programs::loadFromRow(const pqxx::row &row) {
    program_id = row["program_id"].as<int>();
    program_name = row["program_name"].as<std::string>();
}   

static void Create(pqxx::connection &conn, const std::string &program_name) {
    Programs program;
    program.program_name = program_name;
    BaseCrud<Programs>::Create(conn, program);
}

static std::vector<Programs> Read(pqxx::connection &conn) {
    return BaseCrud<Programs>::Read(conn);
}

static void Update(pqxx::connection &conn, int program_id, std::vector<std::string> new_params_for_program) {
    Programs updated_program;
    updated_program.program_id = program_id;
    updated_program.program_name = new_params_for_program[0];
    BaseCrud<Programs>::Update(conn, program_id, updated_program);
}

static void Delete(pqxx::connection &conn, int program_id) {
    BaseCrud<Programs>::Delete(conn, program_id);
}