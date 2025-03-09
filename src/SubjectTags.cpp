#include "../inc/SubjectTags.hpp"

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

static std::vector<SubjectTags> Read(pqxx::connection &conn) {
    return BaseCrud<SubjectTags>::Read(conn);
}

static void Update(pqxx::connection &conn, int subject_id, std::vector<std::string> new_params_for_subject_tags) {
    SubjectTags updated_subject_tag;
    updated_subject_tag.subject_id = subject_id;
    updated_subject_tag.tag_id = std::stoi(new_params_for_subject_tags[0]);
    BaseCrud<SubjectTags>::Update(conn, subject_id, updated_subject_tag);
}

static void Delete(pqxx::connection &conn, int subject_id) {
    BaseCrud<SubjectTags>::Delete(conn, subject_id);
}