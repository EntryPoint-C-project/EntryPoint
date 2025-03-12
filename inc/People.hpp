#pragma once
#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>


class People : public ISinglePrimaryKeyEntity {
public:
    int person_id;
    std::string first_name;
    std::string last_name;
    std::string tg_nick;


    int GetPrimaryKey() const override { return person_id; }
    void SetPrimaryKey(int id) override { person_id = id; }
    static const inline std::string table_name = "people";
    static const inline std::vector<std::string> columns = {"person_id", "first_name", "last_name", "tg_nick"};

    void loadFromRow(const pqxx::row &row); 
    auto get_values_tuple() const {
        return std::make_tuple(first_name, last_name, tg_nick);
    }
    static void Create(pqxx::connection &conn, const std::string &first_name, const std::string &last_name, const std::string &tg_nick) ; 
    static std::vector<People> Read(pqxx::connection &conn , int person_id) ; 
    static void Update(pqxx::connection &conn, int person_id, std::vector<std::string> new_params_for_person) ; 
    static void Delete(pqxx::connection &conn, int person_id) ; 

    friend std::ostream& operator<<(std::ostream& os, const People& p) {
        return os << fmt::format( "Person(ID: {}, LastName: {}, FirstName: {}, TgNick: {})", p.person_id, p.last_name, p.first_name, p.tg_nick );
    }    
};


template <>
struct fmt::formatter<People> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const People& p, format_context& ctx) const {
        return format_to(ctx.out(), 
            "Person(ID: {}, LastName: {}, FirstName: {}, TgNick: {})", p.person_id, p.last_name, p.first_name, p.tg_nick );
    }
};