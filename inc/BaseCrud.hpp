#pragma once
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <stdexcept>
#include <fmt/format.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

template <typename T>
class BaseCrud {
public:
    static void Create(pqxx::connection& conn, const T& entity) {
        try {
            pqxx::work txn(conn);
            auto columns = std::vector<std::string>(std::next(T::columns.begin()),  T::columns.end() ); // no student_id 
            
            std::vector<std::string> placeholders;
            for (size_t i = 1; i <= columns.size(); ++i) {
                placeholders.push_back(fmt::format("${}", i));
            }

            /* 
                join - фукнция которая преобразует итератор в строчку с разделитемем , который указали 
            */
            // insert into studenst (person_id , program_id , info) values ($1 , $2 , $3) ; 
            std::string sql = fmt::format( "INSERT INTO {} ({}) VALUES ({});", T::table_name, fmt::join(columns, ", "), fmt::join(placeholders, ", ") );


            auto values = entity.get_values_tuple();

            std::apply([&sql, &txn](const auto&... args) {
                txn.exec_params(sql, args...);
            }, values);


            txn.commit();
        } catch (const std::exception& e) {
            throw std::runtime_error(fmt::format("Create error: {}", e.what()));
        }
    }

    static std::vector<T> Read(pqxx::connection &conn) {
        std::vector<T> result;
        try {
            pqxx::work txn(conn);
            std::string sql = fmt::format("SELECT * FROM {} ; ", T::table_name);
            pqxx::result res = txn.exec(sql);

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
            /* 
                тут типо он получает список колонок , и преобразует их в поля бд
            */
            for (size_t i = 1; i < T::columns.size(); ++i) {
                set_clauses.push_back(fmt::format("{} = ${}", T::columns[i], i));
            }
            

            // update students set (student_id = $1 , person_id = $2 , subject_id =$3 , info = $4  ) where student_id = $5 ; 
            std::string sql = fmt::format("UPDATE {} SET {} WHERE {} = ${}", T::table_name, fmt::join(set_clauses, ", "), T::columns[0], T::columns.size() );

            auto values = entity.get_values_tuple(); // std::tuple 

            std::apply([&sql, &txn ,&id](const auto&... args) {
                txn.exec_params(sql, args... , id);
            }, values);

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
