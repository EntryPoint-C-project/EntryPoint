#include "inc/Students.hpp"
#include <pqxx/pqxx>
#include <fmt/core.h>

int main() {
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";

    try {
        pqxx::connection conn(conn_str);

        Students test_student1{
            .person_id = 23 ,
            .program_id = 23 , 
            .info = "бла бла бла"
        };
        
        fmt::print("\n[CREATE] Создание тестовых записей...\n");
        BaseCrud<Students>::Create(conn, test_student1);
        fmt::print("\u2713 Запись созданА!!!!\n");


        fmt::print("\n[READ] Чтение всех студентов:\n");
        auto students = BaseCrud<Students>::Read(conn);
        for (const auto& s : students) {
            fmt::print("• {}\n", s);
        }


        fmt::print("\n[UPDATE] Обновление студента...\n");
        Students updated_student = test_student1;
        updated_student.program_id = 300;
        BaseCrud<Students>::Update(conn,1 , updated_student);
        fmt::print("\u2713 Запись обновлена\n");


        fmt::print("\n[DELETE] Удаление студента...\n");
        BaseCrud<Students>::Delete(conn, test_student1.student_id);
        fmt::print("\u2713 Запись удалена\n");


        fmt::print("\n[FINAL READ] Текущие студенты:\n");
        auto studentss = BaseCrud<Students>::Read(conn);
        for (const auto& s : studentss) {
            fmt::print("• {}\n", s);
        }

    } catch (const std::exception& e) {
        fmt::print(stderr, "\n!!! ОШИБКА: {}\n", e.what());
        return 1;
    }

    fmt::print("\n=== ТЕСТЫ УСПЕШНО ЗАВЕРШЕНЫ ===\n");
    return 0;
}