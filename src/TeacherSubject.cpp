#include "../inc/TeacherSubject.hpp"

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

static std::vector<TeacherSubject> Read(pqxx::connection &conn) {
    return BaseCrud<TeacherSubject>::Read(conn);
}

static void Update(pqxx::connection &conn, int teacher_id, std::vector<std::string> new_params_for_teacher_subject) {
    TeacherSubject updated_teacher_subject;
    updated_teacher_subject.teacher_id = teacher_id;
    updated_teacher_subject.subject_id = std::stoi(new_params_for_teacher_subject[0]);
    BaseCrud<TeacherSubject>::Update(conn, teacher_id, updated_teacher_subject);
}

static void Delete(pqxx::connection &conn, int teacher_id) {
    BaseCrud<TeacherSubject>::Delete(conn, teacher_id);
}
