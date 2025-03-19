#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class FilterExcludes : public ICompositePrimaryKeyEntity {
public:
    int filter_id;
    int tag_id;

    std::pair <int , int> GetPrimaryKey() const { return std::make_pair(filter_id, tag_id); }
    void SetPrimaryKey(std::pair<int, int> ids) { filter_id = ids.first; tag_id = ids.second; }

    static const inline std::string table_name = "filter_excludes";
    static const inline std::vector<std::string> columns = {"filter_id", "tag_id"};
    void loadFromRow(const pqxx::row &row);
    auto get_values_tuple() const {
        return std::make_tuple(filter_id, tag_id);
    }
    static void Create(pqxx::connection &conn, int filter_id, int tag_id) ;
    static void Update(pqxx::connection &conn, int filter_id, std::vector<std::string> new_params_for_filter_excludes) ;
    static void Delete(pqxx::connection &conn, int filter_id) ;

    friend std::ostream& operator<<(std::ostream& os, const FilterExcludes& fe) {
        return os << fmt::format( "FilterExcludes(Filter: {}, Tag: {})", fe.filter_id, fe.tag_id );
    }
}; 

template <>
struct fmt::formatter<FilterExcludes> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const FilterExcludes& fe, format_context& ctx) const {
        return format_to(ctx.out(), 
            "FilterExcludes(Filter: {}, Tag: {})",
            fe.filter_id, fe.tag_id
        );
    }
};