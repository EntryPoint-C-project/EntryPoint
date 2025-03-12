#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class FilterInludes: public ICompositePrimaryKeyEntity {
public:
    int filter_id;
    int tag_id;

    std::pair <int , int> GetPrimaryKey() const { return std::make_pair(filter_id, tag_id); }
    void SetPrimaryKey(std::pair<int, int> ids) { filter_id = ids.first; tag_id = ids.second; }

    static const inline std::string table_name = "filter_includes";
    static const inline std::vector<std::string> columns = {"filter_id", "tag_id"};
    
    void loadFromRow(const pqxx::row &row); 
    auto get_values_tuple() const {
        return std::make_tuple(filter_id, tag_id);
    }
    static void Create(pqxx::connection &conn, int filter_id, int tag_id) ;
    static std::vector<FilterInludes> ReadTag(pqxx::connection &conn , int filter_id) ;
    static std::vector<FilterInludes> ReadFitler(pqxx::connection &conn , int tag_id) ;
    static void Update(pqxx::connection &conn, int filter_id, std::vector<std::string> new_params_for_filter_includes) ;
    static void Delete(pqxx::connection &conn, int filter_id) ;
    friend std::ostream& operator<<(std::ostream& os, const FilterInludes& fi) {
        return os << fmt::format( "FilterInludes(Person: {}, Subject: {})", fi.filter_id, fi.tag_id );
    }
};

template <>
struct fmt::formatter<FilterInludes> {
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }
    template <typename FormatContext>
    auto format(const FilterInludes &fi, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "FilterInludes(Person: {}, Subject: {})", fi.filter_id, fi.tag_id);
    }
};