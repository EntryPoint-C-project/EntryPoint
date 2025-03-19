#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class ResultRequest : public ICompositePrimaryKeyEntity {
public:
    int result_id;
    int request_id;

    std::pair <int , int> GetPrimaryKey() const { return std::make_pair(result_id, request_id); }
    void SetPrimaryKey(std::pair<int, int> ids) { result_id = ids.first; request_id = ids.second; }
    static const inline std::string table_name = "result_request";
    static const inline std::vector<std::string> columns = {"result_id", "request_id"};
    
    void loadFromRow(const pqxx::row &row); 
    auto get_values_tuple() const {
        return std::make_tuple(result_id, request_id);
    }
    static void Create(pqxx::connection &conn, int result_id, int request_id) ;
    static void UpdateLinkingPlates(pqxx::connection &conn, std::pair<int ,int > ids, std::pair<int , int> new_params_for_result_request) ;
    static void DeleteFromLinkingPlates(pqxx::connection &conn, std::pair<int , int> ids) ;
    friend std::ostream& operator<<(std::ostream& os, const ResultRequest& rr) {
        return os << fmt::format( "ResultRequest(Result: {}, Request: {})", rr.result_id, rr.request_id );
    }
};

template <>
struct fmt::formatter<ResultRequest> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    auto format(const ResultRequest& rr, format_context& ctx) const {
        return format_to(ctx.out(), 
            "ResultRequest(Result: {}, Request: {})",
            rr.result_id, rr.request_id
        );
    }
};