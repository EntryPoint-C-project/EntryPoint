#include "../include/TeacherSubject.hpp"

void TeacherSubject::loadFromRow(const pqxx::row &row) {
    teacher_id = row["teacher_id"].as<int>();
    subject_id = row["subject_id"].as<int>();
}

static void Create(pqxx::connection &conn, int teacher_id, int subject_id) {
    TeacherSubject teacher_subject;
    teacher_subject.teacher_id = teacher_id;
    teacher_subject.subject_id = subject_id;
    BaseCrud<TeacherSubject>::Create(conn, teacher_subject);
}

static void UpdateLinkingPlates(pqxx::connection &conn, std::pair<int ,int > ids, std::pair<int , int> new_params_for_teacher_subject) {
    BaseCrud<TeacherSubject>::UpdateLinkingPlates(conn, ids, new_params_for_teacher_subject);
}

static void DeleteFromLinkingPlates(pqxx::connection &conn, std::pair<int , int> ids) {
    BaseCrud<TeacherSubject>::DeleteFromLinkingPlates(conn, ids);
}