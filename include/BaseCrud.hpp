#pragma once
#include <pqxx/pqxx>
#include "IPrimaryKeyEntity.hpp"
#include <vector>
#include <string>
#include <stdexcept>
#include <fmt/format.h>
#include <fmt/core.h>
#include <fmt/ranges.h>


template <typename T>
class BaseCrud  {
public:
    static void Create(pqxx::connection& conn, T& entity) {
        try {
            pqxx::work txn(conn);
            std::vector<std::string> columns;
            if constexpr (std::is_base_of_v<ISinglePrimaryKeyEntity, T>) {
                columns = std::vector<std::string>(std::next(T::columns.begin()), T::columns.end());
            } else if constexpr (std::is_base_of_v<ICompositePrimaryKeyEntity, T>) {
                columns = T::columns;
            } else {
                throw std::runtime_error("Entity type must implement a primary key interface.");
            }

            std::vector<std::string> placeholders;
            for (size_t i = 1; i <= columns.size(); ++i) {
                placeholders.push_back(fmt::format("${}", i));
            }

            std::string sql;
            if constexpr (std::is_base_of_v<ISinglePrimaryKeyEntity, T>) {
                sql = fmt::format("INSERT INTO {} ({}) VALUES ({}) RETURNING {};",
                                T::table_name,
                                fmt::join(columns, ", "),
                                fmt::join(placeholders, ", "),
                                T::columns[0]);
            } else if constexpr (std::is_base_of_v<ICompositePrimaryKeyEntity, T>) {
                sql = fmt::format("INSERT INTO {} ({}) VALUES ({}) RETURNING {}, {};",
                                T::table_name,
                                fmt::join(columns, ", "),
                                fmt::join(placeholders, ", "),
                                T::columns[0],
                                T::columns[1]);
            }

            auto values = entity.get_values_tuple();
            if constexpr (std::is_base_of_v<ISinglePrimaryKeyEntity, T>) {
                pqxx::result result = std::apply([&sql, &txn](const auto&... args) {
                    return txn.exec_params(sql, args...);
                }, values);
                    entity.SetEntityPrimaryKey(entity, result, T::columns[0]);
            } else if constexpr (std::is_base_of_v<ICompositePrimaryKeyEntity, T>) {
                pqxx::result res = std::apply([&sql, &txn](const auto&... args) {
                    return txn.exec_params(sql, args...);
                }, values);
                entity.SetEntityPrimaryKey(entity, res, T::columns[0], T::columns[1]);
            }

            txn.commit();
        } catch (const std::exception& e) {
            throw std::runtime_error(fmt::format("Create error: {}", e.what()));
        }
    }

    static std::vector<T> Read(pqxx::connection &conn , int id ) {
        std::vector<T> result;
        try {
            pqxx::work txn(conn);
            std::string sql = fmt::format("SELECT * FROM {} WHERE {} = ${}; ", T::table_name, T::columns[0], 1);
            pqxx::result res = txn.exec(sql , id);

            for (const auto& row : res) {
                T entity;
                entity.loadFromRow(row);
                result.push_back(entity);
            }

            txn.commit();
        } catch (const std::exception &e) {
            throw std::runtime_error(fmt::format("Read error: {} ", e.what()));
        }
        return result;
    }

    static void Update(pqxx::connection &conn, int id, const T &entity) {
        try {
            pqxx::work txn(conn);
            std::vector<std::string> set_clauses;

            for (size_t i = 1; i < T::columns.size(); ++i) {
                set_clauses.push_back(fmt::format("{} = ${}", T::columns[i], i));
            }
            std::string sql = fmt::format("UPDATE {} SET {} WHERE {} = ${}", T::table_name, fmt::join(set_clauses, ", "), T::columns[0], T::columns.size() );

            auto values = entity.get_values_tuple(); 

            if constexpr (std::is_base_of_v<ISinglePrimaryKeyEntity, T>) {
            std::apply([&sql, &txn ,&id](const auto&... args) {
                txn.exec_params(sql, args...,id );
            }, values);
            } else if constexpr (std::is_base_of_v<ICompositePrimaryKeyEntity, T>) {
            std::apply([&sql, &txn ,&id](const auto&... args) {
                txn.exec_params(sql, args... );
            }, values);
            } else {
                throw std::runtime_error("Entity type must implement a primary key interface.");
            }



            txn.commit();
        } catch (const std::exception& e) {
            throw std::runtime_error(fmt::format("Update error: {}", e.what()));
        }
    }

    static void Delete(pqxx::connection& conn, int id) {
        try {
            pqxx::work txn(conn);
            std::string sql = fmt::format( "DELETE FROM {} WHERE {} = $1", T::table_name, T::columns[0] ); 
            
            txn.exec_params(sql, id);
            txn.commit();
        } catch (const std::exception& e) {
            throw std::runtime_error(fmt::format("Delete error: {}", e.what()));
        }
    }
};
