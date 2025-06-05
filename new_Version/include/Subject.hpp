#pragma once 
#include <iostream>
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>


class Subject {
private: 
    int subject_id;
    std::string subject_name;

public : 
    Subject( std::string subject_name) :  subject_name(subject_name){}

    void SetPrimaryKey(int id) { subject_id = id; }
    int GetPrimaryKey() const { return subject_id; }
    std::string GetSubjectName() const { return subject_name; }

}; 

int CreateSubject(pqxx::transaction_base& txn , const std::string &subject_name) ;
std::string ReadSubject(pqxx::transaction_base& txn , int subject_id) ;
int ReadSubjectId(pqxx::transaction_base& txn , const std::string &subject_name) ;

bool IsThereARecordSubject(pqxx::transaction_base& txn, std::string subject_name) ;
void UpdateSubject(pqxx::transaction_base& txn, int subject_id, std::string new_subject_name) ;
void  DeleteSubject(pqxx::transaction_base& txn, int subject_id) ;