#include "../inc/CategoryTags.hpp"
#include "../inc/PeopleSubject.hpp"
#include "../inc/People.hpp"
#include "../inc/Subjects.hpp"
#include "../inc/Roles.hpp"
#include "../inc/Programs.hpp"
#include "../inc/Students.hpp"
#include "../inc/Categories.hpp"
#include "../inc/TeacherSubject.hpp"
#include "../inc/Tags.hpp"
#include <pqxx/pqxx>
#include <fmt/core.h>

void AddPeople( pqxx::connection &conn  ) {
    People p1 ; 
    p1.first_name = "Danik" ;
    p1.last_name = "Kalasnikov" ; 
    p1.tg_nick = "@spelaya_melon" ; 


    People p2 ; 
    p2.first_name = "Egor" ; 
    p2.last_name = "Lukavenko" ; 
    p2.tg_nick = "people2" ; 

    
    People p3 ; 
    p3.first_name = "Bad" ; 
    p3.last_name = "People" ; 
    p3.tg_nick = "people3" ; 

    People p4 ; 
    p4.first_name = "Sergey" ; 
    p4.last_name = "Kopel" ; 
    p4.tg_nick = "@burunduk" ; 

    People p5 ; 
    p5.first_name = "Misha" ; 
    p5.last_name = "Antipov" ; 
    p5.tg_nick = "@ochev" ; 

    People p6 ; 
    p6.first_name = "Aleksander" ; 
    p6.last_name = "Kchabrov" ; 
    p6.tg_nick = "@math" ; 
        
    try {
        BaseCrud <People>::Create (conn , p1);
        fmt::print("{} , успешно добавлен\n" , p1.first_name); 
        BaseCrud <People>::Create (conn , p2);
        fmt::print("{} , успешно добавлен\n" , p2.first_name);
        try {
            BaseCrud <People>::Create (conn , p3); // <-- error 
        } catch (const std::exception &e){
            throw std::runtime_error(fmt::format("произошла ошибка : {}", e.what()));
        }
        BaseCrud <People>::Create (conn , p4);
        fmt::print("{} , успешно добавлен\n" , p4.first_name); 
        BaseCrud <People>::Create (conn , p5);
        fmt::print("{} , успешно добавлен \n" , p5.first_name); 
        BaseCrud <People>::Create (conn , p6);
        fmt::print("{} , успешно добавлен \n" , p6.first_name); 
    } catch (const std::exception & e){
        throw std::runtime_error(fmt::format("произошла ошибка : {}", e.what()));
    }
}

void AddSubjects( pqxx::connection &conn  ) {
    Subjects s1 ; 
    s1.subject_name = "Math"; 

    Subjects s2 ; 
    s2.subject_name = "Algebra"; 

    Subjects s3 ; 
    s3.subject_name = "Algosy"; 
    try {
        BaseCrud <Subjects>::Create(conn , s1); 
        fmt::print("{} , успешно добавлен\n" , s1.subject_name); 
        BaseCrud <Subjects>::Create(conn , s2); 
        fmt::print("{} , успешно добавлен\n" , s2.subject_name); 
        BaseCrud <Subjects>::Create(conn , s3); 
        fmt::print("{} , успешно добавлен\n" , s3.subject_name); 

    }catch (const std::exception &e){
        fmt::print("Произошла ошибка при добавлеи новго предмента : {}" , e.what() ) ; 
    }

}


void AddLinkBetweenSubjectsAndPeople(pqxx::connection &conn){
    PeopleSubject l1 ; 
    l1.person_id = 1; 
    l1.subject_id= 2; 

    l1.person_id = 1; 
    l1.subject_id= 3; 

    l1.person_id = 1; 
    l1.subject_id= 1; 

    PeopleSubject l2 ; 
    l2.person_id = 2 ; 
    l2.subject_id= 2  ; 

    BaseCrud<PeopleSubject>::Create(conn , l1);   
    fmt::print("связь успешно добавлен : {} + {}\n" , l1.person_id , l1.subject_id);
    BaseCrud<PeopleSubject>::Create(conn , l2);    
    fmt::print("связь успешно добавлен : {} + {}\n" , l2.person_id , l2.subject_id);
    
    fmt::print("инфомация успешно добавлен\n"); 
}


void AddLinkBetweenSubjectsAndTeacher(pqxx::connection &conn){
    TeacherSubject l1 ; 
    l1.teacher_id = 4 ; 
    l1.subject_id = 3 ; 

    TeacherSubject l2 ; 
    l2.teacher_id = 5 ; 
    l2.subject_id = 2 ; 

    TeacherSubject l3 ; 
    l3.teacher_id = 6; 
    l3.subject_id = 1 ; 

    try {
        BaseCrud<TeacherSubject>::Create(conn , l1); 
        fmt::print("связь успешно добавлен : {} + {}\n" , l1.teacher_id , l1.subject_id);
        BaseCrud<TeacherSubject>::Create(conn , l2); 
        fmt::print("связь успешно добавлен : {} + {}\n" , l2.teacher_id , l2.subject_id);
        BaseCrud<TeacherSubject>::Create(conn , l3); 
        fmt::print("связь успешно добавлен : {} + {}\n" , l3.teacher_id , l3.subject_id);

    }catch (const std::exception &e){
        fmt::print("произошла ошибка : {}" , e.what()) ; 
    }

}


void ReadPeople(pqxx::connection &conn, int id ){
    try {
        std::vector <People> people = BaseCrud<People>::Read(conn , id); 
        for (const auto& p : people) {
            fmt::print("• {}\n", p);
        }

    }catch (const std::exception &e){
        fmt::print("произошла ошибка : {}" , e.what()) ;
    }
}





//! перед тем как начать тестировтаь все это , необходимо удалить все таблицы 
int main(){
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";
    try {
        pqxx::connection conn(conn_str); 
        AddPeople(conn); 
        AddSubjects(conn); 
        AddLinkBetweenSubjectsAndPeople(conn);
        AddLinkBetweenSubjectsAndTeacher(conn); 

        ReadPeople(conn , 1);
        ReadPeople(conn , 2);
        ReadPeople(conn , 3);
        ReadPeople(conn , 4);
        ReadPeople(conn , 5);
        ReadPeople(conn , 6);


        
    } catch (const std::exception & e){
        fmt::print("Произошла ошибка при работе теста  : {}\n" , e.what() ) ; 
    }

}