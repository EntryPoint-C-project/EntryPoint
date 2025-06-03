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

                Teacher teacher;
                teacher.first_name = std::get<0>(teacher_info); 
                teacher.last_name = std::get<1>(teacher_info);

                std::vector<int> role_ids = ReadRoleId(txn, person_id);
                std::vector<std::string> his_roles; 
                for (auto role_id : role_ids) {
                    his_roles.push_back(ReadRole(txn, role_id));
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

void CreatePersonWithParams(pqxx::transaction_base& txn ,  Person person) {
    try {
        int person_id = CreatePerson(txn , person.first_name , person.last_name , person.tg_nick , person.access , person.snils);
        if ( person.role == "student"){
            CreatePersonRole(txn , person_id , "student");
        }else if (person.role == "lector"){
            CreatePersonRole(txn , person_id , "lector");
        }else if (person.role == "practitioner"){
            CreatePersonRole(txn , person_id , "practitioner");
        }


        int subject_id
        if (IsThereARecordSubject(txn , person.subject_name)) {
            subject_id = ReadSubjectId(txn , person.subject_name);
        } else {
            int subject_id = CreateSubject(txn , person.subject_name);
        }

        int program_id;
        if ( IsThereARecordProgram(txn , person.program_name)) {
            program_id = ReadProgramId(txn , person.program_name);
        } else {
            program_id = CreateProgram(txn , person.program_name);
        }

        int course_id; 
        if (IsThereARecordCourse(txn , person.course_name)) {
            course_id = ReadCourseId(txn , person.course_name);
        } else {
            course_id = CreateCourse(txn , person.course_name);
        }

        int people_group_id ;
        if (IsThereARecordPeopleGroup(txn , person.people_group_name)) {
            people_group_id = ReadPeopleGroupId(txn , person.people_group_name);
        } else {
            people_group_id = CreatePeopleGroup(txn , person.people_group_name);
        }

        int offer_id ; 
        if (IsThereARecordOffer(txn , people_group_id, program_id, course_id)) {
            offer_id = GetOfferId(txn , people_group_id, program_id, course_id);
        } else {
            offer_id = CreateSubjectOffer(txn , people_group_id, program_id, course_id);
        }

        if (IsThereARecordTeachingAssigment(txn , person_id , offer_id , subject_id)) {
            int teaching_assigment_id = GetTeachingAssigmentId(txn , person_id , offer_id , subject_id);
        } else {
            int teaching_assigment_id = CreateTeachingAssigment(txn , person_id , offer_id , subject_id);
        }


    } catch (const std::exception &e) {
        fmt::print("Ошибка при создании {}: {}", person.first_name, e.what()) ;

    }   
}

void AssignCompletelyToPeople(pqxx::transaction_base& txn) {
  try {
    std::string sql = "SELECT p.*"
                      " FROM People p"
                      " JOIN Person_Role pr ON p.id = pr.person_id"
                      " WHERE pr.role = 'Student' AND p.status != 'Не начал проходить СОП'";
    pqxx::result result = txn.exec(sql);
    for (const auto& row : result) {

      std::string update_sql = "UPDATE People SET status = 'Не начал проходить СОП' WHERE id = " + std::to_string(row["id"].as<int>());
      txn.exec(update_sql);
    }
  } catch (const pqxx::sql_error& e) {
    // обработка ошибки
  }
}