#include "../include/FeedBackRequest.hpp"

void FeedBackRequest::loadFromRow(const pqxx::row &row) {
    request_id = row["request_id"].as<int>();
    teacher_id = row["teacher_id"].as<int>();
    subject_id = row["subject_id"].as<int>();
    request_name = row["request_name"].as<std::string>();
}

static void Create(pqxx::connection &conn, int teacher_id, int subject_id, const std::string &request_name) {
    FeedBackRequest feedBackRequest;
    feedBackRequest.teacher_id = teacher_id;
    feedBackRequest.subject_id = subject_id;
    feedBackRequest.request_name = request_name;
    BaseCrud<FeedBackRequest>::Create(conn, feedBackRequest);
}

static FeedBackRequest Read(pqxx::connection &conn , int request_id) {
    return BaseCrud<FeedBackRequest>::Read(conn, request_id);
}

static void UpdateLinkingPlates(pqxx::connection &conn, std::pair<int ,int > ids, std::pair<int , int> new_params_for_request) {
    BaseCrud<FeedBackRequest>::UpdateLinkingPlates(conn, ids, new_params_for_request);
}


static void DeleteFromLinkingPlates(pqxx::connection &conn, std::pair<int , int> ids) {
    BaseCrud<FeedBackRequest>::DeleteFromLinkingPlates(conn, ids);
}