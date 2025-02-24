#include <tgbot/tgbot.h>

#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <vector>

#include "BotToken.hpp"
#include "OfficeStaff.hpp"
#include "Student.hpp"
#include "Teacher.hpp"
#include "Tutor.hpp"
#include "User.hpp"

TgBot::InlineKeyboardMarkup::Ptr get_raiting_scale() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    // Создаем кнопки от 1 до 10
    for (int i = 1; i < 11; ++i) {
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
        button->text = std::to_string(i);
        button->callbackData = std::to_string(i);  // Колбек-данные соответствуют цифре
        keyboard->inlineKeyboard.push_back({button});  // Добавляем кнопки в строку клавиатуры
    }
    return keyboard;
}

void StudentCallBackQuery(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query,
                          std::shared_ptr<mtd::User> user) {
    int64_t ChatId = user->id();
    if (query->data == "1" || query->data == "2" || query->data == "3" || query->data == "4"
        || query->data == "5" || query->data == "6" || query->data == "7" || query->data == "8"
        || query->data == "9" || query->data == "10") {
        bot.getApi().sendMessage(
            ChatId, "Этого лоха ты оценил на " + query->data + ".\nИзменить свой выбор нельзя(");
        user->GetEvaluations().push_back(std::stoi(query->data));
        // Следующий вопрос
        if (user->GetStep() < 5) {
            bot.getApi().sendMessage(ChatId, "Вопрос " + std::to_string(user->GetStep() + 1), 0, 0,
                                     get_raiting_scale());
            user->GetStep()++;  // Переход к следующему вопросу
        } else {
            bot.getApi().sendMessage(ChatId, "Опрос завершен. Спасибо за участие!", 0, 0,
                                     user->BackButton());
            user->GetState() = mtd::UserState::NONE;
            user->GetStep() = 0;
        }
    }

    //---------------------------------
    //---------------------------------
    if (query->data == "student_buttons") {
        bot.getApi().sendMessage(ChatId, "fsfsdf", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "student_sop" && user->GetStep() == 0) {
        bot.getApi().sendMessage(ChatId, "Вопрос 1", 0, 0, get_raiting_scale());
        user->GetStep()++;
        user->GetState() = mtd::UserState::STUDENT_SOP;
    } else if (query->data == "student_time_table") {
        bot.getApi().sendMessage(ChatId, "Ссылка на расписание", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "student_declaration") {
        bot.getApi().sendMessage(ChatId, "Актуальные объявления", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "student_connect_with_teacher") {
        bot.getApi().sendMessage(ChatId, "Списочек с контактами преподавателя", 0, 0,
                                 user->GetInlineKeyboard());
    } else if (query->data == "student_help") {
        bot.getApi().sendMessage(ChatId, "Помощь", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "student_back") {
        bot.getApi().sendMessage(ChatId, "Меню", 0, 0, user->GetMenu());
    } else if (query->data == "student_information") {
        bot.getApi().sendMessage(ChatId, "Какая-то информация", 0, 0, user->BackButton());
    }
}

void OfficeStaffCallBackQuery(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query,
                              std::shared_ptr<mtd::User> user) {
    int64_t ChatId = user->id();
    if (query->data == "office_staff_buttons") {
        bot.getApi().sendMessage(ChatId, "Кнопочки", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "office_staff_time_table") {
        bot.getApi().sendMessage(ChatId, "Ссылка на расписание для office staff", 0, 0,
                                 user->GetInlineKeyboard());
    } else if (query->data == "office_staff_declaration") {
        bot.getApi().sendMessage(ChatId, "Актуальные объявления для office staff", 0, 0,
                                 user->GetInlineKeyboard());
    } else if (query->data == "office_staff_connect_with_teacher") {
        bot.getApi().sendMessage(ChatId, "Списочек с контактами преподавателя для office staff", 0,
                                 0, user->GetInlineKeyboard());
    } else if (query->data == "office_staff_help") {
        bot.getApi().sendMessage(ChatId, "Помощь для office staff", 0, 0,
                                 user->GetInlineKeyboard());
    } else if (query->data == "office_staff_back") {
        bot.getApi().sendMessage(ChatId, "Меню для office staff", 0, 0, user->GetMenu());
    } else if (query->data == "office_staff_information") {
        bot.getApi().sendMessage(ChatId, "Какая-то информация для office staff", 0, 0,
                                 user->BackButton());
    } else if (query->data == "office_add_info") {
        bot.getApi().sendMessage(ChatId, "Здесь вы можете ввести информацию", 0, 0,
                                 user->GetInlineKeyboard());
    }
}

void TeacherCallBackQuery(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query,
                          std::shared_ptr<mtd::User> user) {
    int64_t ChatId = user->id();
    if (query->data == "teacher_declaration") {
        bot.getApi().sendMessage(ChatId, "Вы преподаватель и вы можите сделать объявление", 0, 0,
                                 user->BackButton());
    } else if (query->data == "teacher_back") {
        bot.getApi().sendMessage(ChatId, "Меню", 0, 0, user->GetMenu());
    } else if (query->data == "teacher_buttons") {
        bot.getApi().sendMessage(ChatId, "Кнопочки для преподов", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "teachert_information") {
        bot.getApi().sendMessage(ChatId, "Какая-то полезная инва для преподов", 0, 0,
                                 user->BackButton());
    }
}

void TutorCallBackQuery(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query,
                        std::shared_ptr<mtd::User> user) {
    int64_t ChatId = user->id();
    if (query->data == "tutor_buttons") {
        bot.getApi().sendMessage(ChatId, "fsdf", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "tutor_add_subject") {
        bot.getApi().sendMessage(ChatId, "Введите название нового предмета", 0, 0,
                                 user->GetInlineKeyboard());
    } else if (query->data == "tutor_view_sop") {
        user->GetState() = mtd::UserState::TUTOR_SOP;
        bot.getApi().sendMessage(ChatId, "Введите id пользователя");

    } else if (query->data == "tutor_add_people") {
        bot.getApi().sendMessage(ChatId, "Введите ID студентов и групп, которых нужно добавить", 0,
                                 0, user->GetInlineKeyboard());
    } else if (query->data == "tutor_create_sop") {
        bot.getApi().sendMessage(ChatId, "Введите данные для создания SOP", 0, 0,
                                 user->GetInlineKeyboard());
    } else if (query->data == "tutor_back") {
        bot.getApi().sendMessage(ChatId, "Меню", 0, 0, user->GetMenu());
    }
}

int main() {
    TgBot::Bot bot(mtd::token);
    std::map<int64_t, std::shared_ptr<mtd::User>> users;
    std::set<int64_t> NewUsers;
    std::mutex MutexForUsers;

    bot.getEvents().onCommand(
        "start", [&bot, &users, &MutexForUsers, &NewUsers](TgBot::Message::Ptr message) {
            std::lock_guard<std::mutex> lock(MutexForUsers);
            NewUsers.insert(message->chat->id);
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

    bot.getEvents().onCallbackQuery(
        [&bot, &users, &MutexForUsers, &NewUsers](TgBot::CallbackQuery::Ptr query) {
            std::lock_guard<std::mutex> lock(MutexForUsers);
            int64_t ChatId = query->message->chat->id;

            if (users.find(ChatId) == users.end()) {
                std::cout << "=== Error ===\n";
            }

            if (NewUsers.find(ChatId) != NewUsers.end()) {
                if (query->data == "student") {
                    auto student_ptr = std::make_shared<mtd::Student>(ChatId);
                    users.insert({ChatId, student_ptr});
                } else if (query->data == "office_staff") {
                    auto office_staff_ptr = std::make_shared<mtd::OfficeStaff>(ChatId);
                    users.insert({ChatId, office_staff_ptr});
                } else if (query->data == "teacher") {
                    auto teacher_ptr = std::make_shared<mtd::Teacher>(ChatId);
                    users.insert({ChatId, teacher_ptr});
                } else if (query->data == "tutor") {
                    auto tutor_ptr = std::make_shared<mtd::Tutor>(ChatId);
                    users.insert({ChatId, tutor_ptr});
                }

                bot.getApi().sendMessage(ChatId, "Меню", 0, 0, users[ChatId]->GetMenu());
                NewUsers.erase(ChatId);
                return;
            }

            auto &user = users[ChatId];
            if (user->GetRole() == mtd::UserRole::STUDENT) {
                StudentCallBackQuery(bot, query, user);
            } else if (user->GetRole() == mtd::UserRole::OFFICE_STAFF) {
                OfficeStaffCallBackQuery(bot, query, user);
            } else if (user->GetRole() == mtd::UserRole::TEACHER) {
                TeacherCallBackQuery(bot, query, user);
            } else if (user->GetRole() == mtd::UserRole::TUTOR) {
                TutorCallBackQuery(bot, query, user);
            }
        });

    bot.getEvents().onAnyMessage([&bot, &users, &MutexForUsers](TgBot::Message::Ptr message) {
        std::lock_guard<std::mutex> lock(MutexForUsers);
        int64_t ChatId = message->chat->id;

        if (users.find(ChatId) == users.end()) {
            std::cout << "=== Error 2 ===\n";
            return;
        }
        auto &user = users[ChatId];

        if (user->GetState() == mtd::UserState::TUTOR_SOP) {
            int64_t student_ChatId = static_cast<int64_t>(std::stoll(message->text));
            std::string s;
            for (const auto i : users[student_ChatId]->GetEvaluations()) {
                s += std::to_string(i) + " ";
            }
            bot.getApi().sendMessage(ChatId, "Оценки этого студента:\n" + s, 0, 0,
                                     user->BackButton());
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