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
#include "sop.hpp"
#include "statistics.hpp"

mtd::Discipline t;
mtd::Subject OMP;
std::vector<std::string> declarations;

TgBot::InlineKeyboardMarkup::Ptr CompleteButton() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = "Завершить";
    button->callbackData = "complete_button";
    keyboard->inlineKeyboard.push_back({button});
    return keyboard;
}

TgBot::InlineKeyboardMarkup::Ptr get_raiting_scale() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    // Создаем кнопки от 1 до 10
    for (int i = 1; i < 11; ++i) {
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
        button->text = std::to_string(i);
        button->callbackData = std::to_string(i);  // Колбек-данные соответствуют цифре
        keyboard->inlineKeyboard.push_back({button});  // Добавляем кнопки в строку клавиатуры
    }
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = "Не моя группа";
    button->callbackData = "-1";
    keyboard->inlineKeyboard.push_back({button});
    return keyboard;
}

void StudentCallBackQuery(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query,
                          std::shared_ptr<mtd::User> user) {
    int64_t ChatId = user->id();
    if (query->data == "1" || query->data == "2" || query->data == "3" || query->data == "4"
        || query->data == "5" || query->data == "6" || query->data == "7" || query->data == "8"
        || query->data == "9" || query->data == "10" || query->data == "-1") {
        if (user->GetState() == mtd::UserState::STUDENT_SOP) {
            if (user->GetStep() == 0) {  // оценка лектора
                user->feedback.grade = std::stoi(query->data);
                bot.getApi().sendMessage(ChatId, "вы оценили лекции на " + query->data
                                                     + "\nНапишите, что вам нравится в лекциях");
                user->GetStep()++;
            } else if (user->GetStep() == 3) {
                user->feedback.grade = std::stoi(query->data);
                user->GetStep()++;
                bot.getApi().sendMessage(ChatId, "Оцените домашку", 0, 0, get_raiting_scale());
            } else if (user->GetStep() == 4) {
                user->feedback.grade_home_work = std::stoi(query->data);
                user->GetStep()++;
                bot.getApi().sendMessage(ChatId, "Что нравится");
            }
        }
    }

    //---------------------------------
    //---------------------------------
    if (query->data == "student_buttons") {
        bot.getApi().sendMessage(ChatId, "Навигация", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "student_sop" && user->GetStep() == 0) {
        if (t.name_subject.empty()) {
            bot.getApi().sendMessage(ChatId, "Пока что оценки преподавания нет", 0, 0, user->GetInlineKeyboard());
            return;
        }
        bot.getApi().sendMessage(ChatId,
                                 "Оцените лекции по " + t.name_subject + " (" + t.lector + ")", 0,
                                 0, get_raiting_scale());
        user->GetState() = mtd::UserState::STUDENT_SOP;
    } else if (query->data == "student_time_table") {
        bot.getApi().sendMessage(ChatId, "Ссылка на расписание", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "student_declaration") {
        std::string result_string;
        for (auto declaration : declarations) {
            result_string += declaration + "\n";
        }
        if (result_string.empty()) {
            result_string = "Объявлений нет";
        }
        bot.getApi().sendMessage(ChatId, result_string, 0, 0, user->BackButton());
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
        bot.getApi().sendMessage(ChatId, "Навигация", 0, 0, user->GetInlineKeyboard());
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
        bot.getApi().sendMessage(ChatId, "Навигация", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "teachert_information") {
        bot.getApi().sendMessage(ChatId, "Какая-то полезная инва для преподов", 0, 0,
                                 user->BackButton());
    }
}

void TutorCallBackQuery(TgBot::Bot &bot, TgBot::CallbackQuery::Ptr &query,
                        std::shared_ptr<mtd::User> user) {
    int64_t ChatId = user->id();
    if (query->data == "tutor_buttons") {
        bot.getApi().sendMessage(ChatId, "Навигация", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "tutor_add_subject") {
        bot.getApi().sendMessage(ChatId, "Введите название нового предмета", 0, 0,
                                 user->GetInlineKeyboard());
    } else if (query->data == "tutor_view_sop") {
        bot.getApi().sendMessage(ChatId, generate_statistics(OMP), 0, 0, user->GetMenu());

    } else if (query->data == "tutor_add_people") {
        bot.getApi().sendMessage(ChatId, "Введите ID студентов и групп, которых нужно добавить", 0,
                                 0, user->GetInlineKeyboard());
    } else if (query->data == "tutor_create_sop") {
        user->GetStep() = 0;
        user->GetState() = mtd::UserState::CREATE_SOP;
        bot.getApi().sendMessage(ChatId, "Название предмета");
    } else if (query->data == "tutor_back") {
        bot.getApi().sendMessage(ChatId, "Меню", 0, 0, user->GetMenu());
    } else if (query->data == "tutor_add_declaration") {
        bot.getApi().sendMessage(ChatId, "Введите объявление");
        user->GetState() = mtd::UserState::TUTOR_ADD_DECLARATION;
    }
}

int main() {
    OMP.name_subject = "ОМП";
    TgBot::Bot bot(mtd::token);
    std::map<int64_t, std::shared_ptr<mtd::User>> users;
    std::set<int64_t> NewUsers;
    std::mutex MutexForUsers;

    bot.getEvents().onCommand("username", [&](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Your username: @" + message->chat->username);
    });

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
            if (users.find(ChatId) == users.end()) {
                std::cout << "=== Error ===\n";
                return;
            }
            auto &user = users[ChatId];

            if (query->data == "complete_button") {
                bot.getApi().sendMessage(ChatId, "СОП по предмету " + t.name_subject + " создан", 0, 0, user->GetMenu());
                return;
            }

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
        } else if (user->GetState() == mtd::UserState::TUTOR_ADD_DECLARATION) {
            declarations.push_back(message->text);
            bot.getApi().sendMessage(ChatId, "Объявление успешно создано и сделана рассылка пользователям", 0, 0, user->GetMenu());
            for (const auto &iter : users) {
                if (iter.first == ChatId) {
                    continue;
                }
                std::string dec = "Объвяление от " + message->chat->firstName + " " + message->chat->lastName + ":\n" + message->text;
                bot.getApi().sendMessage(iter.first, dec, 0, 0, iter.second->GetMenu());
            }
            return;
        } else if (user->GetState() == mtd::UserState::STUDENT_SOP) {
            if (user->GetStep() == -1) {  // конец
                OMP.comments.push_back(message->text);
                bot.getApi().sendMessage(ChatId, "Меню", 0, 0, user->GetMenu());
            }
            if (user->GetStep() == 1) {
                user->feedback.advantages = message->text;
                bot.getApi().sendMessage(ChatId, "Что не нравится в лекциях?");
                user->GetStep()++;
            } else if (user->GetStep() == 2) {
                if (user->feedback.index == 0) {
                    user->feedback.disadvantages = message->text;
                    mtd::LectionFeedback q;
                    q.grade = user->feedback.grade;
                    q.advantages = user->feedback.advantages;
                    q.disadvantages = user->feedback.disadvantages;
                    OMP.lections_result.push_back(q);
                }
                user->GetStep()++;
                if (user->feedback.index < t.seminarians.size()) {
                    bot.getApi().sendMessage(
                        ChatId, "Оцените практику с " + t.seminarians[user->feedback.index], 0, 0,
                        get_raiting_scale());
                } else {
                    user->GetStep() = -1;
                    bot.getApi().sendMessage(ChatId, "Введите какой-нибудь коммент");
                }

            } else if (user->GetStep() == 5) {
                user->feedback.advantages = message->text;
                bot.getApi().sendMessage(ChatId, "Что не нравится");
                user->GetStep()++;
            } else if (user->GetStep() == 6) {
                user->feedback.disadvantages = message->text;
                mtd::PracticeFeedback q;
                q.grade = user->feedback.grade;
                q.grade_for_homework = user->feedback.grade_home_work;
                q.advantages = user->feedback.advantages;
                q.disadvantages = user->feedback.disadvantages;
                q.name_teacher = t.seminarians[user->feedback.index];
                OMP.practice_result.push_back(q);
                user->feedback.index++;
                user->GetStep() = 2;
                bot.getApi().sendMessage(ChatId, "Если хотите продолжить, введите что-то");
            }
        } else if (user->GetState() == mtd::UserState::CREATE_SOP) {
            if (user->GetStep() == 0) {
                t.name_subject = message->text;
                user->GetStep()++;
                bot.getApi().sendMessage(ChatId, "Как зовут лектора");
            } else if (user->GetStep() == 1) {
                t.lector = message->text;
                user->GetStep()++;
                bot.getApi().sendMessage(ChatId, "Как зовут практика", 0, 0, CompleteButton());
            } else if (user->GetStep() == 2) {
                t.seminarians.push_back(message->text);
                bot.getApi().sendMessage(ChatId, "Как зовут практика", 0, 0, CompleteButton());
            }
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

    std::cout << "Test started\n";
    for (int i = 0; i < 10000; ++i) {
        TgBot::Message::Ptr msg(new TgBot::Message);
        msg->text = "Test message " + std::to_string(i);
        bot.getEvents().handleMessage(msg);
    }
    std::cout << "Test finisded\n";
    return 0;
}