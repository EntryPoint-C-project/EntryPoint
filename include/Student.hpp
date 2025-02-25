#ifndef STUDENT_GPP_
#define STUDENT_GPP_

#include "User.hpp"

namespace mtd {
class Student : public User {
public:
    Student(int64_t chat_id) : User(chat_id, UserRole::STUDENT) {}
    TgBot::InlineKeyboardMarkup::Ptr GetInlineKeyboard() override;
    TgBot::InlineKeyboardMarkup::Ptr GetMenu() override;
    TgBot::InlineKeyboardMarkup::Ptr BackButton() override;
};
}  // namespace mtd

#endif