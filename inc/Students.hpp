#pragma once
#include "BaseCrud.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class Students {
public:
    int student_id;
    int person_id;
    int program_id;
    std::string info;

    static const inline std::string table_name = "students";
    static const inline std::vector<std::string> columns = {"student_id", "person_id", "program_id", "info"};


    /* 
        this is function for pqxx --> int / std::string 
    */
    void loadFromRow(const pqxx::row &row) {
        student_id = row["student_id"].as<int>();
        person_id = row["person_id"].as<int>();
        program_id = row["program_id"].as<int>();
        info = row["info"].as<std::string>();
    }

    /* 
        for set params for sql request
    */
    std::vector<std::string> get_values() const {
        return {
            std::to_string(person_id),
            std::to_string(program_id),
            info  
        };
    }

    auto get_values_tuple() const {
        return std::make_tuple(person_id, program_id, info);
    }

    static void Create(pqxx::connection &conn, int person_id, int program_id, const std::string &info) {
        Students student{
            .person_id = person_id,
            .program_id = program_id,
            .info = info
        };
        BaseCrud<Students>::Create(conn, student);
    }

    static std::vector<Students> Read(pqxx::connection &conn) {
        return BaseCrud<Students>::Read(conn);
    }



    static void Update(pqxx::connection &conn, int student_id, std::vector<std::string> new_params_for_student) {  // !tesing
        Students update_student {
            .person_id = std::stoi(new_params_for_student[0]),
            .program_id = std::stoi(new_params_for_student[1]) , 
            .info = new_params_for_student[2]
        }; 
        BaseCrud<Students>::Update(conn, student_id, update_student);
    }

    static void Delete(pqxx::connection &conn, int student_id) {
        BaseCrud<Students>::Delete(conn, student_id);
    }

    friend std::ostream& operator<<(std::ostream& os, const Students& s) {
        return os << fmt::format( "Student(ID: {}, Person: {}, Program: {}, Info: {})", s.student_id, s.person_id, s.program_id, s.info );
    }
};


template <>
struct fmt::formatter<Students> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const Students& s, format_context& ctx) const {
        return format_to(ctx.out(), 
            "Student(ID: {}, Person: {}, Program: {}, Info: {})",
            s.student_id, s.person_id, s.program_id, s.info
        );
    }
};
