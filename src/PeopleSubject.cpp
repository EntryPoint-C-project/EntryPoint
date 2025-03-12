#include "../inc/PeopleSubject.hpp"

void PeopleSubject::loadFromRow(const pqxx::row &row) {
    person_id = row["person_id"].as<int>();
    subject_id = row["subject_id"].as<int>();
}


static void Create(pqxx::connection &conn, int person_id, int subject_id) {
    PeopleSubject people_subject;
    people_subject.person_id = person_id;
    people_subject.subject_id = subject_id;
    BaseCrud<PeopleSubject>::Create(conn, people_subject);
}


static std::vector<PeopleSubject> ReadSubject(pqxx::connection &conn , int person_id) {
    return BaseCrud<PeopleSubject>::Read(conn , person_id);
}   

static std::vector<PeopleSubject> ReadPeople(pqxx::connection &conn , int subject_id) {
    return BaseCrud<PeopleSubject>::Read(conn , subject_id);
}   

static void Update(pqxx::connection &conn, int person_id, std::vector<std::string> new_params_for_people_subject) {
    PeopleSubject updated_people_subject;
    updated_people_subject.person_id = person_id;
    updated_people_subject.subject_id = std::stoi(new_params_for_people_subject[0]);
    BaseCrud<PeopleSubject>::Update(conn, person_id, updated_people_subject);
}

static void Delete(pqxx::connection &conn, int person_id) {
    BaseCrud<PeopleSubject>::Delete(conn, person_id);
}