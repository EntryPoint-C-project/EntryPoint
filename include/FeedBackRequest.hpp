#pragma once
#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class FeedBackRequest : public ISinglePrimaryKeyEntity {
public:
    int request_id; 
    int teacher_id ; 
    int subject_id; 
    std::string request_name ; 

    int GetPrimaryKey() const override { return request_id; }
    void SetPrimaryKey(int id) override { request_id = id; }

    static const inline std::string table_name = "feedback_requests";
    static const inline std::vector<std::string> columns = {"request_id", "teacher_id", "subject_id", "request_name"};

    void loadFromRow(const pqxx::row &row);
    auto get_values_tuple() const {
        return std::make_tuple(request_id, teacher_id , subject_id, request_name);
    }

    static void Create(pqxx::connection &conn, int teacher_id, int subject_id, const std::string &request_name) ;
    static FeedBackRequest Read(pqxx::connection &conn, int request_id) ;
    static void UpdateLinkingPlates(pqxx::connection &conn, std::pair<int ,int > ids, std::pair<int , int> new_params_for_request) ;
    static void DeleteFromLinkingPlates(pqxx::connection &conn, std::pair<int , int> ids) ;

    friend std::ostream& operator<<(std::ostream& os, const FeedBackRequest& f) {
        return os << fmt::format ("FeedBackRequest(ID: {}, TeacherID: {}, SubjectID: {}, RequestName: {})", f.request_id, f.teacher_id, f.subject_id, f.request_name );
    }
};

template <>
struct fmt::formatter<FeedBackRequest> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    auto format(const FeedBackRequest& f, format_context& ctx) const {
        return format_to(ctx.out(), 
            "FeedBackRequest(ID: {}, TeacherID: {}, SubjectID: {}, RequestName: {})", f.request_id, f.teacher_id, f.subject_id, f.request_name );
    }
};