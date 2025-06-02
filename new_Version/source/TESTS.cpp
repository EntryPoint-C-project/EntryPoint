
#include <TESTS.hpp>



void TEST_PERSON(pqxx::transaction_base& txn  ) {   

    People person1{"John", "Doe", "johвndoe", 0 , 12121};
    People person2{"Danik", "bla " , "dвanik_b" , 0 , 12141} ; 
    People person3{"Egor", "Schcred " , "eвgorik" , 1 , 141432 } ; 
    People person4{"Egor", "PIDOR " , "eвgorikkk" , 0 , 1214213 } ; 


    person1.SetPrimaryKey(CreatePerson(txn, person1.GetFirstName(), person1.GetLastName(), person1.GetTgNick(), person1.GetAccess() , person1.GetSnils() ));
    person2.SetPrimaryKey(CreatePerson(txn, person2.GetFirstName(), person2.GetLastName(), person2.GetTgNick(), person2.GetAccess() , person2.GetSnils()));
    person3.SetPrimaryKey(CreatePerson(txn, person3.GetFirstName(), person3.GetLastName(), person3.GetTgNick(), person3.GetAccess() , person3.GetSnils()));
    person4.SetPrimaryKey(CreatePerson(txn, person4.GetFirstName(), person4.GetLastName(), person4.GetTgNick(), person4.GetAccess() , person4.GetSnils()));
    auto person4_read = ReadPerson(txn, person4.GetPrimaryKey()) ;

    std::cout << std::get<0>(person4_read) << std::endl;
    std::cout << std::get<1>(person4_read) << std::endl;
    std::cout << std::get<2>(person4_read) << std::endl;
    std::cout << std::get<3>(person4_read) << std::endl;
    int i = 22 ; 

    // DeletePerson(txn, i);
}


void TEST_SUBJECT(pqxx::transaction_base& txn  ) {   
    Subject subject{"Mathematics"};
    subject.SetPrimaryKey(CreateSubject(txn, subject.GetSubjectName()));
    std::cout << "SUBject: " << ReadSubject(txn, subject.GetPrimaryKey()) << std::endl;
    UpdateSubject(txn, subject.GetPrimaryKey(), "Physics");
    std::cout << "SUBject: " << ReadSubject(txn, subject.GetPrimaryKey()) << std::endl;
    // DeleteSubject(txn, subject.GetPrimaryKey());


}

void TEST_PROGRAM(pqxx::transaction_base& txn  ) {   
    Program program{"Mathematics"};
    program.SetPrimaryKey(CreateProgram(txn, program.GetProgramName()));
    std::cout << "Program: " << ReadProgram(txn, program.GetPrimaryKey()) << std::endl;
    UpdateProgram(txn, program.GetPrimaryKey(), "Physics");
    std::cout << "Program: " << ReadProgram(txn, program.GetPrimaryKey()) << std::endl;
    // DeleteProgram(txn, program.GetPrimaryKey());
}

void TEST_ROLE(pqxx::transaction_base& txn  ) {   
    Role role{"Mathematics"};
    role.SetPrimaryKey(CreateRole(txn, role.GetRoleName()));
    std::cout << "Role: " << ReadRole(txn, role.GetPrimaryKey()) << std::endl;
    UpdateRole(txn, role.GetPrimaryKey(), "Physics");
    std::cout << "Role: " << ReadRole(txn, role.GetPrimaryKey()) << std::endl;
    // DeleteRole(txn, role.GetPrimaryKey());
}


