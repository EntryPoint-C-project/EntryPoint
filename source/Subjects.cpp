#include "../include/Subjects.hpp"

void Subjects::loadFromRow(const pqxx::row &row) {
    subject_id = row["subject_id"].as<int>();
    subject_name = row["subject_name"].as<std::string>();
}

void Subjects::Create(pqxx::connection &conn, const std::string &subject_name) {
    Subjects subject; 
    subject.subject_name = subject_name;
    BaseCrud<Subjects>::Create(conn, subject);
}

std::vector<Subjects> Subjects::Read(pqxx::connection &conn , int subject_id) {
    return BaseCrud<Subjects>::Read(conn , subject_id);
}

void Subjects::Update(pqxx::connection &conn, int subject_id, std::vector<std::string> new_params_for_subject) {
    Subjects updated_subject;
    updated_subject.subject_id = subject_id ;
    updated_subject.subject_name = new_params_for_subject[0];
    BaseCrud<Subjects>::Update(conn, subject_id, updated_subject);
}

void Subjects::Delete(pqxx::connection &conn, int subject_id) {
    BaseCrud<Subjects>::Delete(conn, subject_id);
}