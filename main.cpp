#include "inc/BaseCrud.hpp" // Подключите ваш заголовочный файл
#include "inc/Students.hpp" // Подключите ваш заголовочный файл

#include <pqxx/pqxx>
#include <iostream>
#include <vector>

int main() {
    // Строка подключения к базе данных
    std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";

    try {
        // Подключение к базе данных
        pqxx::connection conn(conn_str);
        if (conn.is_open()) {
            std::cout << "Успешное подключение к базе данных: " << conn.dbname() << std::endl;
        } else {
            std::cerr << "Не удалось подключиться к базе данных." << std::endl;
            return 1;
        }

        // Тестирование CRUD-операций для Students
        std::cout << "\n=== Тестирование Students ===" << std::endl;

        // Создание записи
        std::cout << "\n[Create] Добавление нового студента..." << std::endl;
        Students::Create(conn, 1, 101, "Информация о студенте 1");
        Students::Create(conn, 2, 102, "Информация о студенте 2");

        // Чтение всех записей
        std::cout << "\n[ReadAll] Чтение всех студентов..." << std::endl;
        std::vector<Students> students = Students::Read(conn);
        for (const auto &student : students) {
            std::cout << "student_id: " << student.student_id
                      << ", person_id: " << student.person_id
                      << ", program_id: " << student.program_id
                      << ", info: " << student.info << std::endl;
        }

        // Чтение одной записи по ID
        std::cout << "\n[ReadById] Чтение студента с ID = 1..." << std::endl;
        Students student = Students::ReadById(conn, 1);
        std::cout << "student_id: " << student.student_id
                  << ", person_id: " << student.person_id
                  << ", program_id: " << student.program_id
                  << ", info: " << student.info << std::endl;

        // Обновление записи
        std::cout << "\n[Update] Обновление информации о студенте с ID = 1..." << std::endl;
        Students::Update(conn,102, 103);

        // Проверка обновления
        student = Students::ReadById(conn, 1);
        std::cout << "Обновленная информация: " << student.info << std::endl;

        // Удаление записи
        std::cout << "\n[Delete] Удаление студента с ID = 2..." << std::endl;
        Students::Delete(conn, 2);

        // Проверка удаления
        std::cout << "[ReadAll] Проверка удаления..." << std::endl;
        students = Students::Read(conn);
        for (const auto &student : students) {
            std::cout << "student_id: " << student.student_id
                      << ", person_id: " << student.person_id
                      << ", program_id: " << student.program_id
                      << ", info: " << student.info << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nТестирование завершено." << std::endl;
    return 0;
}