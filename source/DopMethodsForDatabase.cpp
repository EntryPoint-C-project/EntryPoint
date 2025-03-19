#include <../include/DopMethodsForDatabase.hpp>


static std::vector <int>  GetAllStudentsId(pqxx::connection& conn ) {
    std::vector <int> ids; 
    try {
        pqxx::work txn(conn);
        std::string sql = fmt::format( "SELECT {} FROM {} ",  Students::columns[0], Students::table_name);
        
        pqxx::result res = txn.exec(sql);
        for (const auto& row : res) {
            ids.push_back(row[0].as<int>());
        }
        txn.commit();

        return ids;

    }catch (const std::exception& e) {
        throw std::runtime_error(fmt::format("Delete error: {}", e.what()));
    }
}



static std::vector <int> GetAllPersonId(pqxx::connection &conn){
    std::vector <int> ids; 
    try {
        pqxx::work txn(conn);
        std::string sql = fmt::format( "SELECT {} FROM {} ",  People::columns[0], People::table_name);
        
        pqxx::result res = txn.exec(sql);
        for (const auto& row : res) {
            ids.push_back(row[0].as<int>());
        }
        txn.commit();

        return ids;

    }catch (const std::exception& e) {
        throw std::runtime_error(fmt::format("Delete error: {}", e.what()));
    }
}