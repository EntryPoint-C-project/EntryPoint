#ifndef USER_HPP_
#define USER_HPP_

#include <tgbot/tgbot.h>
#include <map>
#include <vector>

namespace mtd {
enum class UserRole { STUDENT, TEACHER, OFFICE_STAFF, TUTOR, NONE }; 
enum class UserState { MENU, BUTTONS, INFORMATION, STUDENT_SOP, TUTOR_SOP, NONE };

class User {
    int64_t chat_id = 0;
    UserRole role = UserRole::NONE;
    UserState state = UserState::NONE;
    int step = 0;
    std::vector<int> evaluations;
public:
    explicit User(int64_t chat_id, UserRole role) : chat_id(chat_id), role(role), state(UserState::NONE) {}
    virtual ~User() {}  
    int64_t id() const;
    UserRole get_role() const;
    UserState &get_state();
    int &get_step();
    std::vector<int> &get_evaluations();
    virtual TgBot::InlineKeyboardMarkup::Ptr get_inline_keyboard() = 0;
    virtual TgBot::InlineKeyboardMarkup::Ptr get_menu() = 0;
    virtual TgBot::InlineKeyboardMarkup::Ptr back_button() = 0;
};
}

#endif