void TEST_PERSON_ROLE(pqxx::transaction_base& txn  ) {
    Person_Role person_role{1, 1};
    person_role.SetPrimaryKey(CreatePersonRole(txn, person_role.GetPrimaryKey(), person_role.GetRoleId()));
    std::cout << "PersonRole: " ; 
    std::vector<int> person_ids = ReadPersonId(txn, person_role.GetRoleId());
    for (int id : person_ids) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
    std::vector<int> role_ids = ReadRoleId(txn, person_role.GetPrimaryKey());
    for (int id : role_ids) {
        std::cout << id << " ";
    }
    std::cout << std::endl;
    // Update(txn, person_role.GetPrimaryKey(), 2, person_role.GetPrimaryKey(), 2);

    // std::cout << "PersonRole: " ; 
    // person_ids = ReadPersonId(txn, person_role.GetRoleId());
    // for (int id : person_ids) {
    //     std::cout << id << " ";
    // }
    // std::cout << std::endl;
    // role_ids = ReadRoleId(txn, person_role.GetPrimaryKey());
    // for (int id : role_ids) {
    //     std::cout << id << " ";
    // }
    // std::cout << std::endl;

    // DeletePersonRole(txn, person_role.GetPrimaryKey() , person_role.GetRoleId());
}

void TEST_COURSE(pqxx::transaction_base& txn  ) {
    Course course{"1"};
    course.SetPrimaryKey(CreateCourse(txn , course.GetCourceName()));
    std::cout << "Course: " << ReadCourse(txn, course.GetPrimaryKey()) << std::endl;
    UpdateCourse(txn, course.GetPrimaryKey(), "Physics");
    std::cout << "Course: " << ReadCourse(txn, course.GetPrimaryKey()) << std::endl;
    // DeleteCource(txn, course.GetPrimaryKey());
}

void TEST_SOP_FORM(pqxx::transaction_base& txn  ) {
    SOP_Form sop_form{1 , "url", "tg_answer", "url_answer"};
    sop_form.SetPrimaryKey(CreateSOPForm(txn ,sop_form.GetPersonId(), sop_form.GetUrl(), sop_form.GetTgAnswer(), sop_form.GetUrlAnswer()));
    std::tuple < int , std::string , std::string , std::string , std::string > read = ReadSOPForm(txn, sop_form.GetPrimaryKey()) ; 
    {
        auto [id, str1, status, str2, str3] = read;
        std::cout << "id " << id << " url " << str1  << " status " << status <<" tg_answer " << str2 << " url_answer " << str3 << std::endl;    
    }


    // UpdatePersonId(txn, sop_form.GetPrimaryKey(), 2);

    UpdateUrl(txn, sop_form.GetPrimaryKey(), "fack");

    UpdateStatus(txn, sop_form.GetPrimaryKey(), "PASSED");
    UpdateTgAnswer(txn, sop_form.GetPrimaryKey(), "sex");

    UpdateUrlAnswer(txn, sop_form.GetPrimaryKey(), "ah ah ah");
    std::tuple < int , std::string , std::string , std::string , std::string > sop_result = ReadSOPForm(txn, sop_form.GetPrimaryKey()) ; 
    {
        auto [id, str1, status, str2, str3] = sop_result;
        std::cout << "id " << id << " url " << str1  << " status " << status <<" tg_answer " << str2 << " url_answer " << str3 << std::endl;
    }



    // Delete_SOP_Form(txn, sop_form.GetPrimaryKey());
}

void TEST_TEACGING_ASSIGMENTS(pqxx::transaction_base& txn  ) {
    Teaching_Assigment teacing_assigments{1 , 1 ,1 };
    teacing_assigments.SetPrimaryKey(CreateTeachingAssigment(txn , teacing_assigments.GetPersonId(), teacing_assigments.GetOfferId(), teacing_assigments.GetSubjectId()));
    std::tuple < int , int , int > read = ReadTeachingAssigment(txn, teacing_assigments.GetPrimaryKey()) ; 
    auto [id, person_id, offer_id] = read;
    std::cout << "id " << id << " person_id " << person_id << " offer_id " << offer_id << std::endl;
    // Update(txn, teacing_assigments.GetPrimaryKey(), 2, 2, 2);
    // Delete_Teaching_Assigment(txn, teacing_assigments.GetPrimaryKey());
}

