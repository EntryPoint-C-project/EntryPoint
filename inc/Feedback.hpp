
#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Feedback {
public:
    static void Create(pqxx::connection &conn, const int teacher_id , const int subject_id , std::string feedback_name); 

    static std::string  ReadFeedbackName(pqxx::connection &conn, const int feedback_id); 

    static std::string  ReadTeacherAndSubjectId(pqxx::connection &conn, const int feedback_id); 

    static void UpdateFeedback(pqxx::connection &conn, const int teacher_id , const int subject_id , std::string old_feedback_name  , std::string new_feedback_name ); 

    static void Remove(pqxx::connection &conn, const int feedback_id ); 
}; 