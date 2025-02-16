#include "FunctionsForTable_all_people.hpp"
#include <iostream>
#include <pqxx/pqxx>
#include <stdexcept>

void RemovePeopleInTableAllPeople(
    pqxx::connection &conn,
    std::string &tg_nick
) {
    try {
        pqxx::work txn(conn);
        std::string sql = "DELETE FROM People WHERE tg_nick = $1; ";

        txn.exec_params(sql, tg_nick);
        txn.commit();
        std::cout << std::string("Пользователь под ником: ") + tg_nick +
                         std::string(" был успешно удален из базы данных ( ")
                  << std::endl;
    } catch (const std::exception &e) {
        std::cerr << std::string("Во время удаления пользователя под ником:  "
                     ) + tg_nick +
                         std::string(" произошла ошибка:  ")
                  << e.what() << std::endl;
    }
}

void UpdateTelegramNick(
    pqxx::connection &conn,
    const std::string &old_nick,
    const std::string &new_nick
) {
    try {
        pqxx::work txn(conn);
        std::string sql = "UPDATE People SET tg_nick = $1 WHERE tg_nick = $2;";

        txn.exec_params(sql, old_nick, new_nick);
        txn.commit();
        std::cout << std::string("Ник был успешно заменен с ") + old_nick +
                         std::string(" -> ") + new_nick + std::string("!")
                  << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Произошла ошибка при изменении ника: " << e.what()
                  << std::endl;
    }
}
