#include <fmt/core.h>
#include <tgbot/tgbot.h>

#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <pqxx/pqxx>
#include <set>
#include <thread>
#include <vector>

// #include "BotToken.hpp"
#include "OfficeStaff.hpp"
#include "Student.hpp"
#include "Teacher.hpp"
#include "Tutor.hpp"
#include "User.hpp"
#include "sop.hpp"
#include "statistics.hpp"

// Data Base
#include "../../DataBase/include/Course.hpp"
#include "../../DataBase/include/Dop_Functions.hpp"
#include "../../DataBase/include/InteractionsWithTables.hpp"
#include "../../DataBase/include/People_Group.hpp"
#include "../../DataBase/include/Person.hpp"
#include "../../DataBase/include/Person_Role.hpp"
#include "../../DataBase/include/Program.hpp"
#include "../../DataBase/include/Role.hpp"
#include "../../DataBase/include/SOP_Form.hpp"
#include "../../DataBase/include/Subject.hpp"
#include "../../DataBase/include/Subject_Offer.hpp"
#include "../../DataBase/include/TESTS.hpp"
#include "../../DataBase/include/Teaching_Assigment.hpp"

// Google API
#include "../../Google API/inc/manageSOP.hpp"

int InitDataBase() {
    const std::string conn_str
        = "dbname=ep_db user=danik password=60992425 hostaddr=127.0.0.1 port=5432";

    try {
        pqxx::connection conn(conn_str);
        if (!conn.is_open()) {
            throw std::runtime_error("Connection failed");
        }
        fmt::print("✓ Подключено к: {}\n", conn.dbname());
        pqxx::work txn(conn);

        DeleteAllTable(txn);
        CreateAllTable(txn);
        TEST_PERSON(txn);
        TEST_SUBJECT(txn);
        TEST_PROGRAM(txn);
        TEST_ROLE(txn);
        TEST_PERSON_GROUP(txn);

        TEST_PERSON_ROLE(txn);
        TEST_COURSE(txn);
        TEST_SUBJECT_OFFER(txn);
        TEST_TEACGING_ASSIGMENTS(txn);

        TEST_SOP_FORM(txn);

        TEST_GET_ALL_TEACHERS(txn);

        txn.commit();

    } catch (const std::exception &e) {
        fmt::print("произошла ошибка : {}\n", e.what());
    }

    return 0;
}

std::string GetUrlAnswer(pqxx::transaction_base &txn, std::string tg_nick) {
    try {
        std::string sql = "SELECT person_id FROM People WHERE tg_nick = $1";
        pqxx::result res = txn.exec_params(sql, tg_nick);
        if (res.empty()) {
            fmt::print("Не найден person_id для tg_nick");
            return "not found";
        }
        int person_id = res[0]["person_id"].as<int>();

        std::string sql2 = "SELECT url_answer FROM SOP_Form WHERE person_id = $1";
        pqxx::result res2 = txn.exec_params(sql2, person_id);
        if (res2.empty()) {
            fmt::print("Не найден url_answer для person_id");
            return "not found";
        }
        if (res2[0]["url_answer"].is_null()) {
            fmt::print("url_answer равен NULL");
            return "null";
        }
        return res2[0]["url_answer"].as<std::string>();
    } catch (const std::exception &e) {
        fmt::print("Ошибка при чтении: {}", e.what());
        return "error";
    }
}

