#pragma once
#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class FeedBackRequest : public ISinglePrimaryKeyEntity {
public:
    int result_id;
    int request_id; 

    int GetPrimaryKey() const override { return result_id; }
    void SetPrimaryKey(int id) override { result_id = id; }

    static const inline std::string table_name = "feedback_requests";
    static const inline std::vector<std::string> columns = {"result_id", "request_id"};

    void loadFromRow(const pqxx::row &row);
    auto get_values_tuple() const {
        return std::make_tuple(request_id);
    }

    static void Create(pqxx::connection &conn, int result_id, int request_id) ;
    static std::vector<FeedBackRequest> Read(pqxx::connection &conn) ;
    static void Update(pqxx::connection &conn, int result_id, std::vector<std::string> new_params_for_result) ;
    static void Delete(pqxx::connection &conn, int result_id) ;

    friend std::ostream& operator<<(std::ostream& os, const FeedBackRequest& f) {
        return os << fmt::format( "FeedBackRequest(ID: {}, RequestID: {})", f.result_id, f.request_id );
    }
};

template <>
struct fmt::formatter<FeedBackRequest> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    auto format(const FeedBackRequest& f, format_context& ctx) const {
        return format_to(ctx.out(), 
            "FeedBackRequest(ID: {}, RequestID: {})", f.result_id, f.request_id );
    }
};