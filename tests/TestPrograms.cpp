#include "../inc/Programs.hpp"
#include <pqxx/pqxx>
#include <fmt/core.h>

int main() {
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";

    try {
        pqxx::connection conn(conn_str);

        Programs test_program1; 
        test_program1.program_name = "test_program";

        
        fmt::print("\n[CREATE] Создание тестовых записей...\n");
        BaseCrud<Programs>::Create(conn, test_program1);
        fmt::print("\u2713 Запись созданА!!!!\n");


        fmt::print("\n[READ] Чтение всех программ:\n");
        auto programs = BaseCrud<Programs>::Read(conn);
        for (const auto& p : programs) {
            fmt::print("• {}\n", p);
        }


        fmt::print("\n[UPDATE] Обновление программ...\n");
        Programs updated_program = test_program1;
        updated_program.program_name = "test_program_updated";
        BaseCrud<Programs>::Update(conn, test_program1.program_id , updated_program);
        fmt::print("\u2713 Запись обновлена\n");

        fmt::print("\n[READ] Чтение всех программ:\n");
        auto programss = BaseCrud<Programs>::Read(conn);
        for (const auto& p : programss) {
            fmt::print("• {}\n", p);
        }

        fmt::print("\n[DELETE] Удаление программ...\n");
        BaseCrud<Programs>::Delete(conn, test_program1.program_id);
        fmt::print("\u2713 Запись удалена\n");

    } catch (const std::exception &e) {
        fmt::print("Произошла ошибка: {}\n", e.what());
    }
    return 0 ; 
}