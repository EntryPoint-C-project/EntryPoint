#include "../include/SubjectTags.hpp"

void SubjectTags::loadFromRow(const pqxx::row &row) {
    subject_id = row["subject_id"].as<int>();
    tag_id = row["tag_id"].as<int>();
}

static void Create(pqxx::connection &conn, int subject_id, int tag_id) {
    SubjectTags subject_tag;
    subject_tag.subject_id = subject_id;
    subject_tag.tag_id = tag_id;
    BaseCrud<SubjectTags>::Create(conn, subject_tag);
}

static void UpdateLinkingPlates(pqxx::connection &conn, std::pair<int ,int > ids, std::pair<int , int> new_params_for_subject_tags) {
    BaseCrud<SubjectTags>::UpdateLinkingPlates(conn, ids, new_params_for_subject_tags);
}

static void DeleteFromLinkingPlates(pqxx::connection &conn, std::pair<int , int> ids) {
    BaseCrud<SubjectTags>::DeleteFromLinkingPlates(conn, ids);
}