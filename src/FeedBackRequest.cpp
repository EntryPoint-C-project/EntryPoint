#include "../inc/FeedBackRequest.hpp"

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

static std::vector<FeedBackRequest> Read(pqxx::connection &conn , int request_id) {
    return BaseCrud<FeedBackRequest>::Read(conn, request_id);
}

static void Update(pqxx::connection &conn, int request_id, std::vector<std::string> new_params_for_request) {
    FeedBackRequest feedBackRequest_updated;
    feedBackRequest_updated.request_id = request_id;
    feedBackRequest_updated.teacher_id = std::stoi(new_params_for_request[0]);
    feedBackRequest_updated.subject_id = std::stoi(new_params_for_request[1]);
    feedBackRequest_updated.request_name = new_params_for_request[2];
    BaseCrud<FeedBackRequest>::Update(conn, request_id, feedBackRequest_updated);
}

static void Delete(pqxx::connection &conn, int request_id) {
    BaseCrud<FeedBackRequest>::Delete(conn, request_id);
}