#include "Dop_Functions.hpp"

std::vector<Teacher> GetAllTeachersForStudent(pqxx::transaction_base& txn, int student_id) {
    std::vector<Teacher> teachers;
    // мы берем студнета --> возвращаем для него его характеристики --> ищем учителей с такими же характеристикаи --> возвращаем учителей
    std::vector<std::pair<int, int> > student_params = ReadInfoOnPersonId(txn, student_id); // vector <offer_id, subject_id >

    for (auto param  : student_params) { 
        int offer_id = param.first;
        int subject_id = param.second;
        std::string subject_name = ReadSubject(txn, subject_id);
        if (subject_name == "Student") {
            std::tuple< int , int , int > subject_offer = ReadSubjectOffer(txn , offer_id) ; // people_group_id, program_id, course_id
            std::vector<std::pair<int, int> > teacher_info = ReadInfoOnOfferIdNoStudents(txn, offer_id);
            for (auto info : teacher_info) { //person_id , subject_id
                int person_id = info.first;
                std::string subject_name = ReadSubject(txn, info.second);
                std::tuple<std::string , std::string , std::string , int , int  > teacher_info = ReadPerson(txn, person_id);

                if (std::get<0>(teacher_info).empty()) {
                    fmt::print("Teacher not found with ID: {}\n", person_id);
                    continue;
                }

                Teacher teacher;
                teacher.first_name = std::get<0>(teacher_info); 
                teacher.last_name = std::get<1>(teacher_info);

                std::vector<int> role_ids = ReadRoleId(txn, person_id);
                std::vector<std::string> his_roles; 
                for (auto role_id : role_ids) {
                    std::string role_name = ReadRole(txn, role_id);
                    if (role_name.empty()) {
                        fmt::print("Role not found with ID: {}\n", role_id);
                        continue;
                    }
                    his_roles.push_back(role_name);
                }
                teacher.his_roles = his_roles;

                teacher.subject_name = subject_name;
                
                teachers.push_back(teacher);
            }
        }
    }
        
    return teachers;
}

bool CorrectSnils(pqxx::transaction_base& txn, int snils , std::string tg_nick)  {
    try {
        std::string sql =  " SELECt EXISTS("
                           "SELECT 1 FROM people WHERE snils = $1 AND tg_nick = $2"
                           ")";
        pqxx::result res = txn.exec_params(sql, snils, tg_nick);
        return res[0][0].as<bool>();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении {}: {}", snils, e.what()) ;
        throw ;
    }
}

void CreatePersonWithParams(pqxx::transaction_base& txn, Person person) {
    try {
        if (person.first_name.empty() || person.last_name.empty() || person.tg_nick.empty() || person.snils == 0) {
            throw std::invalid_argument("Заполните все поля в Person");
        }

        int person_id = CreatePerson(txn, person.first_name, person.last_name, person.tg_nick, person.access, person.snils);

        int role_id = ReadRoleId(txn, person.role);
        if (role_id != 0) {
            CreatePersonRole(txn, person_id, role_id);
        } else {
            throw std::runtime_error("Role not found: " + person.role);
        }

        int subject_id = IsThereARecordSubject(txn, person.subject_name) ? ReadSubjectId(txn, person.subject_name) : CreateSubject(txn, person.subject_name);

        int program_id = IsThereARecordProgram(txn, person.program_name) ? ReadProgramId(txn, person.program_name) : CreateProgram(txn, person.program_name);

        int course_id = IsThereARecordCourse(txn, person.course_name) ? ReadCourseId(txn, person.course_name) : CreateCourse(txn, person.course_name);

        int people_group_id = IsThereARecordPeopleGroup(txn, person.people_group_name) ? ReadPeopleGroupId(txn, person.people_group_name) : CreatePeopleGroup(txn, person.people_group_name);

        int offer_id = IsThereARecordOffer(txn, people_group_id, program_id, course_id) ? GetOfferId(txn, people_group_id, program_id, course_id) : CreateSubjectOffer(txn, people_group_id, program_id, course_id);

        if (!IsThereARecordTeachingAssigment(txn, person_id, offer_id, subject_id)) {
            CreateTeachingAssigment(txn, person_id, offer_id, subject_id);
        }

    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", person.first_name, e.what());
        throw; 
    }
}


void AssignCompletelyToPeople(pqxx::transaction_base& txn) { // метод для нажатия кнопки ОКТРЫТЬ СОП //! для ТИМОФЕЯ
  try {
    std::string sql = "SELECT  p.person_id "
                  " FROM People p"
                  " JOIN Person_Role pr ON p.person_id = pr.person_id"
                  " JOIN Role r ON pr.role_id = r.role_id"
                  " WHERE r.role_name = 'Student'";
    pqxx::result result = txn.exec(sql);
    for (const auto& row : result) {
        if (row.size() > 0 && row["person_id"].is_not_null()) {
            int person_id = row["person_id"].as<int>();
            if (person_id != 0) { // добавляем проверку
                CreateSOPForm(txn, person_id, "", "", "");
            }
        }
    }
  } catch (const pqxx::sql_error& e) {
        fmt::print("Error: {}\n", e.what());
        throw ;
  }
}

void AssignStatusToAllPeople(pqxx::transaction_base& txn, std::string status) {
    try {
        std::string sql = "SELECT sop_id FROM SOP_Form";
        pqxx::result result = txn.exec(sql);
        for (const auto& row : result) {
            int sop_id = row["sop_id"].as<int>();
            if (sop_id != 0) {
                UpdateStatus(txn, sop_id, status);
            }
        }
    } catch (const pqxx::sql_error& e) {
        fmt::print("Error: {}\n", e.what());
        throw ;
    }
}

