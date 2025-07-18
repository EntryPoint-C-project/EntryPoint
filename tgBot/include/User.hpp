#ifndef USER_HPP_
#define USER_HPP_

#include <tgbot/tgbot.h>

#include <map>
#include <vector>

#include "sop.hpp"

namespace mtd {
enum class UserRole { STUDENT, TEACHER, OFFICE_STAFF, TUTOR, NONE };
enum class UserState {
    MENU,
    BUTTONS,
    INFORMATION,
    STUDENT_SOP,
    TUTOR_SOP,
    CREATE_SOP,
    TUTOR_ADD_DECLARATION,
    NONE
};

class User {
    int64_t chat_id = 0;
    UserRole role = UserRole::NONE;
    UserState state = UserState::NONE;
    int step = 0;
    std::vector<int> evaluations;

public:
    explicit User(int64_t chat_id, UserRole role);
    virtual ~User();
    Feedback feedback;
    int64_t id() const;
    UserRole GetRole() const;
    UserState &GetState();
    int &GetStep();
    std::vector<int> &GetEvaluations();
    virtual TgBot::InlineKeyboardMarkup::Ptr GetInlineKeyboard() = 0;
    virtual TgBot::InlineKeyboardMarkup::Ptr GetMenu() = 0;
    virtual TgBot::InlineKeyboardMarkup::Ptr BackButton() = 0;
};
}  // namespace mtd

#endif