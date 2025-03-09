#pragma once
#include "ForTableInternal.hpp"

class FunctionForAdmin {
    public:
    static void AddStudent(pqxx::connection &conn,const  int admin , const std::string first_name, const std::string last_name, const std::string tg_nick, const int program_id,const std::string info) ; 
    // then.....

};
