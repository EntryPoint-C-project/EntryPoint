#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class Categories : public ISinglePrimaryKeyEntity {
public:
    int category_id;
    std::string category_name;
    int filter_id;
    bool required;

    int GetPrimaryKey() const override { return category_id; }
    void SetPrimaryKey(int id) override { category_id = id; }

    static const inline std::string table_name = "categories";
    static const inline std::vector<std::string> columns = {"category_id", "category_name", "filter_id", "required"};

    void loadFromRow(const pqxx::row &row);
    auto get_values_tuple() const {
        return std::make_tuple(category_name, filter_id, required);
    }

    static void Create(pqxx::connection &conn, const std::string &category_name, int filter_id, bool required) ;
    static Categories Read(pqxx::connection &conn , int category_id) ;
    static void Update(pqxx::connection &conn, int category_id, std::vector<std::string> new_params_for_category) ;
    static void Delete(pqxx::connection &conn, int category_id) ;
    friend std::ostream& operator<<(std::ostream& os, const Categories& c) {
        return os << fmt::format( "Categories(Category: {}, Filter: {}, Required: {})", c.category_id, c.category_name, c.filter_id, c.required );
    }

}; 

template <>
struct fmt::formatter<Categories> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const Categories& c, format_context& ctx) const {
        return format_to(ctx.out(), 
            "Category(ID: {}, Name: {}, Filter: {}, Required: {})",
            c.category_id, c.category_name, c.filter_id, c.required
        );
    }
};