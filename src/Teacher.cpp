#include "Teacher.hpp"

namespace mtd {
TgBot::InlineKeyboardMarkup::Ptr Teacher::get_inline_keyboard() {
    TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr declaration(new TgBot::InlineKeyboardButton);
    declaration->text = "Уведомление студентам";
    declaration->callbackData = "teacher_declaration";
    inline_keyboard->inlineKeyboard.push_back({declaration});

    TgBot::InlineKeyboardButton::Ptr back(new TgBot::InlineKeyboardButton);
    back->text = "🔙 Назад";
    back->callbackData = "teacher_back";
    inline_keyboard->inlineKeyboard.push_back({back});

    return inline_keyboard; 
}

TgBot::InlineKeyboardMarkup::Ptr Teacher::get_menu() {
    TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr buttons(new TgBot::InlineKeyboardButton);
    buttons->text = "кнопочки";
    buttons->callbackData = "teacher_buttons";

    TgBot::InlineKeyboardButton::Ptr information(new TgBot::InlineKeyboardButton);
    information->text = "Информация";
    information->callbackData = "teachert_information";


    inline_keyboard->inlineKeyboard.push_back({buttons});
    inline_keyboard->inlineKeyboard.push_back({information});

    return inline_keyboard;
}

TgBot::InlineKeyboardMarkup::Ptr Teacher::back_button() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = "🔙 Назад";
    button->callbackData = "teacher_back";
    keyboard->inlineKeyboard.push_back({button});
    return keyboard;
}
}