
#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class Feedback_Participants {
public:
    static void Create(pqxx::connection &conn,  int student_id , int feedback_id , std::string student_feedback); 

    static std::string  ReadFeedback(pqxx::connection &conn, const int student_id ,const int feedback_id );   

    static void Update(pqxx::connection &conn, std::string old_feedback  , std::string new_feedback ,const  int student_id ,const  int feedback_id);

    static void Remove(pqxx::connection &conn, const int student_id ,const int feedback_id ); 
}; 