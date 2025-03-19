#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class Programs : public ISinglePrimaryKeyEntity {
public:
    int program_id;
    std::string program_name;

    int GetPrimaryKey() const override { return program_id; }
    void SetPrimaryKey(int id) override { program_id = id; }

    static const inline std::string table_name = "programs";
    static const inline std::vector<std::string> columns = {"program_id", "program_name"};

    void loadFromRow(const pqxx::row &row);

    auto get_values_tuple() const {
        return std::make_tuple(program_name);
    }

    static void Create(pqxx::connection &conn, const std::string &program_name) ;
    static Programs Read(pqxx::connection &conn , int program_id) ;
    static void Update(pqxx::connection &conn, int program_id, std::vector<std::string> new_params_for_program) ;
    static void Delete(pqxx::connection &conn, int program_id) ;
    friend std::ostream& operator<<(std::ostream& os, const Programs& p) {
        return os << fmt::format( "Program(ID: {}, Name: {})", p.program_id, p.program_name );
    }
};

template <>
struct fmt::formatter<Programs> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const Programs& p, format_context& ctx) const {
        return format_to(ctx.out(), 
            "Program(ID: {}, Name: {})",
            p.program_id, p.program_name
        );
    }
};