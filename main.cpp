#include "FunctionsForCreateAllTables.hpp"
#include "FunctionsForTable_all_people.hpp"

int main() {
    std::string conn_str =
        "dbname=postgres user=postgres password=spelaya_melon "
        "hostaddr=127.0.0.1 port=5432";
    try {
        pqxx::connection conn(conn_str);
        if (conn.is_open()) {
            std::cout << "Успешное подключение к базе данных: " << conn.dbname()
                      << std::endl;

            std::string filename = "CreateAllTable.sql";

            // CreateAllTables(conn , filename);
            // CheckTableExistence(conn);

            // TODO: сделать так , чтобы при мы передаем сразу параметры ,
            People user;
            user.first_name = "Даня";
            user.last_name = "Калашников";
            user.tg_nick = "@бла бла бля";
            user.subject = "MATH"; 
            user.info = "alfjlf"; 
            user.program_name = "PMI"; 


            // RemovePeopleInTableAllPeople(conn,user.tg_nick); 

            FunctionsForPeople transaction;
            transaction.AddPeopleInAllData(conn, user);

            conn.close();
        } else {
            std::cerr << "Не удалось открыть базу данных." << std::endl;
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
