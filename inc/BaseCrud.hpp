#pragma once
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <stdexcept>

template <typename T>
class BaseCrud {
public:
    static void Create(pqxx::connection &conn, const T &entity) {
        try {
            pqxx::work txn(conn);
            
            std::string sql = "INSERT INTO " + T::table_name + " (";
            for (size_t i = 1; i < T::columns.size(); ++i) { // Skip first column (ID)
                sql += T::columns[i];
                if (i != T::columns.size() - 1) sql += ", ";
            }
            sql += ") VALUES (";
            for (size_t i = 1; i < T::columns.size(); ++i) {
                sql += "$" + std::to_string(i);
                if (i != T::columns.size() - 1) sql += ", ";
            }
            sql += ")";

            pqxx::params params;
            for (const auto& value : entity.get_values()) {
                params.append(value);
            }

            txn.exec_params(sql, params);
            txn.commit();
        } catch (const std::exception &e) {
            throw std::runtime_error("Create error: " + std::string(e.what()));
        }
    }

    static std::vector<T> Read(pqxx::connection &conn) {
        std::vector<T> result;
        try {
            pqxx::work txn(conn);
            std::string sql = "SELECT * FROM " + T::table_name;
            
            pqxx::result res = txn.exec(sql);
            for (const auto& row : res) {
                T entity;
                entity.loadFromRow(row);
                result.push_back(entity);
            }
            txn.commit();
        } catch (const std::exception &e) {
            throw std::runtime_error("Read error: " + std::string(e.what()));
        }
        return result;
    }

    static T ReadById(pqxx::connection &conn, int id) {
        try {
            pqxx::work txn(conn);
            std::string sql = "SELECT * FROM " + T::table_name 
                            + " WHERE " + T::columns[0] + " = $1";
            
            pqxx::params params;
            params.append(std::to_string(id));
            
            pqxx::result res = txn.exec_params(sql, params);
            if (res.empty()) {
                throw std::runtime_error("Record not found");
            }
            
            T entity;
            entity.loadFromRow(res[0]);
            txn.commit();
            return entity;
        } catch (const std::exception &e) {
            throw std::runtime_error("ReadById error: " + std::string(e.what()));
        }
    }

    static void Update(pqxx::connection &conn, int id, const T &entity) {
        try {
            pqxx::work txn(conn);
            std::string sql = "UPDATE " + T::table_name + " SET ";
            
            // Generate SET clause
            for (size_t i = 1; i < T::columns.size(); ++i) {
                sql += T::columns[i] + " = $" + std::to_string(i);
                if (i != T::columns.size() - 1) sql += ", ";
            }
            
            // Add WHERE clause
            sql += " WHERE " + T::columns[0] + " = $" + std::to_string(T::columns.size());

            // Prepare parameters
            auto values = entity.get_values();
            values.push_back(std::to_string(id)); // Add ID as last parameter
            
            pqxx::params params;
            for (const auto& value : values) {
                params.append(value);
            }

            txn.exec_params(sql, params);
            txn.commit();
        } catch (const std::exception &e) {
            throw std::runtime_error("Update error: " + std::string(e.what()));
        }
    }

    static void Delete(pqxx::connection &conn, int id) {
        try {
            pqxx::work txn(conn);
            std::string sql = "DELETE FROM " + T::table_name 
                            + " WHERE " + T::columns[0] + " = $1";
            
            pqxx::params params;
            params.append(std::to_string(id));
            
            txn.exec_params(sql, params);
            txn.commit();
        } catch (const std::exception &e) {
            throw std::runtime_error("Delete error: " + std::string(e.what()));
        }
    }
};