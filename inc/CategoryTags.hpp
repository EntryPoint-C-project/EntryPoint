#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class CategoryTags : public ICompositePrimaryKeyEntity {
public:
    int category_id;
    int tag_id ; 
    
    std::pair<int, int> GetPrimaryKey() const { return std::make_pair(category_id, tag_id); }
    void SetPrimaryKey(std::pair<int, int> ids) { category_id = ids.first; tag_id = ids.second; }

    static const inline std::string table_name = "category_tags";
    static const inline std::vector<std::string> columns = {"category_id", "tag_id"};
    
    void loadFromRow(const pqxx::row &row); 
    auto get_values_tuple() const {
        return std::make_tuple(category_id, tag_id);
    }
    static void Create(pqxx::connection &conn, int category_id, int tag_id) ;
    static std::vector<CategoryTags> Read(pqxx::connection &conn) ;
    static void Update(pqxx::connection &conn, int category_id, std::vector<std::string> new_params_for_category) ;
    static void Delete(pqxx::connection &conn, int category_id) ;
    friend std::ostream& operator<<(std::ostream& os, const CategoryTags& ct) {
        return os << fmt::format( "CategoryTags(Category: {}, Tag: {})", ct.category_id, ct.tag_id  );
    }
}; 

template <>
struct fmt::formatter<CategoryTags> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const CategoryTags& ct, format_context& ctx) const {
        return format_to(ctx.out(), 
            "CategoryTags(Category: {}, Tag: {})",
            ct.category_id, ct.tag_id
        );
    }
};