#ifndef OFFECESTAFF_HPP_
#define OFFECESTAFF_HPP_

#include <tgbot/tgbot.h>
#include "User.hpp"

namespace mtd {
class OfficeStaff : public User {
public:
    OfficeStaff(int64_t chat_id) : User(chat_id, UserRole::OFFICE_STAFF) {} 
    TgBot::InlineKeyboardMarkup::Ptr get_inline_keyboard() override;
    TgBot::InlineKeyboardMarkup::Ptr get_menu() override;
    TgBot::InlineKeyboardMarkup::Ptr back_button() override;
};
}


#endif
