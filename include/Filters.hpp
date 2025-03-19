#pragma once
#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <vector>
#include <string>
#include <pqxx/pqxx>
#include <fmt/format.h>
class Filters : public ISinglePrimaryKeyEntity {
public:
    int filter_id;
    std::string filter_name;

    int GetPrimaryKey() const override { return filter_id; }
    void SetPrimaryKey(int id) override { filter_id = id; }
    static const inline std::string table_name = "filters";
    static const inline std::vector<std::string> columns = {"filter_id", "filter_name"};

    void loadFromRow(const pqxx::row &row) ;
    auto get_values_tuple() const {
        return std::make_tuple(filter_name);
    }
    static void Create(pqxx::connection &conn, const std::string &filter_name) ;
    static Filters Read(pqxx::connection &conn , int filter_id) ;
    static void Update(pqxx::connection &conn, int filter_id, std::vector<std::string> new_params_for_filter) ;
    static void Delete(pqxx::connection &conn, int filter_id) ;
    friend std::ostream& operator<<(std::ostream& os, const Filters& f) {
        return os << fmt::format( "Filter(ID: {}, Name: {})", f.filter_id, f.filter_name );
    }
};

template <>
struct fmt::formatter<Filters> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    auto format(const Filters& f, format_context& ctx) const {
        return format_to(ctx.out(), 
            "Filter(ID: {}, Name: {})", f.filter_id, f.filter_name );
    }
};