mtd::Discipline t;
mtd::Subject OMP;
std::vector<std::string> declarations;
std::vector<std::string> quotes
    = {"Учись так, как будто тебе предстоит жить вечно.", "Знание — сила.",
       "Мотивация приходит во время действия.", "Каждый день — шанс стать лучше.",
       "Не бойся ошибаться — бойся не попробовать."};

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

    for (int i = 1; i < 11; ++i) {
        TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
        button->text = std::to_string(i);
        button->callbackData = std::to_string(i);
        keyboard->inlineKeyboard.push_back({button});
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
            if (user->GetStep() == 0) {
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

    if (query->data == "student_buttons") {
        bot.getApi().sendMessage(ChatId, "fsfsdf", 0, 0, user->GetInlineKeyboard());
    } else if (query->data == "student_sop" && user->GetStep() == 0) {
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

TgBot::InlineKeyboardMarkup::Ptr getAdminKeyboard() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);

    std::vector<TgBot::InlineKeyboardButton::Ptr> row1;
    TgBot::InlineKeyboardButton::Ptr btnOpenSOP(new TgBot::InlineKeyboardButton);
    btnOpenSOP->text = "📄 Открыть СОП";
    btnOpenSOP->callbackData = "admin_open_sop";
    row1.push_back(btnOpenSOP);

    std::vector<TgBot::InlineKeyboardButton::Ptr> row2;
    TgBot::InlineKeyboardButton::Ptr btnMakeAnnouncement(new TgBot::InlineKeyboardButton);
    btnMakeAnnouncement->text = "📢 Сделать объявление";
    btnMakeAnnouncement->callbackData = "admin_make_announcement";
    row2.push_back(btnMakeAnnouncement);

    std::vector<TgBot::InlineKeyboardButton::Ptr> row3;
    TgBot::InlineKeyboardButton::Ptr btnAddUser(new TgBot::InlineKeyboardButton);
    btnAddUser->text = "➕ Добавить человека";
    btnAddUser->callbackData = "admin_add_user";
    row3.push_back(btnAddUser);

    std::vector<TgBot::InlineKeyboardButton::Ptr> row4;
    TgBot::InlineKeyboardButton::Ptr btnRemoveUser(new TgBot::InlineKeyboardButton);
    btnRemoveUser->text = "➖ Удалить человека";
    btnRemoveUser->callbackData = "admin_remove_user";
    row4.push_back(btnRemoveUser);

    keyboard->inlineKeyboard.push_back(row1);
    keyboard->inlineKeyboard.push_back(row2);
    keyboard->inlineKeyboard.push_back(row3);
    keyboard->inlineKeyboard.push_back(row4);

    return keyboard;
}

std::set<int64_t> waiting_for_admin_code, users_admin;
std::mutex mutes_for_admin;

enum class AdminState { ADD_USER, MAKE_ANOUNSMENT, DELETE_USER };
std::map<int64_t, AdminState> AdminStarus;

int main() {
    const std::string conn_str
        = "dbname=ep_db user=danik password=60992425 hostaddr=127.0.0.1 port=5432";

    try {
        pqxx::connection conn(conn_str);
        if (!conn.is_open()) {
            throw std::runtime_error("Connection failed");
        }
        fmt::print("✓ Подключено к: {}\n", conn.dbname());

        pqxx::work txn_open(conn);
        DeleteAllTable(txn_open);
        CreateAllTable(txn_open);
        txn_open.commit();

        {
            pqxx::work txn(conn);
            CreatePersonWithParams(txn, Person("XHR", "Aleck", "sexmen", 1, 83883, "Lector", "Math",
                                               "1st Year", "PMI", "Group A"));
            txn.commit();
        }

        {
            pqxx::work txn(conn);
            CreatePersonWithParams(txn, Person("simarova", "Kate", "kate", 1, 23424, "Practitioner",
                                               "Math", "1st Year", "PMI", "Group A"));

            txn.commit();
        }

        OMP.name_subject = "ОМП";
        TgBot::Bot bot("7472835556:AAGGxuQuWDgYb9rskK3tn7YG660YEg7OgKM");
        std::map<int64_t, std::shared_ptr<mtd::User>> users;
        std::set<int64_t> NewUsers;
        std::mutex MutexForUsers;

        bot.getEvents().onCommand("secret", [&bot](TgBot::Message::Ptr message) {
            if (users_admin.count(message->chat->id)) {
                bot.getApi().sendMessage(message->chat->id, "Панель админимтратора:", 0, 0,
                                         getAdminKeyboard());
            } else {
                bot.getApi().sendMessage(message->chat->id, "Вы не являетесь администратором");
            }
        });
        bot.getEvents().onCommand("admin", [&bot](TgBot::Message::Ptr message) {
            std::lock_guard<std::mutex> lock(mutes_for_admin);
            waiting_for_admin_code.insert(message->chat->id);
            bot.getApi().sendMessage(message->chat->id, "Введите пароль");
        });
        
        bot.getEvents().onCommand("sooop", [&bot, &conn](TgBot::Message::Ptr message) {
            try {
                pqxx::work txn(conn);
                std::string url_answer = GetUrlAnswer(txn, "st_luka");
                txn.commit();
                if (!url_answer.empty()) {
                    bot.getApi().sendMessage(message->chat->id, url_answer);
                } else {
                    bot.getApi().sendMessage(message->chat->id, "Информация не найдена");
                }
            } catch (const std::exception& e) {
                fmt::print("Ошибка: {}", e.what());
            }
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

        bot.getEvents().onCallbackQuery([&](TgBot::CallbackQuery::Ptr query) {
            std::lock_guard<std::mutex> lock(MutexForUsers);
            int64_t ChatId = query->message->chat->id;
            if (query->data == "admin_open_sop") {
                {
                    {
                        pqxx::work txn(conn);
                        AssignCompletelyToPeople(txn);
                        txn.commit();
                    }

                    pqxx::work txn1(conn);
                    std::vector<int> person_ids = ReadSubjectId(txn1);
                    txn1.commit();

                    sop::Config config = sop::Config::getInstance();
                    sop::HttpClient httpClient;
                    std::string file_path = "GoogleAPI/json/formTitle.json";

                    for (const auto &id : person_ids) {
                        std::string formId = sop::createForm(file_path, config, httpClient);
                        pqxx::work txn1(conn);
                        nlohmann::json question = sop::generateQuestionsPerStudent(txn1, id);
                        txn1.commit();
                        sop::addFieldToForm(formId, question, config, httpClient);
                        pqxx::work txn2(conn);
                        std::string formUrl = sop::getFormUrl(formId);
                        CreateSOPForm(txn2, id, formUrl, " ", " ");
                        txn2.commit();
                    }
                }

                bot.getApi().sendMessage(ChatId, "СОП открыт");
            } else if (query->data == "admin_add_user") {
                std::cout << "admin_add_user\n";
                bot.getApi().sendMessage(ChatId, "Введите данные:");
                AdminStarus[ChatId] = AdminState::ADD_USER;
            } else if (query->data == "admin_remove_user") {
                bot.getApi().sendMessage(ChatId, "Напиши тгник");
                AdminStarus[ChatId] = AdminState::DELETE_USER;
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
            if (users.find(ChatId) == users.end()) {
                std::cout << "=== Error ===\n";
                return;
            }
            auto &user = users[ChatId];

            if (query->data == "complete_button") {
                std::cout << "sfdfdfdf\n";
                bot.getApi().sendMessage(ChatId, "_", 0, 0, user->GetMenu());
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

        bot.getEvents().onAnyMessage([&bot, &users, &MutexForUsers,
                                      &conn](TgBot::Message::Ptr message) {
            std::lock_guard<std::mutex> lock(MutexForUsers);
            int64_t ChatId = message->chat->id;

            if (users_admin.count(ChatId) && AdminStarus[ChatId] == AdminState::ADD_USER) {
                Logger::getInstance().info("Hello, World!");

                {
                    pqxx::work txn(conn);
                    CreatePersonWithParams(
                        txn, Person("Egor", "Lukavenko", "st_luka", 1, 123456789, "Student", "Math",
                                    "1st Year", "PMI", "Group A"));
                    txn.commit();
                }

            } else if (users_admin.count(ChatId)
                       && AdminStarus[ChatId] == AdminState::DELETE_USER) {
                bot.getApi().sendMessage(ChatId, "Person is deleted");

                {
                    pqxx::work txn(conn);
                    DeletePerson(txn, message->text);
                }
            }

            if (waiting_for_admin_code.count(ChatId)) {
                if (message->text == "123456") {
                    users_admin.insert(ChatId);
                    bot.getApi().sendMessage(ChatId,
                                             "Поздравляю!!! Вы теперь админ. При команде /secret у "
                                             "вас будет админская панель");
                    waiting_for_admin_code.erase(ChatId);
                } else {
                    bot.getApi().sendMessage(ChatId,
                                             "Пароль неверн, вы можете попробовать еще раз. И не "
                                             "надо пиздеть, если ты не админ, то вали нахер "
                                             "отсуда. Алминская панель не для таких лохов как ты");
                }
            }

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
                bot.getApi().sendMessage(
                    ChatId, "Объявление успешно создано и сделана рассылка пользователям", 0, 0,
                    user->GetMenu());
                for (const auto &iter : users) {
                    if (iter.first == ChatId) {
                        continue;
                    }
                    std::string dec = "Объвяление от " + message->chat->firstName + " "
                                      + message->chat->lastName + ":\n" + message->text;
                    bot.getApi().sendMessage(iter.first, dec, 0, 0, iter.second->GetMenu());
                }
                return;
            } else if (user->GetState() == mtd::UserState::STUDENT_SOP) {
                if (user->GetStep() == -1) {
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
                            ChatId, "Оцените практику с " + t.seminarians[user->feedback.index], 0,
                            0, get_raiting_scale());
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

    } catch (const std::exception &e) {
        fmt::print("произошла ошибка : {}\n", e.what());
    }

    return 0;
}
