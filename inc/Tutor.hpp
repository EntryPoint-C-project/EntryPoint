#ifndef TUTOR_HPP_
#define TUTOR_HPP_

#include "User.hpp"

namespace mtd {
class Tutor : public User {
public:
    Tutor(int64_t chat_id);

    TgBot::InlineKeyboardMarkup::Ptr GetInlineKeyboard() override;
    TgBot::InlineKeyboardMarkup::Ptr GetMenu() override;
    TgBot::InlineKeyboardMarkup::Ptr BackButton() override;
};
}

#endif