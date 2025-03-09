#include "../inc/Roles.hpp"
#include <pqxx/pqxx>
#include <fmt/core.h>

int main() {
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";

    try {
        pqxx::connection conn(conn_str);

        Roles test_role1; 
        test_role1.role_name = "test_role";

        
        fmt::print("\n[CREATE] Создание тестовых записей...\n");
        BaseCrud<Roles>::Create(conn, test_role1);
        fmt::print("\u2713 Запись созданА!!!!\n");


        fmt::print("\n[READ] Чтение всех ролей:\n");
        auto roles = BaseCrud<Roles>::Read(conn);
        for (const auto& r : roles) {
            fmt::print("• {}\n", r);
        }

        

        fmt::print("\n[UPDATE] Обновление ролей...\n");
        Roles updated_role = test_role1;
        updated_role.role_name = "test_role_updated";
        BaseCrud<Roles>::Update(conn, test_role1.role_id , updated_role);
        fmt::print("\u2713 Запись обновлена\n");

        fmt::print("\n[READ] Чтение всех ролей:\n");
        auto roless = BaseCrud<Roles>::Read(conn);
        for (const auto& r : roless) {
            fmt::print("• {}\n", r);
        }




        fmt::print("\n[DELETE] Удаление ролей...\n");
        BaseCrud<Roles>::Delete(conn, test_role1.role_id);
        fmt::print("\u2713 Запись удалена\n");

    } catch (const std::exception &e) {
        fmt::print("Произошла ошибка: {}\n", e.what());
    }
    return 0;
}