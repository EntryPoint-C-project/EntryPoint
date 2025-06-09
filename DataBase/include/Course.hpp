#pragma once 
#include <iostream>
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>


class Course {
private: 
    int course_id;
    std::string course_name;

public : 
    Course( std::string course_name) :  course_name(course_name){}

    void SetPrimaryKey(int id) { course_id = id; }
    int GetPrimaryKey() const { return course_id; }
    std::string GetCourceName() const { return course_name; }

}; 

int CreateCourse(pqxx::transaction_base& txn , const std::string &course_name) ;
std::string ReadCourse(pqxx::transaction_base& txn , int course_id) ;
int ReadCourseId(pqxx::transaction_base& txn , std::string course_name) ;

bool IsThereARecordCourse(pqxx::transaction_base& txn, std::string course_name) ;
void UpdateCourse(pqxx::transaction_base& txn, int course_id, std::string new_course_name) ;
void  DeleteCource(pqxx::transaction_base& txn, int course_id) ;