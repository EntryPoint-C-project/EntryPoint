
#pragma once
#include "ForTableInternal.hpp"
#include <vector>

class PersonRole {
public:
    static void Create(pqxx::connection &conn, const int person_id, const int role_id); 

    static std::vector<int> ReadRolesByPersonId(pqxx::connection &conn, const int person_id); 

    static std::vector<int> ReadPersonsByRoleId(pqxx::connection &conn, const int role_id); 

    static bool ReadInformationAboutPersonId(pqxx::connection &conn , const int person_id); 

    static void Update(pqxx::connection &conn, const int old_person_id, const int old_role_id,  const int new_person_id, const int new_role_id) ; 

    static void Remove(pqxx::connection &conn, const int person_id, const int role_id); 
};