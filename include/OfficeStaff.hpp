#ifndef OFFECESTAFF_HPP_
#define OFFECESTAFF_HPP_

#include "User.hpp"

namespace mtd {
class OfficeStaff : public User {
public:
    OfficeStaff(int64_t chat_id) : User(chat_id, UserRole::OFFICE_STAFF) {}
    TgBot::InlineKeyboardMarkup::Ptr GetInlineKeyboard() override;
    TgBot::InlineKeyboardMarkup::Ptr GetMenu() override;
    TgBot::InlineKeyboardMarkup::Ptr BackButton() override;
};
}  // namespace mtd

#endif