void TEST_PERSON_GROUP(pqxx::transaction_base& txn  ) {
    People_Group person_group{"groop" };
    person_group.SetPrimaryKey(CreatePeopleGroup(txn , person_group.GetGroupName()));
    std::string read = ReadPeopleGroup(txn, person_group.GetPrimaryKey()) ; 
    std::cout << "id " << read << std::endl;
    UpdatePeopleGroup(txn, person_group.GetPrimaryKey(), "groop1");
    // Delete_Person_Group(txn, person_group.GetPrimaryKey());
}

 
void TEST_SUBJECT_OFFER(pqxx::transaction_base& txn  ) {
    Subject_Offer subject_offer{1 , 1 , 1 };
    subject_offer.SetPrimaryKey(CreateSubjectOffer(txn , subject_offer.GetGroupId(), subject_offer.GetProgramId(), subject_offer.GetCourseId()));
    std::tuple < int , int , int > read = ReadSubjectOffer(txn, subject_offer.GetPrimaryKey()) ;
    auto [group_id, program_id, course_id] = read;
    std::cout << "group_id " << group_id << " program_id " << program_id << " course_id " << course_id << std::endl;
    // Update(txn, subject_offer.GetPrimaryKey(), 2, 2, 2);
    // Delete_Subject_Offer(txn, subject_offer.GetPrimaryKey());
}

