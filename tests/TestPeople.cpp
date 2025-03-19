#include "../inc/People.hpp"
#include <pqxx/pqxx>
#include <fmt/core.h>

int main() {
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";

    try {
        pqxx::connection conn(conn_str);

        People test_person1; 
        test_person1.first_name = "test_person";
        test_person1.last_name = "test_person";
        test_person1.tg_nick = "dfkla,fa";

        
        fmt::print("\n[CREATE] Создание тестовых записей...\n");
        BaseCrud<People>::Create(conn, test_person1);
        fmt::print("\u2713 Запись созданА!!!!\n");


        fmt::print("\n[READ] Чтение всех людей:\n");
        auto people = BaseCrud<People>::Read(conn);
        for (const auto& p : people) {
            fmt::print("• {}\n", p);
        }


        fmt::print("\n[UPDATE] Обновление людей...\n");
        People updated_person = test_person1;
        updated_person.first_name = "test_person_updated";
        BaseCrud<People>::Update(conn, test_person1.person_id , updated_person);
        fmt::print("\u2713 Запись обновлена\n");

        fmt::print("\n[READ] Чтение всех людей:\n");
        auto peopless = BaseCrud<People>::Read(conn);
        for (const auto& p : peopless) {
            fmt::print("• {}\n", p);
        }

        fmt::print("\n[DELETE] Удаление людей...\n");
        BaseCrud<People>::Delete(conn, test_person1.person_id);
        fmt::print("\u2713 Запись удалена\n");

    } catch (const std::exception &e) {
        fmt::print("Произошла ошибка: {}\n", e.what());
    }
    return 0 ; 
}


