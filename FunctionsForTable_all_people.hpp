#ifndef FUNCTIONS_FOR_TABLE_ALL_PEOPLE_
#define FUNCTIONS_FOR_TABLE_ALL_PEOPLE_
#include <fstream>
#include <iostream>
#include <pqxx/pqxx>
#include <sstream>
#include <string>

class People {
public:
    std::string first_name;
    std::string last_name;
    std::string tg_nick;
    std::string program_name ; 
    std::string info ; 
    std::string  subject; 
    int role_id; 
    int  subject_id ;
    int student_id;
};

class FunctionsForPeople {
public:
    void SetPersonRole(pqxx::work &txn, pqxx::connection &conn, int &person_id){
        pqxx::result res_for_get_role_id= txn.exec(
            "SELECT role_id FROM Roles WHERE role_name = " +
            conn.quote("admin")
        );
        if (res_for_get_role_id.empty()) {
            throw std::runtime_error(
                "Не найдена роль 'admin' в таблице Roles."
            );
        }
        int role_id = res_for_get_role_id[0][0].as<int>();

        std::string sql_insert_person_role =
            "INSERT INTO Person_Role (person_id, role_id) VALUES ($1, $2) "
            "ON CONFLICT DO NOTHING;";

        txn.exec_params(sql_insert_person_role, person_id, role_id);
    }

    void AddPeopleInAllData(pqxx::connection &conn, People user)  {
        try {
            pqxx::work txn(conn);

            std::string sql_for_insert_people =
                "INSERT INTO People (first_name, last_name, tg_nick) VALUES "
                "($1, $2, $3) "
                "RETURNING person_id;";

            pqxx::result res_for_get_person_id{txn.exec_params(
                sql_for_insert_people, user.first_name, user.last_name, user.tg_nick
            )};

            if (res_for_get_person_id.empty()) {
                throw std::runtime_error(
                    "Не удалось получить person_id после вставки/обновления "
                    "People"
                );
            }
            int person_id = res_for_get_person_id[0][0].as<int>();
            // добавление роли 
            if (user.role_id == 1){
                SetPersonRole(txn , conn , person_id); 
            }

            //добавление в студениты 
            std::string sql_get_program_id = "SELECT program_id FROM Programs WHERE program_name = " + conn.quote(user.program_name) ; 
            pqxx::result res_sql_get_program_id = txn.exec(sql_get_program_id);

            if (res_sql_get_program_id.empty()){
                throw std::runtime_error(
                    "Не найдена программа "+ user.program_name + " в таблице Programs.\n"
            ); 
            }
            int program_id = res_sql_get_program_id[0][0].as<int>();
            std::string sql_insert_program_id = "INSERT INTO Students (person_id, program_id, info) VALUES ($1, $2 , $3) "
                "ON CONFLICT DO NOTHING;";

            txn.exec_params(sql_insert_program_id, person_id, program_id , user.info);

            //Добавление в Feedback 
            // TODO: сгенирировать табличку из всех учителей 
            std::string sql_get_subject_id = "SELECT subject_id FROM Subjects WHERE subject_name  = " + conn.quote(user.subject) ; 
            pqxx::result res_sql_get_subject_id = txn.exec(sql_get_subject_id);

            if (res_sql_get_subject_id.empty()){
                throw std::runtime_error(
                    "Не найдена программа "+ user.subject + " в таблице Subjects.\n"
            ); 
            }
            int subject_id = res_sql_get_subject_id[0][0].as<int>();
            std::string sql_insert_subject_id = "INSERT INTO Feedback (teacher_id , subject_id , name ) VALUES ($1, $2 , $3) "
                "ON CONFLICT DO NOTHING;";

            txn.exec_params(sql_insert_subject_id, person_id, subject_id , user.subject);

            txn.commit();
            std::cout
                << "Запись в таблице Person_Role для пользователя с ником - "
                << user.tg_nick << " успешно добавлена." << std::endl;

        } catch (const std::exception &e) {
            std::cout << std::string("Произошла ошибка с добавлением ") +
                             user.tg_nick + std::string("Навзание ошибки :")
                      << e.what() << std::endl;
        }
    }
};

void RemovePeopleInTableAllPeople(pqxx::connection &conn, std::string &tg_nick);

// это нужно в том случае , когда человек поменял телеграм и хочет зарегаться
// еще раз
void UpdateTelegramNick(
    pqxx::connection &conn,
    const std::string &old_nick,
    const std::string &new_nick
);

#endif  // FUNCTIONS_FOR_TABLE_ALL_PEOPLE_
