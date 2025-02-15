#ifndef STUDENT_GPP_
#define STUDENT_GPP_

#include "User.hpp"

namespace mtd {
class Student : public User {
public:
    Student(int64_t chat_id) : User(chat_id, UserRole::STUDENT) {} 
    TgBot::InlineKeyboardMarkup::Ptr get_inline_keyboard() override;
    TgBot::InlineKeyboardMarkup::Ptr get_menu() override;
    TgBot::InlineKeyboardMarkup::Ptr back_button() override;
};
}



#endif