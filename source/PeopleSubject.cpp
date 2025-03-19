#include "../include/PeopleSubject.hpp"

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

static void UpdateLinkingPlates(pqxx::connection &conn, std::pair<int ,int > ids, std::pair<int , int> new_params_for_people_subject) {
    BaseCrud<PeopleSubject>::UpdateLinkingPlates(conn, ids, new_params_for_people_subject);
}


static void DeleteFromLinkingPlates(pqxx::connection &conn, std::pair<int , int> ids) {
    BaseCrud<PeopleSubject>::DeleteFromLinkingPlates(conn, ids);
}   