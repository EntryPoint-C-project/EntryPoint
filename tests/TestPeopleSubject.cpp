#include "../inc/PeopleSubject.hpp"
#include "../inc/People.hpp"
#include "../inc/Subjects.hpp"
#include <pqxx/pqxx>
#include <fmt/core.h>

int main(){
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";
    
    try {
        // Подключение к БД
        pqxx::connection conn(conn_str);

        People test_person1; 
        test_person1.first_name = "test_person1";
        test_person1.last_name = "test_person1";
        test_person1.tg_nick = "bla_bla_bla1";


        // Subjects test_subject1; 
        // test_subject1.subject_id = 1 ; 
        // test_subject1.subject_name = "test_subject";
        

        fmt::print("\n[CREATE] Создание челоека...\n");
        BaseCrud<People>::Create(conn, test_person1);
        fmt::print("\u2713 Запись созданА!!!!\n");

        // fmt::print("\n[CREATE] Создание предмета...\n");
        // BaseCrud<Subjects>::Create(conn, test_subject1);
        // fmt::print("\u2713 Запись созданА!!!!\n");

        fmt::print("\n[CREATE] Создание тестовых записей...\n");
        auto people = BaseCrud<People>::Read(conn);
        int id ; 
        for( auto p : people){
            if(p.first_name == "test_person1" && p.last_name == "test_person1" && p.tg_nick == "bla_bla_bla1"){
                id = p.person_id;   
            }
        }
        PeopleSubject test_people_subject1; 
        test_people_subject1.person_id = id ; 
        test_people_subject1.subject_id = 1 ; 
        


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