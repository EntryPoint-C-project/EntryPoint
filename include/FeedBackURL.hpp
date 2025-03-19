#pragma once
#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class FeedBackURL : public ISinglePrimaryKeyEntity {
public:
    int result_id;
    int student_id;
    std::string form_url;

    int GetPrimaryKey() const override { return result_id; }
    void SetPrimaryKey(int id) override { result_id = id; }
    static const inline std::string table_name = "feedback_urls";
    static const inline std::vector<std::string> columns = {"result_id", "student_id", "form_url"};

    void loadFromRow(const pqxx::row &row) ;
    auto get_values_tuple() const {
        return std::make_tuple(student_id, form_url);
    }
    static void Create(pqxx::connection &conn, int student_id, const std::string &form_url) ;
    static FeedBackURL Read(pqxx::connection &conn , int result_id) ;
    static void Update(pqxx::connection &conn, int result_id, std::vector<std::string> new_params_for_result) ;
    static void Delete(pqxx::connection &conn, int result_id) ;
    
    friend std::ostream& operator<<(std::ostream& os, const FeedBackURL& f) {
        return os << fmt::format( "FeedBackURL(ID: {}, StudentID: {}, FormURL: {})", f.result_id, f.student_id, f.form_url );
    }
};

template <>
struct fmt::formatter<FeedBackURL> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    auto format(const FeedBackURL& f, format_context& ctx) const {
        return format_to(ctx.out(), 
            "FeedBackURL(ID: {}, StudentID: {}, FormURL: {})", f.result_id, f.student_id, f.form_url );
    }
};