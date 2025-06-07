#pragma once
#include <string>
#include <vector>
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <Person.hpp>
#include <Role.hpp>
#include <Person_Role.hpp>
#include <Subject_Offer.hpp>
#include <Teaching_Assigment.hpp>
#include <Subject.hpp>
#include <Course.hpp>
#include <Program.hpp>
#include <People_Group.hpp>
#include <Person_Role.hpp> 
#include <SOP_Form.hpp>



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

bool CorrectSnils(pqxx::transaction_base& txn, int snils , std::string tg_nick) ;


#include <sstream>
#include <vector>

struct Person {
    std::string first_name;
    std::string last_name;
    std::string tg_nick;
    int access = 0; // по умолчанию 0
    int snils;
    std::string role;
    std::string subject_name;
    std::string course_name;
    std::string program_name;
    std::string people_group_name;

    Person(const std::string& line) {
        std::istringstream iss(line);
        std::vector<std::string> parts;
        std::string part;

        while (iss >> part) {
            parts.push_back(part);
        }

        // Ожидаем, что будет ровно 10 частей
        // parts: 0:first_name, 1:last_name, 2:tg_nick, 3:access, 4:snils,
        // 5:role, 6:subject_name, 7:course_name, 8:program_name, 9:people_group_name

        if (parts.size() >= 10) {
            first_name = parts[0];
            last_name = parts[1];
            tg_nick = parts[2];
            access = std::stoi(parts[3]);
            snils = std::stoi(parts[4]);
            role = parts[5];
            subject_name = parts[6];
            course_name = parts[7];
            program_name = parts[8];
            people_group_name = parts[9];
        } else {
            // Можно выбросить исключение или установить значения по умолчанию
            // Например:
            first_name = "";
            last_name = "";
            tg_nick = "";
            access = 0;
            snils = 0;
            role = "";
            subject_name = "";
            course_name = "";
            program_name = "";
            people_group_name = "";
        }
    }
};


void CreatePersonWithParams(pqxx::transaction_base& txn ,Person  person) ;


void AssignCompletelyToPeople(pqxx::transaction_base& txn ) ;

void AssignStatusToAllPeople(pqxx::transaction_base& txn , std::string status ) ;