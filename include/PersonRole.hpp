#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class PersonRole : public ICompositePrimaryKeyEntity {
public:
    int person_id;
    int role_id;
    std::pair <int , int> GetPrimaryKey() const { return std::make_pair(person_id, role_id); }
    void SetPrimaryKey(std::pair<int, int> ids) { person_id = ids.first; role_id = ids.second; }

    static const inline std::string table_name = "person_role";
    static const inline std::vector<std::string> columns = {"person_id", "role_id"};
    
    void loadFromRow(const pqxx::row &row);
    auto get_values_tuple() const {
        return std::make_tuple(person_id, role_id);
    }
    static void Create(pqxx::connection &conn, int person_id, int role_id) ;
    static std::vector<PersonRole> ReadRole(pqxx::connection &conn , int person_id) ;
    static std::vector<PersonRole> ReadPerson(pqxx::connection &conn , int role_id) ;
    static void Update(pqxx::connection &conn, int person_id, std::vector<std::string> new_params_for_person_role) ;
    static void Delete(pqxx::connection &conn, int person_id) ;
    friend std::ostream& operator<<(std::ostream& os, const PersonRole& pr) {
        return os << fmt::format( "PersonRole(Person: {}, Role: {})", pr.person_id, pr.role_id );
    }
};

template <>
struct fmt::formatter<PersonRole> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const PersonRole& pr, format_context& ctx) const {
        return format_to(ctx.out(), 
            "PersonRole(Person: {}, Role: {})",
            pr.person_id, pr.role_id
        );
    }
};