#pragma once 
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <Students.hpp>
#include <People.hpp> 
#include <fmt/format.h>
#include <fmt/core.h>
#include <fmt/ranges.h>


static std::vector <int>  GetAllStudentsId(pqxx::connection& conn ); 

static std::vector <int> GetAllPersonId(pqxx::connection &conn); 