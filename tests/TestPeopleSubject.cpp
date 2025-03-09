#include "../inc/PeopleSubject.hpp"
#include <pqxx/pqxx>
#include <fmt/core.h>

int main(){
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";
    
    try {
        // Подключение к БД
        pqxx::connection conn(conn_str);

        PeopleSubject test_people_subject1; 
        test_people_subject1.person_id = 23 ; 
        test_people_subject1.subject_id = 23 ;  

        fmt::print("\n[CREATE] Создание тестовых записей...\n");
        BaseCrud<PeopleSubject>::Create(conn, test_people_subject1);
        fmt::print("\u2713 Запись созданА!!!!\n");

        fmt::print("\n[READ] Чтение всех записей:\n");
        auto people_subjects = BaseCrud<PeopleSubject>::Read(conn);

        for (const auto& p : people_subjects) {
            fmt::print("• {}\n", p);
        }        


        fmt::print("\n[UPDATE] Обновление записей...\n");
        PeopleSubject updated_people_subject = test_people_subject1;
        updated_people_subject.subject_id = 300;
        BaseCrud<PeopleSubject>::Update(conn, test_people_subject1.person_id , updated_people_subject);
        fmt::print("\u2713 Запись обновлена\n");

        fmt::print("\n[READ] Чтение всех записей:\n");
        auto people_subjectss = BaseCrud<PeopleSubject>::Read(conn);
        for (const auto& p : people_subjectss) {
            fmt::print("• {}\n", p);
        }

        fmt::print("\n[DELETE] Удаление записей...\n");
        BaseCrud<PeopleSubject>::Delete(conn, test_people_subject1.person_id);
        fmt::print("\u2713 Запись удалена\n");

        fmt::print("\n[READ] Чтение всех записей:\n");
        auto people_subjectsss = BaseCrud<PeopleSubject>::Read(conn);
        for (const auto& p : people_subjectsss) {
            fmt::print("• {}\n", p);
        }


    } catch (const std::exception &e) {
        fmt::print("✗ Ошибка подключения к БД: {}\n", e.what());
    }
}