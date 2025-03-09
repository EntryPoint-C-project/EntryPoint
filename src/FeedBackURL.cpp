#include "../inc/FeedBackURL.hpp"

void FeedBackURL::loadFromRow(const pqxx::row &row) {
    result_id = row["result_id"].as<int>();
    student_id = row["student_id"].as<int>();
    form_url = row["form_url"].as<std::string>();
}

static void Create(pqxx::connection &conn, int student_id, const std::string &form_url) {
    FeedBackURL feedBackURL;
    feedBackURL.student_id = student_id;
    feedBackURL.form_url = form_url;
    BaseCrud<FeedBackURL>::Create(conn, feedBackURL);
}

static std::vector<FeedBackURL> Read(pqxx::connection &conn) {
    return BaseCrud<FeedBackURL>::Read(conn);
}

static void Update(pqxx::connection &conn, int result_id, std::vector<std::string> new_params_for_result) {
    FeedBackURL feedBackURL_updated;
    feedBackURL_updated.result_id = result_id;
    feedBackURL_updated.student_id = std::stoi(new_params_for_result[1]);
    feedBackURL_updated.form_url = new_params_for_result[0];
    BaseCrud<FeedBackURL>::Update(conn, result_id, feedBackURL_updated);
}

static void Delete(pqxx::connection &conn, int result_id) {
    BaseCrud<FeedBackURL>::Delete(conn, result_id);
}