void TEST_GET_ALL_TEACHERS(pqxx::transaction_base& txn) {
    try {
        // ================== 1. Подготовка тестовых данных ==================
        // Очистка старых данных (для чистоты теста)

        // Создаем роли
        int student_role = CreateRole(txn, "Student");
        int teacher_role = CreateRole(txn, "Teacher");
        int practice_role = CreateRole(txn, "Practice");

        // Создаем курсы
        int course1 = CreateCourse(txn, "1");
        int course2 = CreateCourse(txn, "2");

        // Создаем предметы
        int math_subj = CreateSubject(txn, "матан");
        int algebra_subj = CreateSubject(txn, "алгебра");
        int student = CreateSubject(txn, "Student");

        // Создаем программы
        int pmi_prog = CreateProgram(txn, "ПМИ");
        int padii_prog = CreateProgram(txn, "ПАДИИ");

        // Создаем группы
        int group1 = CreatePeopleGroup(txn, "Группа ПМИ-1");
        int group2 = CreatePeopleGroup(txn, "Группа ПАДИИ-2");

        // ================== 2. Создаем пользователей ==================
        // Создаем 1 студента
        int student_1 = CreatePerson(txn, "Иван", "Иванов", "ivanov", 0 , 12132);
        CreatePersonRole(txn, student_1, student_role);

        int student_2 = CreatePerson(txn, "Вася", "Пупкин", "сися666", 0 , 21412);
        CreatePersonRole(txn, student_2, student_role);

        // Создаем 3 преподавателей
        int teacher1 = CreatePerson(txn, "Петр", "Петров", "petrov", 1 , 5943);
        CreatePersonRole(txn, teacher1, teacher_role);
        
        int teacher2 = CreatePerson(txn, "Сергей", "Сергеев", "sergeev", 1 , 662662);
        CreatePersonRole(txn, teacher2, teacher_role);
        
        int teacher3 = CreatePerson(txn, "Анна", "Сидорова", "sidorova", 1 , 93993);
        CreatePersonRole(txn, teacher3, teacher_role);

        // Создаем 2 практиков
        int practic1 = CreatePerson(txn, "Дмитрий", "Практиков", "practic1", 1 , 32323);
        CreatePersonRole(txn, practic1, practice_role);
        
        int practic2 = CreatePerson(txn, "Ольга", "Практикова", "practic2", 1 , 849494);
        CreatePersonRole(txn, practic2, practice_role);

        // ================== 3. Создаем учебные предложения ==================
        // Предложение 1: ПМИ, курс 1, группа 1
        int offer1 = CreateSubjectOffer(txn, group1, pmi_prog, course1);
        
        // Предложение 2: ПАДИИ, курс 2, группа 2
        int offer2 = CreateSubjectOffer(txn, group2, padii_prog, course2);

        // ================== 4. Назначаем преподавателей ==================
        // Для offer1 назначаем всех преподавателей и практиков на матан
        // CreateTeachingAssigment(txn ,student_1 , offer2, student);


        
        CreateTeachingAssigment(txn, teacher1, offer1, math_subj);
        CreateTeachingAssigment(txn, teacher2, offer1, math_subj);
        CreateTeachingAssigment(txn, teacher3, offer1, math_subj);
        CreateTeachingAssigment(txn, practic1, offer1, math_subj);
        CreateTeachingAssigment(txn, practic2, offer1, math_subj);

        // Для offer2 назначаем некоторых преподавателей на алгебру
        CreateTeachingAssigment(txn, teacher1, offer2, algebra_subj);
        CreateTeachingAssigment(txn, practic1, offer2, algebra_subj);

        // ================== 5. Назначаем студента на offer1 ==================
        CreateTeachingAssigment(txn, student_1, offer1, student);

        CreateTeachingAssigment(txn, student_2, offer2, student);

        // ================== 6. Тестируем функцию ==================
        fmt::print("=== Тестируем для student_1 = {} ===\n", student_1);


        auto teachers_1 = GetAllTeachersForStudent(txn, student_1);

        auto teachers_2 = GetAllTeachersForStudent(txn, student_2);


        // ================== 7. Проверяем результаты ==================
        fmt::print("Найдено учителей: {}\n", teachers_1.size());
        
        // Должно быть 5 учителей (3 Teacher + 2 Practice) для offer1
        if(teachers_1.size() != 5) {
            fmt::print("Ошибка: ожидалось 5 учителей, получено {}\n", teachers_1.size());
            fmt::print("Проверьте:\n");
            fmt::print("1. Назначен ли студент на правильный offer\n");
            fmt::print("2. Назначены ли преподаватели на тот же offer\n");
            fmt::print("3. Корректно ли работает функция GetAllTeachers_1ForStudent\n");
        } else {
            fmt::print("Тест пройден успешно!\n");
            
            // Дополнительная проверка данных
            fmt::print("Список учителей:\n");
            for(const auto& t : teachers_1) {
                fmt::print("- {} {} ({}), предмет: {}\n", 
                    t.first_name, t.last_name, 
                    fmt::join(t.his_roles, ", "), 
                    t.subject_name);
            }
        }

        fmt::print("Найдено учителей: {}\n", teachers_2.size());
        
        // Должно быть 5 учителей (3 Teacher + 2 Practice) для offer1
        if(teachers_2.size() != 2) {
            fmt::print("Ошибка: ожидалось 5 учителей, получено {}\n", teachers_2.size());
            fmt::print("Проверьте:\n");
            fmt::print("1. Назначен ли студент на правильный offer\n");
            fmt::print("2. Назначены ли преподаватели на тот же offer\n");
            fmt::print("3. Корректно ли работает функция GetAllTeachers_1ForStuden2\n");
        } else {
            fmt::print("Тест пройден успешно!\n");
            
            // Дополнительная проверка данных
            fmt::print("Список учителей:\n");
            for(const auto& t : teachers_2) {
                fmt::print("- {} {} ({}), предмет: {}\n", 
                    t.first_name, t.last_name, 
                    fmt::join(t.his_roles, ", "), 
                    t.subject_name);
            }
        }

        std::vector <int> student_ids = ReadSubjectId(txn);
        for ( auto id : student_ids) {
            fmt::print("student_id: {}\n", id);
        }



    } catch (const std::exception& e) {
        fmt::print("Ошибка в тесте: {}\n", e.what());
        throw;
    }
}