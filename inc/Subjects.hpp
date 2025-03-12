#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class Subjects : public ISinglePrimaryKeyEntity {
public:
    int subject_id;
    std::string subject_name; 

    int GetPrimaryKey() const override { return subject_id; }
    void SetPrimaryKey(int id) override { subject_id = id; }

    static const inline std::string table_name = "subjects";
    static const inline std::vector<std::string> columns = {"subject_id", "subject_name"};
    void loadFromRow(const pqxx::row &row) ;
    auto get_values_tuple() const {
        return std::make_tuple(subject_name);
    }
    static void Create(pqxx::connection &conn, const std::string &subject_name) ;
    static std::vector<Subjects> Read(pqxx::connection &conn , int subject_id) ;
    static void Update(pqxx::connection &conn, int subject_id, std::vector<std::string> new_params_for_subject) ;
    static void Delete(pqxx::connection &conn, int subject_id) ;
    friend std::ostream& operator<<(std::ostream& os, const Subjects& s) {
        return os << fmt::format( "Subject(ID: {}, Name: {})", s.subject_id, s.subject_name );
    }
};


template <>
struct fmt::formatter<Subjects> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const Subjects& s, format_context& ctx) const {
        return format_to(ctx.out(), 
            "Subject(ID: {}, Name: {})",
            s.subject_id, s.subject_name
        );
    }
};