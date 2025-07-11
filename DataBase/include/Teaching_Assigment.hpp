#pragma once

#include <fmt/core.h>
#include <fmt/format.h>

#include <Subject.hpp>
#include <pqxx/pqxx>
#include <string>
#include <vector>

class Teaching_Assigment {
private:
    int assignment_id;
    int person_id;
    int offer_id;
    int subject_id;

public:
    Teaching_Assigment(int person_id, int offer_id, int subject_id)
        : person_id(person_id), offer_id(offer_id), subject_id(subject_id) {}

    void SetPrimaryKey(int id) { assignment_id = id; }
    int GetPrimaryKey() const { return assignment_id; }

    int GetPersonId() const { return person_id; }
    int GetOfferId() const { return offer_id; }
    int GetSubjectId() const { return subject_id; }
};
int CreateTeachingAssigment(pqxx::transaction_base& txn, int person_id, int offer_id,
                            int subject_id);
std::tuple<int, int, int> ReadTeachingAssigment(pqxx::transaction_base& txn, int assignment_id);
int GetTeachingAssigmentId(pqxx::transaction_base& txn, int person_id, int offer_id,
                           int subject_id);
std::vector<std::pair<int, int> > ReadInfoOnPersonId(pqxx::transaction_base& txn, int person_id);
std::vector<std::pair<int, int> > ReadInfoOnOfferIdNoStudents(pqxx::transaction_base& txn,
                                                              int offer_id);

bool IsThereARecordTeachingAssigment(pqxx::transaction_base& txn, int person_id, int offer_id,
                                     int subject_id);
void UpdateTeachingAssigment(pqxx::transaction_base& txn, int assignment_id, int person_id,
                             int offer_id, int subject_id);
void DeleteTeachingAssigment(pqxx::transaction_base& txn, int assignment_id);