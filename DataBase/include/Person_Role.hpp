#pragma once
#include <fmt/core.h>
#include <fmt/printf.h>

#include <iostream>
#include <pqxx/pqxx>

class Person_Role {
private:
    int person_id;
    int role_id;

public:
    Person_Role(int person_id, int role_id) : person_id(person_id), role_id(role_id) {}

    void SetPrimaryKey(std::pair<int, int> ids) {
        person_id = ids.first;
        role_id = ids.second;
    }
    int GetPrimaryKey() const { return person_id; }
    int GetRoleId() const { return role_id; }
};

std::pair<int, int> CreatePersonRole(pqxx::transaction_base& txn, int person_id, int role_id);

std::vector<int> ReadPersonId(pqxx::transaction_base& txn, int role_id);
std::vector<int> ReadRoleId(pqxx::transaction_base& txn, int person_id);

static void UpdatePersonRole(pqxx::transaction_base& txn, int person_id, int role_id,
                             int new_person_id, int new_role_id);
void DeletePersonRole(pqxx::transaction_base& txn, int person_id, int role_id);