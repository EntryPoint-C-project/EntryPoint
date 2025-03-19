#include "../include/ResultRequest.hpp"


void ResultRequest::loadFromRow(const pqxx::row &row) {
    result_id = row["result_id"].as<int>();
    request_id = row["request_id"].as<int>();
}

static void Create(pqxx::connection &conn, int result_id, int request_id) {
    ResultRequest result_request;
    result_request.result_id = result_id;
    result_request.request_id = request_id;
    BaseCrud<ResultRequest>::Create(conn, result_request);
}

static void UpdateLinkingPlates(pqxx::connection &conn, std::pair<int ,int > ids, std::pair<int , int> new_params_for_result_request) {
    BaseCrud<ResultRequest>::UpdateLinkingPlates(conn, ids, new_params_for_result_request);
}

static void DeleteFromLinkingPlates(pqxx::connection &conn, std::pair<int , int> ids) {
    BaseCrud<ResultRequest>::DeleteFromLinkingPlates(conn, ids);
}