#pragma once 
#include <iostream>
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>


class SOP_Form {
private: 
    int sop_id;
    int person_id;
    std::string url ; 
    std::string status;
    std::string tg_answer;
    std::string url_answer;

public : 
    SOP_Form( int person_id, std::string url ,  std::string tg_answer , std::string url_answer) : person_id(person_id), url(url), tg_answer(tg_answer), url_answer(url_answer) {} 

    void SetPrimaryKey(int id) { sop_id = id; }
    int GetPrimaryKey() const { return sop_id; }
    int GetPersonId() const { return person_id; }
    std::string GetUrl() const { return url; }
    std::string  GetStatus() const { return status; }
    std::string GetTgAnswer() const { return tg_answer; }
    std::string GetUrlAnswer() const { return url_answer; }
}; 

int CreateSOPForm(pqxx::transaction_base& txn ,int person_id, const std::string url , std::string tg_answer, std::string url_answer) ;
std::tuple < int , std::string , std::string  , std::string , std::string > ReadSOPForm(pqxx::transaction_base& txn , int sop_id) ;


void UpdatePersonId(pqxx::transaction_base& txn, int sop_id, int new_person_id) ;
void UpdateUrl(pqxx::transaction_base& txn, int sop_id, std::string new_url) ;
void UpdateStatus(pqxx::transaction_base& txn, int sop_id, std::string new_status) ;
void UpdateTgAnswer(pqxx::transaction_base& txn, int sop_id, std::string new_tg_answer) ;
void UpdateUrlAnswer(pqxx::transaction_base& txn, int sop_id, std::string new_url_answer) ;

void  DeleteSOPForm(pqxx::transaction_base& txn, int sop_id) ;