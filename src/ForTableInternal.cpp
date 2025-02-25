
#include "ForTableInternal.hpp"

std::string ReturnSqlRequesInFile( std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть  файл: " + filename+ "\n");
    }
    std::stringstream buffer;
    buffer << file.rdbuf(); 
    return buffer.str();
}


static bool VerificationAdmin(pqxx::connection &conn , const int person_id){
    PersonRole::ReadInformationAboutPersonId(conn , person_id); 
    std::vector <int> vector_for_role_id = PersonRole::ReadRolesByPersonId(conn , person_id); 
    for (const auto role_id : vector_for_role_id){
        if (Roles::Read(conn , role_id) == "admin") {
            return true; 
        }
    }
    return false; 
}