#pragma once
#include <pqxx/pqxx>
#include <utility> 


class ISinglePrimaryKeyEntity {
public:
    virtual int GetPrimaryKey() const = 0; 
    virtual void SetPrimaryKey(int id) = 0;

    void SetEntityPrimaryKey(ISinglePrimaryKeyEntity& entity, const pqxx::result& result, const std::string& column_name) {
        if (!result.empty()) {
            entity.SetPrimaryKey(result[0][column_name].as<int>());
        }
    }

    virtual ~ISinglePrimaryKeyEntity() = default; 

};


class ICompositePrimaryKeyEntity {
public:
    virtual std::pair<int, int> GetPrimaryKey() const = 0;
    virtual void SetPrimaryKey(std::pair<int, int> ids) = 0;


    void SetEntityPrimaryKey(ICompositePrimaryKeyEntity& entity, const pqxx::result& result, const std::string& column_name1, const std::string& column_name2) {
        if (!result.empty()) {
            int first_key = result[0][column_name1].as<int>();
            int second_key = result[0][column_name2].as<int>();
            entity.SetPrimaryKey(std::make_pair(first_key, second_key));
        }
    }

    virtual ~ICompositePrimaryKeyEntity() = default; 
};