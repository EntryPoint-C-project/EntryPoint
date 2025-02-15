#ifndef TEACHER_HPP_
#define TEACHER_HPP_

#include "User.hpp"

namespace mtd {
class Teacher : public User {
public:
    Teacher(int64_t chat_id) : User(chat_id, UserRole::TEACHER) {}
    TgBot::InlineKeyboardMarkup::Ptr get_inline_keyboard() override;
    TgBot::InlineKeyboardMarkup::Ptr get_menu() override;
    TgBot::InlineKeyboardMarkup::Ptr back_button() override;
};
}

#endif