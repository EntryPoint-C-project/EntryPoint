#include "../inc/ResultRequest.hpp"


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

static std::vector<ResultRequest> Read(pqxx::connection &conn) {
    return BaseCrud<ResultRequest>::Read(conn);
}

static void Update(pqxx::connection &conn, int result_id, std::vector<std::string> new_params_for_result_request) {
    ResultRequest updated_result_request;
    updated_result_request.result_id = result_id;
    updated_result_request.request_id = std::stoi(new_params_for_result_request[0]);
    BaseCrud<ResultRequest>::Update(conn, result_id, updated_result_request);
}

static void Delete(pqxx::connection &conn, int result_id) {
    BaseCrud<ResultRequest>::Delete(conn, result_id);
}