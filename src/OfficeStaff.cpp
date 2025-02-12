#include "OfficeStaff.hpp"

namespace mtd {
TgBot::InlineKeyboardMarkup::Ptr OfficeStaff::get_inline_keyboard() {
    TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr time_table(new TgBot::InlineKeyboardButton);
    time_table->text = "📅 Расписание";
    time_table->callbackData = "office_staff_time_table";

    TgBot::InlineKeyboardButton::Ptr declaration(new TgBot::InlineKeyboardButton);
    declaration->text = "📢 Объявления";
    declaration->callbackData = "office_staff_declaration";

    TgBot::InlineKeyboardButton::Ptr connect_with_teacher(new TgBot::InlineKeyboardButton);
    connect_with_teacher->text = "📩 Связь с преподавателем";
    connect_with_teacher->callbackData = "office_staff_connect_with_teacher";

    TgBot::InlineKeyboardButton::Ptr help(new TgBot::InlineKeyboardButton);
    help->text = "❓ Помощь";
    help->callbackData = "office_staff_help";

    // ЗДЕСЬ КАКОЙ_ТО ПИЗДЕЦ
    // TgBot::InlineKeyboardButton::Ptr add_info(new TgBot::InlineKeyboardButton);
    // help->text = "Добавить информацию";
    // help->callbackData = "office_add_info";

    TgBot::InlineKeyboardButton::Ptr back(new TgBot::InlineKeyboardButton);
    back->text = "🔙 Назад";
    back->callbackData = "office_staff_back";

    inline_keyboard->inlineKeyboard.push_back({time_table});
    inline_keyboard->inlineKeyboard.push_back({declaration});
    inline_keyboard->inlineKeyboard.push_back({connect_with_teacher});
    inline_keyboard->inlineKeyboard.push_back({help});
    inline_keyboard->inlineKeyboard.push_back({back});
    // inline_keyboard->inlineKeyboard.push_back({add_info});
    std::cout << "1234567\n";
    return inline_keyboard;
}

TgBot::InlineKeyboardMarkup::Ptr OfficeStaff::get_menu() {
    TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr buttons(new TgBot::InlineKeyboardButton);
    buttons->text = "кнопочки";
    buttons->callbackData = "office_staff_buttons";

    TgBot::InlineKeyboardButton::Ptr information(new TgBot::InlineKeyboardButton);
    information->text = "Информация";
    information->callbackData = "office_staff_information";


    inline_keyboard->inlineKeyboard.push_back({buttons});
    inline_keyboard->inlineKeyboard.push_back({information});
    std::cout << "=====\n";
    return inline_keyboard;
}

TgBot::InlineKeyboardMarkup::Ptr OfficeStaff::back_button() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = "🔙 Назад";
    button->callbackData = "office_staff_back";
    keyboard->inlineKeyboard.push_back({button});
    return keyboard;
}
}