#include "Program.hpp"

int CreateProgram(pqxx::transaction_base &txn, const std::string &program_name) {
    if (program_name.empty()) {
        fmt::print("Заполните все поля\n");
        throw std::invalid_argument("Заполните все поля");
    }
    try {
        std::string sql = "INSERT INTO Program (program_name) VALUES ($1)  ReTURNING program_id";

        pqxx::result res = txn.exec_params(sql, program_name);
        int program_id;
        if (!res.empty()) {
            program_id = res[0]["program_id"].as<int>();
        } else {
            fmt::print("Запись уже существует с указанным program_name\n");
        }
        // txn.commit() ;
        return program_id;

        // txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", program_name, e.what());
        throw;
    }
}

std::string ReadProgram(pqxx::transaction_base &txn, int program_id) {
    try {
        std::string sql = "SELECT program_name FROM Program WHERE program_id = $1";
        pqxx::result res = txn.exec_params(sql, program_id);
        // txn.commit();
        std::string program_name = res[0]["program_name"].as<std::string>();
        return program_name;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", program_id, e.what());
        throw;
    }
}

void UpdateProgram(pqxx::transaction_base &txn, int program_id, std::string new_program_name) {
    try {
        std::string sql = "UPDATE Program SET program_name = $1 WHERE program_id = $2";
        txn.exec_params(sql, new_program_name, program_id);
        // txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при обновлении {}: {}", program_id, e.what());
        throw;
    }
}

void DeleteProgram(pqxx::transaction_base &txn, int program_id) {
    try {
        std::string sql = "DELETE FROM Program WHERE program_id = $1";
        txn.exec_params(sql, program_id);
        // txn.commit();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при удалении {}: {}", program_id, e.what());
        throw;
    }
}

bool IsThereARecordProgram(pqxx::transaction_base &txn, std::string program_name) {
    try {
        std::string sql
            = " SELECt EXISTS("
              "SELECT 1 FROM Program WHERE program_name = $1"
              ")";
        pqxx::result res = txn.exec_params(sql, program_name);
        return res[0][0].as<bool>();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", program_name, e.what());
        throw;
    }
}

int ReadProgramId(pqxx::transaction_base &txn, std::string program_name) {
    try {
        std::string sql = "SELECT program_id FROM Program WHERE program_name = $1";
        pqxx::result res = txn.exec_params(sql, program_name);
        // txn.commit();
        int program_id = res[0]["program_id"].as<int>();
        return program_id;
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", program_name, e.what());
        throw;
    }
}