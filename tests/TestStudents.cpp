#include "../include/Students.hpp"
#include <pqxx/pqxx>
#include <fmt/core.h>

int main() {
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";

    try {
        pqxx::connection conn(conn_str);

        Students test_student1; 
        test_student1.person_id = 23 ; 
        test_student1.program_id = 1 ;  
        test_student1.info = "бла "; 

        
        fmt::print("\n[CREATE] Создание тестовых записей...\n");
        BaseCrud<Students>::Create(conn, test_student1);
        fmt::print("\u2713 Запись созданА!!!!\n");


        fmt::print("\n[READ] Чтение всех студентов:\n");
        auto students = BaseCrud<Students>::Read(conn, test_student1.student_id);
        fmt::print("• {}\n", students);


        fmt::print("\n[UPDATE] Обновление студента...\n");
        Students updated_student = test_student1;
        updated_student.program_id = 300;
        BaseCrud<Students>::Update(conn, test_student1.student_id , updated_student);
        fmt::print("\u2713 Запись обновлена\n");


        fmt::print("\n[FINAL READ] Текущие студенты:\n");
        auto studentsss = BaseCrud<Students>::Read(conn , test_student1.student_id);
        fmt::print("• {}\n", studentsss);


        fmt::print("\n[DELETE] Удаление студента...\n");
        BaseCrud<Students>::Delete(conn, test_student1.student_id);
        fmt::print("\u2713 Запись удалена\n");


        fmt::print("\n[FINAL READ] Текущие студенты:\n");
        auto studentss = BaseCrud<Students>::Read(conn , test_student1.student_id);
        fmt::print("• {}\n", studentss);

    } catch (const std::exception& e) {
        fmt::print(stderr, "\n!!! ОШИБКА: {}\n", e.what());
        return 1;
    }

    fmt::print("\n=== ТЕСТЫ УСПЕШНО ЗАВЕРШЕНЫ ===\n");
    return 0;
}