#include "../inc/Students.hpp"



/* 
    this is function for pqxx --> int / std::string 
*/
void Students::loadFromRow(const pqxx::row &row) {
    student_id = row["student_id"].as<int>();
    person_id = row["person_id"].as<int>();
    program_id = row["program_id"].as<int>();
    info = row["info"].as<std::string>();
}

/*  for set params for sql request*/


static void Create(pqxx::connection &conn, int person_id, int program_id, const std::string &info) {
    Students student; 

    student.person_id = person_id; 
    student.program_id = program_id;
    student.info = info; 
    BaseCrud<Students>::Create(conn, student);
}


static std::vector<Students> Read(pqxx::connection &conn) {
    return BaseCrud<Students>::Read(conn);
}



static void Update(pqxx::connection &conn, int student_id, std::vector<std::string> new_params_for_student) {  // !tesing
    Students update_student; 
    update_student.person_id = std::stoi(new_params_for_student[0]); 
    update_student.program_id = std::stoi(new_params_for_student[1]); 
    update_student.info = new_params_for_student[2]; 
    BaseCrud<Students>::Update(conn, student_id, update_student);
}

static void Delete(pqxx::connection &conn, int student_id) {
    BaseCrud<Students>::Delete(conn, student_id);
}

