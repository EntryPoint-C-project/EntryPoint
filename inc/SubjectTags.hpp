#pragma once 

#include "BaseCrud.hpp"
#include "IPrimaryKeyEntity.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <fmt/format.h>

class SubjectTags : public ICompositePrimaryKeyEntity {
public:
    int subject_id;
    int tag_id;

    std::pair <int , int> GetPrimaryKey() const { return std::make_pair(subject_id, tag_id); }
    void SetPrimaryKey(std::pair<int, int> ids) { subject_id = ids.first; tag_id = ids.second; }
    static const inline std::string table_name = "subject_tags";
    static const inline std::vector<std::string> columns = {"subject_id", "tag_id"};
    void loadFromRow(const pqxx::row &row) ;
    auto get_values_tuple() const {
        return std::make_tuple(subject_id, tag_id);
    }
    static void Create(pqxx::connection &conn, int subject_id, int tag_id) ;
    static std::vector<SubjectTags> Read(pqxx::connection &conn) ;
    static void Update(pqxx::connection &conn, int subject_id, std::vector<std::string> new_params_for_subject_tags) ;
    static void Delete(pqxx::connection &conn, int subject_id) ;
    friend std::ostream& operator<<(std::ostream& os, const SubjectTags& st) {
        return os << fmt::format( "SubjectTags(Subject: {}, Tag: {})", st.subject_id, st.tag_id );
    }
};

template <>
struct fmt::formatter<SubjectTags> {
    constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }
    template <typename FormatContext>
    auto format(const SubjectTags &st, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "SubjectTags(Subject: {}, Tag: {})", st.subject_id, st.tag_id);
    }
}; 