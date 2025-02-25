#include "OfficeStaff.hpp"

namespace mtd {
TgBot::InlineKeyboardMarkup::Ptr OfficeStaff::GetInlineKeyboard() {
    TgBot::InlineKeyboardMarkup::Ptr inlineKeyboard(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr timeTable(new TgBot::InlineKeyboardButton);
    timeTable->text = "📅 Расписание";
    timeTable->callbackData = "office_staff_time_table";

    TgBot::InlineKeyboardButton::Ptr declaration(new TgBot::InlineKeyboardButton);
    declaration->text = "📢 Объявления";
    declaration->callbackData = "office_staff_declaration";

    TgBot::InlineKeyboardButton::Ptr connectWithTeacher(new TgBot::InlineKeyboardButton);
    connectWithTeacher->text = "📩 Связь с преподавателем";
    connectWithTeacher->callbackData = "office_staff_connect_with_teacher";

    TgBot::InlineKeyboardButton::Ptr help(new TgBot::InlineKeyboardButton);
    help->text = "❓ Помощь";
    help->callbackData = "office_staff_help";

    // ЗДЕСЬ КАКОЙ_ТО ПИЗДЕЦ
    TgBot::InlineKeyboardButton::Ptr addInfo(new TgBot::InlineKeyboardButton);
    addInfo->text = "Добавить информацию";
    addInfo->callbackData = "office_add_info";

    TgBot::InlineKeyboardButton::Ptr back(new TgBot::InlineKeyboardButton);
    back->text = "🔙 Назад";
    back->callbackData = "office_staff_back";

    inlineKeyboard->inlineKeyboard.push_back({timeTable});
    inlineKeyboard->inlineKeyboard.push_back({declaration});
    inlineKeyboard->inlineKeyboard.push_back({connectWithTeacher});
    inlineKeyboard->inlineKeyboard.push_back({help});
    inlineKeyboard->inlineKeyboard.push_back({addInfo});
    inlineKeyboard->inlineKeyboard.push_back({back});
    return inlineKeyboard;
}

TgBot::InlineKeyboardMarkup::Ptr OfficeStaff::GetMenu() {
    TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr buttons(new TgBot::InlineKeyboardButton);
    buttons->text = "кнопочки";
    buttons->callbackData = "office_staff_buttons";

    TgBot::InlineKeyboardButton::Ptr information(new TgBot::InlineKeyboardButton);
    information->text = "Информация";
    information->callbackData = "office_staff_information";

    inline_keyboard->inlineKeyboard.push_back({buttons});
    inline_keyboard->inlineKeyboard.push_back({information});
    return inline_keyboard;
}

TgBot::InlineKeyboardMarkup::Ptr OfficeStaff::BackButton() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = "🔙 Назад";
    button->callbackData = "office_staff_back";
    keyboard->inlineKeyboard.push_back({button});
    return keyboard;
}
}  // namespace mtd