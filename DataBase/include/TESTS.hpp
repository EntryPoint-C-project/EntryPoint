#pragma once
#include <iostream> 
#include <pqxx/pqxx>
#include <fmt/core.h>
#include <fmt/printf.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include "../include/Person.hpp"
#include "../include/Subject.hpp"
#include "../include/Person_Role.hpp"
#include "../include/Role.hpp"
#include "../include/Program.hpp"
#include "../include/SOP_Form.hpp"
#include "../include/Subject_Offer.hpp"
#include "../include/Teaching_Assigment.hpp"
#include "../include/Course.hpp"
#include "../include/People_Group.hpp"
#include "Dop_Functions.hpp"
#include "../include/Dop_Functions.hpp"



void TEST_PERSON(pqxx::transaction_base& txn  ) ; 

void TEST_SUBJECT(pqxx::transaction_base& txn  ) ;

void TEST_SUBJECT_OFFER(pqxx::transaction_base& txn  ) ;

void TEST_PERSON_GROUP(pqxx::transaction_base& txn  ) ;

void TEST_ROLE(pqxx::transaction_base& txn  ) ;

void TEST_PROGRAM(pqxx::transaction_base& txn  ) ;

void TEST_SOP_FORM(pqxx::transaction_base& txn  ) ;

void TEST_TEACGING_ASSIGMENTS(pqxx::transaction_base& txn  ) ;

void TEST_PERSON_ROLE(pqxx::transaction_base& txn  ) ;

void TEST_COURSE(pqxx::transaction_base& txn  ) ;


void TEST_GET_ALL_TEACHERS(pqxx::transaction_base& txn  ) ;

