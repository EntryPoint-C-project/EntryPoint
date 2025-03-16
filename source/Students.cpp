#include "../include/Students.hpp"

void Students::loadFromRow(const pqxx::row &row) {
    student_id = row["student_id"].as<int>();
    person_id = row["person_id"].as<int>();
    program_id = row["program_id"].as<int>();
    info = row["info"].as<std::string>();
}

static void Create(pqxx::connection &conn, int person_id, int program_id, const std::string &info) {
    Students student; 
    student.person_id = person_id; 
    student.program_id = program_id;
    student.info = info; 
    BaseCrud<Students>::Create(conn, student);
}


static std::vector<Students> Read(pqxx::connection &conn, int student_id) {
    return BaseCrud<Students>::Read(conn, student_id);
}


static void Update(pqxx::connection &conn, int student_id, std::vector<std::string> new_params_for_student) {  
    Students update_student; 
    update_student.person_id = std::stoi(new_params_for_student[0]); 
    update_student.program_id = std::stoi(new_params_for_student[1]); 
    update_student.info = new_params_for_student[2]; 
    BaseCrud<Students>::Update(conn, student_id, update_student);
}

static void Delete(pqxx::connection &conn, int student_id) {
    BaseCrud<Students>::Delete(conn, student_id);
}

