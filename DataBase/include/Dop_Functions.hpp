#pragma once
#include <string>
#include <vector>
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>
#include "Person.hpp"
#include "Role.hpp"
#include "Person_Role.hpp"
#include "Subject_Offer.hpp"
#include "Teaching_Assigment.hpp"
#include "Subject.hpp"
#include "Course.hpp"
#include "Program.hpp"
#include "People_Group.hpp"
#include "Person_Role.hpp"



struct Teacher{
    std::string first_name;
    std::string last_name;
    std::vector<std::string>  his_roles ;
    std::string subject_name ; 
    std::string course_name ;
    std::string program_name ;
    std::string people_group_name ;
}; 

std::vector<Teacher> GetAllTeachersForStudent(pqxx::transaction_base& txn, int student_id) ;