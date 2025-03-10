#pragma once
#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <vector>
#include <string>
#include <pqxx/pqxx>
#include <fmt/format.h>

class Tags : public ISinglePrimaryKeyEntity {
public:
    int tag_id;
    std::string tag_name;
    int GetPrimaryKey() const override { return tag_id; }
    void SetPrimaryKey(int id) override { tag_id = id; }
    static const inline std::string table_name = "tags";
    static const inline std::vector<std::string> columns = {"tag_id", "tag_name"};
    void loadFromRow(const pqxx::row &row) ;
    auto get_values_tuple() const {
        return std::make_tuple(tag_name);
    }
    static void Create(pqxx::connection &conn, const std::string &tag_name) ;
    static std::vector<Tags> Read(pqxx::connection &conn) ;
    static void Update(pqxx::connection &conn, int tag_id, std::vector<std::string> new_params_for_tag) ;
    static void Delete(pqxx::connection &conn, int tag_id) ;
    friend std::ostream& operator<<(std::ostream& os, const Tags& t) {
        return os << fmt::format( "Tag(ID: {}, Name: {})", t.tag_id, t.tag_name );
    }
};

template <>
struct fmt::formatter<Tags> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    auto format(const Tags& t, format_context& ctx) const {
        return format_to(ctx.out(), 
            "Tag(ID: {}, Name: {})", t.tag_id, t.tag_name );
    }
};