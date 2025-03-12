#pragma once
#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>


class Students : public ISinglePrimaryKeyEntity {
public:
    int student_id;
    int person_id;
    int program_id;
    std::string info;

    int GetPrimaryKey() const override { return student_id; }
    void SetPrimaryKey(int id) override { student_id = id; }

    static const inline std::string table_name = "students";
    static const inline std::vector<std::string> columns = {"student_id", "person_id", "program_id", "info"};

    void loadFromRow(const pqxx::row &row); 


    auto get_values_tuple() const {
        return std::make_tuple(person_id, program_id, info);
    }

    static void Create(pqxx::connection &conn, int person_id, int program_id, const std::string &info) ; 
    static std::vector<Students> Read(pqxx::connection &conn , int person_id) ; 
    static void Update(pqxx::connection &conn, int student_id, std::vector<std::string> new_params_for_student) ; 
    static void Delete(pqxx::connection &conn, int student_id) ; 

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
