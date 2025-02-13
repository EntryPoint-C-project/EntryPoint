#include <tgbot/tgbot.h>
#include "BotToken.hpp"
#include <map>
#include "User.hpp"
#include "Student.hpp"
#include "OfficeStaff.hpp"
#include <memory>
#include <mutex>

void student_call_back_query(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query, int64_t chat_id, std::map<int64_t, std::shared_ptr<mtd::User>> &users) {
    if (query->data == "student_buttons") {
        bot.getApi().sendMessage(chat_id, "fsfsdf", 0, 0, users[chat_id]->get_inline_keyboard());
    }
    if (query->data == "student_time_table") {
        bot.getApi().sendMessage(chat_id, "Ссылка на расписание", 0, 0, users[chat_id]->get_inline_keyboard());
    }
    else if (query->data == "student_declaration") {
        bot.getApi().sendMessage(chat_id, "Актуальные объявления", 0, 0, users[chat_id]->get_inline_keyboard());
    }
    else if (query->data == "student_connect_with_teacher") {
        bot.getApi().sendMessage(chat_id, "Списочек с контактами преподавателя", 0, 0, users[chat_id]->get_inline_keyboard());
    }
    else if (query->data == "student_help") {
        bot.getApi().sendMessage(chat_id, "Помощь", 0, 0, users[chat_id]->get_inline_keyboard());
    }
    else if (query->data == "student_back") {
        bot.getApi().sendMessage(chat_id, "Меню", 0, 0, users[chat_id]->get_menu());
        return;
    }

    else if (query->data == "student_information") {
        bot.getApi().sendMessage(chat_id, "Какая-то информация", 0, 0, users[chat_id]->back_button());
        return;
    }
}

void office_staff_call_back_query(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query, int64_t chat_id, std::map<int64_t, std::shared_ptr<mtd::User>> &users) {
    if (query->data == "office_staff_buttons") {
        bot.getApi().sendMessage(chat_id, "zxc", 0, 0, users[chat_id]->get_inline_keyboard());
        return;
    }
    if (query->data == "office_staff_time_table") {
        bot.getApi().sendMessage(chat_id, "Ссылка на расписание для office staff", 0, 0, users[chat_id]->get_inline_keyboard());
    }
    else if (query->data == "office_staff_declaration") {
        bot.getApi().sendMessage(chat_id, "Актуальные объявления для office staff", 0, 0, users[chat_id]->get_inline_keyboard());
    }
    else if (query->data == "office_staff_connect_with_teacher") {
        bot.getApi().sendMessage(chat_id, "Списочек с контактами преподавателя для office staff", 0, 0, users[chat_id]->get_inline_keyboard());
    }
    else if (query->data == "office_staff_help") {
        bot.getApi().sendMessage(chat_id, "Помощь для office staff", 0, 0, users[chat_id]->get_inline_keyboard());
    }
    else if (query->data == "office_staff_back") {
        bot.getApi().sendMessage(chat_id, "Меню для office staff", 0, 0, users[chat_id]->get_menu());
        return;
    }
    else if (query->data == "office_staff_information") {
        bot.getApi().sendMessage(chat_id, "Какая-то информация для office staff", 0, 0, users[chat_id]->back_button());
        return;
    }
    else if (query->data == "office_add_info") {
        bot.getApi().sendMessage(chat_id, "Здесь вы можете ввести информацию", 0, 0, users[chat_id]->get_inline_keyboard());
    }
}

int main() {
    TgBot::Bot bot(mtd::token);
    std::map<int64_t, std::shared_ptr<mtd::User>> users;
    std::mutex mutex_for_users;

    bot.getEvents().onCommand("start", [&bot, &users](TgBot::Message::Ptr message) {
        auto st = std::make_shared<mtd::Student>(message->chat->id);
        users.insert({st->id(), st});
        bot.getApi().sendMessage(st->id(), "zDF", 0, 0, st->get_menu());
    });
    
    bot.getEvents().onCallbackQuery([&bot, &users, &mutex_for_users](TgBot::CallbackQuery::Ptr query) {
        std::lock_guard<std::mutex> lock(mutex_for_users);
        int64_t chat_id = query->message->chat->id;
        if (users.find(chat_id) == users.end()) {
            std::cout << "=== Error ===\n";
            return;
        }
        auto user = users[chat_id];
        if (user->get_role() == mtd::UserRole::STUDENT) {
            std::cout << "This is student\n";
        }
        else {
            std::cout << "This is office staff\n";
        }
        // перестает блестеть кнопочка
        // bot.getApi().answerCallbackQuery(query->id);
        if (user->get_role() == mtd::UserRole::STUDENT) {
            student_call_back_query(bot, query, chat_id, users);
        }
        else if (user->get_role() == mtd::UserRole::OFFICE_STAFF) {
            office_staff_call_back_query(bot, query, chat_id, users);
        }
        // for office staff 
        
    });

    try {
        std::cout << "Bot is running...\n";
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (const TgBot::TgException &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}