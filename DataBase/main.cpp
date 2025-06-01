// #include <iostream> 
// #include <pqxx/pqxx>
// #include <fmt/core.h>
// #include "../include/InteractionsWithTables.hpp"

// #include "../include/TESTS.hpp"

// int main() {
//     // const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";
//     const std::string conn_str = "dbname=ep_db user=danik password=60992425 hostaddr=127.0.0.1 port=5432";

//     try {
//         pqxx::connection conn(conn_str);
//         // pqxx::work txn(conn); 
//         if (!conn.is_open()) {
//             throw std::runtime_error("Connection failed");
//         }
//         fmt::print("✓ Подключено к: {}\n", conn.dbname());
//         pqxx::work txn(conn);


//         DeleteAllTable(txn);
//         CreateAllTable(txn); 
//         TEST_PERSON(txn);
//         TEST_SUBJECT(txn);
//         TEST_PROGRAM(txn);
//         TEST_ROLE(txn);
//         TEST_PERSON_GROUP(txn) ; 

//         TEST_PERSON_ROLE(txn);
//         TEST_COURSE(txn);
//         TEST_SUBJECT_OFFER(txn);
//         TEST_TEACGING_ASSIGMENTS(txn);

//         TEST_SOP_FORM(txn);

//         TEST_GET_ALL_TEACHERS(txn);

//         txn.commit();





    
//     }catch( const std::exception &e){
//         fmt::print("произошла ошибка : {}\n", e.what());
//     }

//     return 0;
// }