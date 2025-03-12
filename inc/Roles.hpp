#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class Roles : public ISinglePrimaryKeyEntity {
public:
    int role_id; 
    std::string role_name;

    int GetPrimaryKey() const override { return role_id; }
    void SetPrimaryKey(int id) override { role_id = id; }

    static const inline std::string table_name = "roles";
    static const inline std::vector<std::string> columns = {"role_id", "role_name"};

    void loadFromRow(const pqxx::row &row) ; 

    auto get_values_tuple() const {
        return std::make_tuple( role_name);
    }

    static void Create(pqxx::connection &conn , const std::string &role_name) ; 
    static std::vector<Roles> Read(pqxx::connection &conn , int role_id) ; 
    static void Update(pqxx::connection &conn, int role_id, std::vector<std::string> new_params_for_role) ; 
    static void Delete(pqxx::connection &conn, int role_id) ; 

    friend std::ostream& operator<<(std::ostream& os, const Roles& r) {
        return os << fmt::format( "Role(ID: {}, Role: {})", r.role_id, r.role_name );
    }
}; 

template <>
struct fmt::formatter<Roles> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const Roles& r, format_context& ctx) const {
        return format_to(ctx.out(), 
            "Role(ID: {}, Role: {})",
            r.role_id, r.role_name
        );
    }
};