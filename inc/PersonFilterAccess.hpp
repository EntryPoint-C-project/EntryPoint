#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class PersonFilterAccess : public ICompositePrimaryKeyEntity {
public:
    int person_id;
    int filter_id;

    std::pair <int , int> GetPrimaryKey() const { return std::make_pair(person_id, filter_id); }
    void SetPrimaryKey(std::pair<int, int> ids) { person_id = ids.first; filter_id = ids.second; }
    
    static const inline std::string table_name = "person_filter_access";
    static const inline std::vector<std::string> columns = {"person_id", "filter_id"};
    
    void loadFromRow(const pqxx::row &row); 
    auto get_values_tuple() const {
        return std::make_tuple(person_id, filter_id);
    }
    static void Create(pqxx::connection &conn, int person_id, int filter_id) ;
    static std::vector<PersonFilterAccess> Read(pqxx::connection &conn);
    static void Update(pqxx::connection &conn, int person_id, std::vector<std::string> new_params_for_person_filter_access) ;
    static void Delete(pqxx::connection &conn, int person_id) ;
    friend std::ostream& operator<<(std::ostream& os, const PersonFilterAccess& pfa) {
        return os << fmt::format( "PersonFilterAccess(Person: {}, Filter: {})", pfa.person_id, pfa.filter_id );
    }
};

template <>
struct fmt::formatter<PersonFilterAccess> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const PersonFilterAccess& pfa, format_context& ctx) const {
        return format_to(ctx.out(), 
            "PersonFilterAccess(Person: {}, Filter: {})",
            pfa.person_id, pfa.filter_id
        );
    }
};