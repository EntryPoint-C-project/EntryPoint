#ifndef TUTOR_HPP_
#define TUTOR_HPP_

#include "User.hpp"

namespace mtd {
class Tutor : public User {
public:
    Tutor(int64_t chat_id);

    TgBot::InlineKeyboardMarkup::Ptr get_inline_keyboard() override;
    TgBot::InlineKeyboardMarkup::Ptr get_menu() override;
    TgBot::InlineKeyboardMarkup::Ptr back_button() override;
};
}

#endif