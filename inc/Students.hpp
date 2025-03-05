
#pragma once
#include "BaseCrud.hpp"
#include <pqxx/pqxx>

class Students {
public:
    int student_id;
    int person_id;
    int program_id;
    std::string info;

    static const inline std::string table_name = "students";
    static const inline std::vector<std::string> columns = {"student_id", "person_id", "program_id", "info"};
    static const inline std::vector<std::string> insert_columns = {"person_id", "program_id", "info"};

    void loadFromRow(const pqxx::row &row) {
        student_id = row["student_id"].as<int>();
        person_id = row["person_id"].as<int>();
        program_id = row["program_id"].as<int>();
        info = row["info"].as<std::string>();
    }   

    std::vector<std::string> get_values() const {
        return {
            std::to_string(person_id),
            std::to_string(program_id),
            info
        };
    }


    std::vector<std::string> get_update_values() const {
        return {
            std::to_string(person_id),
            std::to_string(program_id),
            info
        };
    }

    static void Create(pqxx::connection &conn, int person_id, int program_id, const std::string &info) {
        Students student;
        student.person_id = person_id;
        student.program_id = program_id;
        student.info = info;
        BaseCrud<Students>::Create(conn, student);
    }


    static Students ReadById(pqxx::connection &conn, int student_id) {
        return BaseCrud<Students>::ReadById(conn, student_id);
    }

    static std::vector<Students> Read(pqxx::connection &conn) {
        return BaseCrud<Students>::Read(conn);
    }

    static void Update(pqxx::connection &conn, int student_id, int new_program_id) {
        Students student = BaseCrud<Students>::ReadById(conn, student_id);
        student.program_id = new_program_id;
        BaseCrud<Students>::Update(conn, student_id, student);
    }

    static void Delete(pqxx::connection &conn , int student_id){
        BaseCrud<Students>::Delete(conn, student_id); 
    }
};