#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <pqxx/pqxx>
#include <utility>
#include <iomanip>

#include "Categories.hpp"
#include "Subjects.hpp"
#include "Tags.hpp"
#include "SubjectTags.hpp"
#include "PeopleSubject.hpp"
#include "PersonFilterAccess.hpp"
#include "Filters.hpp"
#include <FilterIncludes.hpp>
#include <FilterExcludes.hpp>
#include "CategoryTags.hpp"
#include "SubjectTags.hpp"
#include "CreateAllTables.hpp"
#include "DeleteAllTables.hpp"
#include "Feedback_Participants.hpp"
#include "Feedback.hpp"
#include "People.hpp"
#include "Roles.hpp"
#include "Programs.hpp"
#include "Students.hpp"
#include "TeacherSubject.hpp"
#include "PersonRole.hpp"


std::string ReturnSqlRequesInFile( std::string &filename) ; 

static bool VerificationAdmin(pqxx::connection &conn , const int person_id); 