#include <tgbot/tgbot.h>
#include "BotToken.hpp"
#include <map>
#include "User.hpp"
#include "Student.hpp"
#include "OfficeStaff.hpp"
#include "Teacher.hpp"
#include <memory>
#include <mutex>
#include <set>

void student_call_back_query(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query, std::shared_ptr<mtd::User> user) {
    int64_t chat_id = user->id();
    if (query->data == "student_buttons") {
        bot.getApi().sendMessage(chat_id, "fsfsdf", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "student_time_table") {
        bot.getApi().sendMessage(chat_id, "Ссылка на расписание", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "student_declaration") {
        bot.getApi().sendMessage(chat_id, "Актуальные объявления", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "student_connect_with_teacher") {
        bot.getApi().sendMessage(chat_id, "Списочек с контактами преподавателя", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "student_help") {
        bot.getApi().sendMessage(chat_id, "Помощь", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "student_back") {
        bot.getApi().sendMessage(chat_id, "Меню", 0, 0, user->get_menu());
    }
    else if (query->data == "student_information") {
        bot.getApi().sendMessage(chat_id, "Какая-то информация", 0, 0, user->back_button());
    }
}

void office_staff_call_back_query(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query, std::shared_ptr<mtd::User> user) {
    int64_t chat_id = user->id();
    if (query->data == "office_staff_buttons") {
        bot.getApi().sendMessage(chat_id, "Кнопочки", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "office_staff_time_table") {
        bot.getApi().sendMessage(chat_id, "Ссылка на расписание для office staff", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "office_staff_declaration") {
        bot.getApi().sendMessage(chat_id, "Актуальные объявления для office staff", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "office_staff_connect_with_teacher") {
        bot.getApi().sendMessage(chat_id, "Списочек с контактами преподавателя для office staff", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "office_staff_help") {
        bot.getApi().sendMessage(chat_id, "Помощь для office staff", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "office_staff_back") {
        bot.getApi().sendMessage(chat_id, "Меню для office staff", 0, 0, user->get_menu());
    }
    else if (query->data == "office_staff_information") {
        bot.getApi().sendMessage(chat_id, "Какая-то информация для office staff", 0, 0, user->back_button());
    }
    else if (query->data == "office_add_info") {
        bot.getApi().sendMessage(chat_id, "Здесь вы можете ввести информацию", 0, 0, user->get_inline_keyboard());
    }
}

void teacher_call_back_query(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query, std::shared_ptr<mtd::User> user) {
    int64_t chat_id = user->id();
    if (query->data == "teacher_declaration") {
        bot.getApi().sendMessage(chat_id, "Вы преподаватель и вы можите сделать объявление", 0, 0, user->back_button());
    }
    else if (query->data == "teacher_back") {
        bot.getApi().sendMessage(chat_id, "Меню", 0, 0, user->get_menu());
    }
    else if (query->data == "teacher_buttons") {
        bot.getApi().sendMessage(chat_id, "Кнопочки для преподов", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "teachert_information") {
        bot.getApi().sendMessage(chat_id, "Какая-то полезная инва для преподов", 0, 0, user->back_button());
    }
}

int main() {
    TgBot::Bot bot(mtd::token);
    std::map<int64_t, std::shared_ptr<mtd::User>> users;
    std::set<int64_t> new_users;
    std::mutex mutex_for_users;

    bot.getEvents().onCommand("start", [&bot, &users, &mutex_for_users, &new_users](TgBot::Message::Ptr message) {
        std::lock_guard<std::mutex> lock(mutex_for_users);
        new_users.insert(message->chat->id);

        TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
        TgBot::InlineKeyboardButton::Ptr b1(new TgBot::InlineKeyboardButton);
        b1->text = "Студент";
        b1->callbackData = "student";

        TgBot::InlineKeyboardButton::Ptr b2(new TgBot::InlineKeyboardButton);
        b2->text = "Очебный офис";
        b2->callbackData = "office_staff";

        TgBot::InlineKeyboardButton::Ptr b3(new TgBot::InlineKeyboardButton);
        b3->text = "Преподаватель";
        b3->callbackData = "teacher";

        keyboard->inlineKeyboard.push_back({b1});
        keyboard->inlineKeyboard.push_back({b2});
        keyboard->inlineKeyboard.push_back({b3});

        bot.getApi().sendMessage(message->chat->id, "Кто ты?", 0, 0, keyboard);
    });
    
    bot.getEvents().onCallbackQuery([&bot, &users, &mutex_for_users, &new_users](TgBot::CallbackQuery::Ptr query) {
        std::lock_guard<std::mutex> lock(mutex_for_users);
        int64_t chat_id = query->message->chat->id;
        if (users.find(chat_id) == users.end()) {
            std::cout << "=== Error ===\n";
        }
        
        if (new_users.find(chat_id) != new_users.end()) {
            if (query->data == "student") {
                auto student_ptr = std::make_shared<mtd::Student>(chat_id);
                users.insert({chat_id, student_ptr});
            }
            else if (query->data == "office_staff") {
                auto office_staff_ptr = std::make_shared<mtd::OfficeStaff>(chat_id);
                users.insert({chat_id, office_staff_ptr});
            }
            else if (query->data == "teacher") {
                auto teacher_ptr = std::make_shared<mtd::Teacher>(chat_id);
                users.insert({chat_id, teacher_ptr});
            }
            
            bot.getApi().sendMessage(chat_id, "Меню", 0, 0, users[chat_id]->get_menu());
            new_users.erase(chat_id);
            return;
        }
        

        auto &user = users[chat_id];
        if (user->get_role() == mtd::UserRole::STUDENT) {
            student_call_back_query(bot, query, user);
        }
        else if (user->get_role() == mtd::UserRole::OFFICE_STAFF) {
            office_staff_call_back_query(bot, query, user);
        }
        else if (user->get_role() == mtd::UserRole::TEACHER) {
            teacher_call_back_query(bot, query, user);
        }
        
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