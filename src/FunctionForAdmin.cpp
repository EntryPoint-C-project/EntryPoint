#include "FunctionForAdmin.hpp"

static void AddStudent(pqxx::connection &conn,const  int admin , const std::string first_name, const std::string last_name, const std::string tg_nick, const int program_id,const std::string info) {
    if (VerificationAdmin(conn , admin)){
        People::Create(conn, first_name, last_name, tg_nick);
        int person_id = People::ReadPersonId(conn, tg_nick);
        Students::Create(conn, person_id, program_id, info);
    }
}