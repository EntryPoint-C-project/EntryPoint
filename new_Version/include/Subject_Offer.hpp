#pragma once 

#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>
#include <fmt/core.h>

class Subject_Offer{
private: 
    int offer_id;
    int people_group_id;
    int program_id;
    int course_id;
public:
    Subject_Offer(int people_group_id, int program_id, int course_id) :  people_group_id(people_group_id), program_id(program_id), course_id(course_id) {}

    void SetPrimaryKey(int id) { offer_id = id; }
    int GetPrimaryKey() const { return offer_id; }

    int GetGroupId() const { return people_group_id; }
    int GetProgramId() const { return program_id; }
    int GetCourseId() const { return course_id; }

};

int CreateSubjectOffer(pqxx::transaction_base& txn , int people_group_id, int program_id, int course_id) ;
std::tuple< int , int , int > ReadSubjectOffer(pqxx::transaction_base& txn , int offer_id) ;

bool IsThereARecordOffer(pqxx::transaction_base& txn, int people_group_id, int program_id, int course_id) ;
int GetOfferId(pqxx::transaction_base& txn, int people_group_id, int program_id, int course_id) ;
void UpdateSubjectOffer(pqxx::transaction_base& txn, int offer_id, int people_group_id, int program_id, int course_id) ;
void DeleteSubjectOffer(pqxx::transaction_base& txn, int offer_id) ;