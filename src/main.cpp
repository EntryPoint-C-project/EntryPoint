#include <tgbot/tgbot.h>
#include "BotToken.hpp"
#include "User.hpp"
#include "Student.hpp"
#include "OfficeStaff.hpp"
#include "Teacher.hpp"
#include "Tutor.hpp"
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <vector>



TgBot::InlineKeyboardMarkup::Ptr get_raiting_scale() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    // Создаем кнопки от 1 до 10
    for (int i = 1; i < 11; ++i) {
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
        button->text = std::to_string(i);
        button->callbackData = std::to_string(i);  // Колбек-данные соответствуют цифре
        keyboard->inlineKeyboard.push_back({button}); // Добавляем кнопки в строку клавиатуры
    }
    return keyboard;
}

void student_call_back_query(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query, std::shared_ptr<mtd::User> user) {
    int64_t chat_id = user->id();
    if (query->data == "1" || query->data == "2" || query->data == "3" || query->data == "4" || 
        query->data == "5" || query->data == "6" || query->data == "7" || query->data == "8" || 
        query->data == "9" || query->data == "10") {
        
        bot.getApi().sendMessage(chat_id, "Этого лоха ты оценил на " + query->data + ".\nИзменить свой выбор нельзя(");
        user->get_evaluations().push_back(std::stoi(query->data));
        // Следующий вопрос
        if (user->get_step() < 5) {
            bot.getApi().sendMessage(chat_id, "Вопрос " + std::to_string(user->get_step() + 1), 0, 0, get_raiting_scale());
            user->get_step()++; // Переход к следующему вопросу
        } else {
            bot.getApi().sendMessage(chat_id, "Опрос завершен. Спасибо за участие!", 0, 0, user->back_button());
            user->get_state() = mtd::UserState::NONE;
            user->get_step() = 0;
        }
    }

    //---------------------------------
    //---------------------------------
    if (query->data == "student_buttons") {
        bot.getApi().sendMessage(chat_id, "fsfsdf", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "student_sop" && user->get_step() == 0) {
        bot.getApi().sendMessage(chat_id, "Вопрос 1", 0, 0, get_raiting_scale());
        user->get_step()++;
        user->get_state() = mtd::UserState::STUDENT_SOP;
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

void tutor_call_back_query(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query, std::shared_ptr<mtd::User> user) {
    int64_t chat_id = user->id();
    if (query->data == "tutor_buttons") {
        bot.getApi().sendMessage(chat_id, "fsdf", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "tutor_add_subject") {
        bot.getApi().sendMessage(chat_id, "Введите название нового предмета", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "tutor_view_sop") {
        user->get_state() = mtd::UserState::TUTOR_SOP;
        bot.getApi().sendMessage(chat_id, "Введите id пользователя");
        
    }
    else if (query->data == "tutor_add_people") {
        bot.getApi().sendMessage(chat_id, "Введите ID студентов и групп, которых нужно добавить", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "tutor_create_sop") {
        bot.getApi().sendMessage(chat_id, "Введите данные для создания SOP", 0, 0, user->get_inline_keyboard());
    }
    else if (query->data == "tutor_back") {
        bot.getApi().sendMessage(chat_id, "Меню", 0, 0, user->get_menu());
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
        std::cout << "User connect: " << message->chat->id << '\n';
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

        TgBot::InlineKeyboardButton::Ptr b4(new TgBot::InlineKeyboardButton);
        b4->text = "Куратор";
        b4->callbackData = "tutor";

        keyboard->inlineKeyboard.push_back({b1});
        keyboard->inlineKeyboard.push_back({b2});
        keyboard->inlineKeyboard.push_back({b3});
        keyboard->inlineKeyboard.push_back({b4});

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
            else if (query->data == "tutor") {
                auto tutor_ptr = std::make_shared<mtd::Tutor>(chat_id);
                users.insert({chat_id, tutor_ptr});
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
        else if (user->get_role() == mtd::UserRole::TUTOR) {
            
            tutor_call_back_query(bot, query, user);
        }
    });

    bot.getEvents().onAnyMessage([&bot, &users, &mutex_for_users](TgBot::Message::Ptr message){
        std::lock_guard<std::mutex> lock(mutex_for_users);
        int64_t chat_id = message->chat->id;
    
        if (users.find(chat_id) == users.end()) {
            std::cout << "=== Error 2 ===\n";
            return;
        }
        auto &user = users[chat_id];

        if (user->get_state() == mtd::UserState::TUTOR_SOP) {
            int64_t student_chat_id = static_cast<int64_t>(std::stoll(message->text));
            std::string s;
            for (const auto i : users[student_chat_id]->get_evaluations()) {
                s += std::to_string(i) + " ";
            }
            bot.getApi().sendMessage(chat_id, "Оценки этого студента:\n" + s, 0, 0, user->back_button());
            return;
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