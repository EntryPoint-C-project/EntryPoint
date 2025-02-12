#ifndef USER_HPP_
#define USER_HPP_

#include <tgbot/tgbot.h>

namespace mtd {
enum class UserRole { STUDENT, TEACHER, OFFICE_STAFF, TUTOR, NONE }; 

class User {
    int64_t chat_id = 0;
    UserRole role = UserRole::NONE;
public:
    explicit User(int64_t chat_id, UserRole role) : chat_id(chat_id), role(role) {}
    virtual ~User() {}  
    int64_t id() const;
    UserRole get_role() const;
    virtual TgBot::InlineKeyboardMarkup::Ptr get_inline_keyboard() = 0;
    virtual TgBot::InlineKeyboardMarkup::Ptr get_menu() = 0;
    virtual TgBot::InlineKeyboardMarkup::Ptr back_button() = 0;
};
}

#endif