#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class TeacherSubject : public ICompositePrimaryKeyEntity {
public:
    int teacher_id;
    int subject_id;

    std::pair <int , int> GetPrimaryKey() const { return std::make_pair(teacher_id, subject_id); }
    void SetPrimaryKey(std::pair<int, int> ids) { teacher_id = ids.first; subject_id = ids.second; }

    static const inline std::string table_name = "teacher_subject";
    static const inline std::vector<std::string> columns = {"teacher_id", "subject_id"};

    void loadFromRow(const pqxx::row &row) ; 

    auto get_values_tuple() const {
        return std::make_tuple(teacher_id, subject_id);
    }
    static void Create(pqxx::connection &conn, int teacher_id, int subject_id) ;
    static std::vector<TeacherSubject> Read(pqxx::connection &conn) ;
    static void Update(pqxx::connection &conn, int teacher_id, std::vector<std::string> new_params_for_teacher_subject) ;
    static void Delete(pqxx::connection &conn, int teacher_id) ;
    friend std::ostream& operator<<(std::ostream& os, const TeacherSubject& ts) {
        return os << fmt::format( "TeacherSubject(Teacher: {}, Subject: {})", ts.teacher_id, ts.subject_id );
    }
};  

template <>
struct fmt::formatter<TeacherSubject> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }
    
    auto format(const TeacherSubject& ts, format_context& ctx) const {
        return format_to(ctx.out(), 
            "TeacherSubject(Teacher: {}, Subject: {})",
            ts.teacher_id, ts.subject_id
        );
    }
};