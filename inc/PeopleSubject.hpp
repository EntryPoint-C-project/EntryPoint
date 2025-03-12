#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class PeopleSubject : public ICompositePrimaryKeyEntity {
public:
    int person_id;
    int subject_id;

    std::pair <int , int> GetPrimaryKey() const { return std::make_pair(person_id, subject_id); }
    void SetPrimaryKey(std::pair<int, int> ids) { person_id = ids.first; subject_id = ids.second; }

    static const inline std::string table_name = "people_subject";
    static const inline std::vector<std::string> columns = {"person_id", "subject_id"};
    
    void loadFromRow(const pqxx::row &row); 
    auto get_values_tuple() const {
        return std::make_tuple(person_id, subject_id);
    }
    static void Create(pqxx::connection &conn, int person_id, int subject_id) ;
    static std::vector<PeopleSubject> ReadSubject(pqxx::connection &conn , int person_id) ;
    static std::vector<PeopleSubject> ReadPeople(pqxx::connection &conn , int subject_id) ;
    static void Update(pqxx::connection &conn, int person_id, std::vector<std::string> new_params_for_people_subject) ;
    static void Delete(pqxx::connection &conn, int person_id) ;
    friend std::ostream& operator<<(std::ostream& os, const PeopleSubject& ps) {
        return os << fmt::format( "PeopleSubject(Person: {}, Subject: {})", ps.person_id, ps.subject_id );
    }
};

template <>
struct fmt::formatter<PeopleSubject> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const PeopleSubject& ps, format_context& ctx) const {
        return format_to(ctx.out(), 
            "PeopleSubject(Person: {}, Subject: {})",
            ps.person_id, ps.subject_id
        );
    }
};