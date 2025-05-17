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
                std::tuple<std::string , std::string , std::string , int > teacher_info = ReadPerson(txn, person_id);

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
