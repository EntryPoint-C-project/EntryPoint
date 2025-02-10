#include <tgbot/tgbot.h>
#include "BotToken.hpp"
#include <map>
#include "Student.hpp"
#include <memory>

int main() {
    TgBot::Bot bot(mtd::token);
    std::map<int64_t, std::shared_ptr<mtd::Student>> users;

    bot.getEvents().onCommand("start", [&bot, &users](TgBot::Message::Ptr message) {
        auto st = std::make_shared<mtd::Student>(message->chat->id);
        users.insert({st->id(), st});
        bot.getApi().sendMessage(st->id(), "zDF", 0, 0, st->get_inline_keyboard());
    });
    
    bot.getEvents().onCallbackQuery([&bot, &users](TgBot::CallbackQuery::Ptr query) {
        int64_t chat_id = query->message->chat->id;
        // перестает блестеть кнопочка
        // bot.getApi().answerCallbackQuery(query->id);
        if (query->data == "student_time_table") {
            bot.getApi().sendMessage(chat_id, "Ссылка на расписание");
        }
        else if (query->data == "student_declaration") {
            bot.getApi().sendMessage(chat_id, "Актуальные объявления");
        }
        else if (query->data == "student_connect_with_teacher") {
            bot.getApi().sendMessage(chat_id, "Списочек с контактами преподавателя");
        }
        else if (query->data == "student_help") {
            bot.getApi().sendMessage(chat_id, "Помощь");
        }
        else if (query->data == "student_back") {
            bot.getApi().sendMessage(chat_id, "Меню", 0, 0, users[chat_id]->get_menu());
            return;
        }
        else if (query->data == "student_information") {
            bot.getApi().sendMessage(chat_id, "Какая-то информация", 0, 0, users[chat_id]->back_button());
            return;
        }
        bot.getApi().sendMessage(chat_id, "sdfds", 0, 0, users[chat_id]->get_inline_keyboard());
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