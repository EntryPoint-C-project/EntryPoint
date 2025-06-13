#pragma once
#include <fmt/core.h>
#include <fmt/printf.h>

#include <Course.hpp>
#include <People_Group.hpp>
#include <Person.hpp>
#include <Person_Role.hpp>
#include <Program.hpp>
#include <Role.hpp>
#include <SOP_Form.hpp>
#include <Subject.hpp>
#include <Subject_Offer.hpp>
#include <Teaching_Assigment.hpp>
#include <pqxx/pqxx>
#include <string>
#include <vector>

struct Teacher {
    std::string first_name;
    std::string last_name;
    std::vector<std::string> his_roles;
    std::string subject_name;
    std::string course_name;
    std::string program_name;
    std::string people_group_name;
};

std::vector<Teacher> GetAllTeachersForStudent(pqxx::transaction_base& txn, int student_id);

bool CorrectSnils(pqxx::transaction_base& txn, int snils, std::string tg_nick);

#include <sstream>
#include <vector>

struct Person {
    std::string first_name;
    std::string last_name;
    std::string tg_nick;
    int access = 0;  // по умолчанию 0
    int snils;
    std::string role;
    std::string subject_name;
    std::string course_name;
    std::string program_name;
    std::string people_group_name;
    Person(std::string n, std::string s, std::string p, int a, int c, std::string u, std::string f,
           std::string y, std::string d, std::string g)
        : name(n),
          surname(s),
          phone(p),
          age(a),
          course(c),
          university(u),
          faculty(f),
          year(y),
          degree(d),
          group(g) {}
};

void CreatePersonWithParams(pqxx::transaction_base& txn, Person person);

void AssignCompletelyToPeople(pqxx::transaction_base& txn);

void AssignStatusToAllPeople(pqxx::transaction_base& txn, std::string status);