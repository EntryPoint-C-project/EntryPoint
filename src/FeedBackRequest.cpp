#include "../inc/FeedBackRequest.hpp"

void FeedBackRequest::loadFromRow(const pqxx::row &row) {
    result_id = row["result_id"].as<int>();
    request_id = row["request_id"].as<int>();
}

static void Create(pqxx::connection &conn, int result_id, int request_id) {
    FeedBackRequest feedBackRequest;
    feedBackRequest.result_id = result_id;
    feedBackRequest.request_id = request_id;
    BaseCrud<FeedBackRequest>::Create(conn, feedBackRequest);
}

static std::vector<FeedBackRequest> Read(pqxx::connection &conn) {
    return BaseCrud<FeedBackRequest>::Read(conn);
}

static void Update(pqxx::connection &conn, int result_id, std::vector<std::string> new_params_for_result) {
    FeedBackRequest feedBackRequest_updated;
    feedBackRequest_updated.result_id = result_id;
    feedBackRequest_updated.request_id = std::stoi(new_params_for_result[0]);
    BaseCrud<FeedBackRequest>::Update(conn, result_id, feedBackRequest_updated);
}

static void Delete(pqxx::connection &conn, int result_id) {
    BaseCrud<FeedBackRequest>::Delete(conn, result_id);
}