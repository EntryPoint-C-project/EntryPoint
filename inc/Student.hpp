#ifndef STUDENT_GPP_
#define STUDENT_GPP_

#include <tgbot/tgbot.h>
#include "User.hpp"

namespace mtd {
class Student : public User {
public:
    Student(int64_t chat_id) : User(chat_id, UserRole::STUDENT) {} 
    TgBot::InlineKeyboardMarkup::Ptr get_inline_keyboard();
    TgBot::InlineKeyboardMarkup::Ptr get_menu();
    TgBot::InlineKeyboardMarkup::Ptr back_button();
};
}



#endif