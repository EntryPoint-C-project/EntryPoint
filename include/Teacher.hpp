#ifndef TEACHER_HPP_
#define TEACHER_HPP_

#include "User.hpp"

namespace mtd {
class Teacher : public User {
public:
    Teacher(int64_t chat_id) : User(chat_id, UserRole::TEACHER) {}
    TgBot::InlineKeyboardMarkup::Ptr GetInlineKeyboard() override;
    TgBot::InlineKeyboardMarkup::Ptr GetMenu() override;
    TgBot::InlineKeyboardMarkup::Ptr BackButton() override;
};
}  // namespace mtd

#endif