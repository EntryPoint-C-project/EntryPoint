#include "Student.hpp"

namespace mtd {
TgBot::InlineKeyboardMarkup::Ptr Student::get_inline_keyboard() {
    TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr time_table(new TgBot::InlineKeyboardButton);
    time_table->text = "📅 Расписание";
    time_table->callbackData = "student_time_table";

    TgBot::InlineKeyboardButton::Ptr declaration(new TgBot::InlineKeyboardButton);
    declaration->text = "📢 Объявления";
    declaration->callbackData = "student_declaration";

    TgBot::InlineKeyboardButton::Ptr connect_with_teacher(new TgBot::InlineKeyboardButton);
    connect_with_teacher->text = "📩 Связь с преподавателем";
    connect_with_teacher->callbackData = "student_connect_with_teacher";

    TgBot::InlineKeyboardButton::Ptr help(new TgBot::InlineKeyboardButton);
    help->text = "❓ Помощь";
    help->callbackData = "student_help";

    TgBot::InlineKeyboardButton::Ptr back(new TgBot::InlineKeyboardButton);
    back->text = "🔙 Назад";
    back->callbackData = "student_back";

    inline_keyboard->inlineKeyboard.push_back({time_table});
    inline_keyboard->inlineKeyboard.push_back({declaration});
    inline_keyboard->inlineKeyboard.push_back({connect_with_teacher});
    inline_keyboard->inlineKeyboard.push_back({help});
    inline_keyboard->inlineKeyboard.push_back({back});
    return inline_keyboard;
}

TgBot::InlineKeyboardMarkup::Ptr Student::get_menu() {
    TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr buttons(new TgBot::InlineKeyboardButton);
    buttons->text = "кнопочки";
    buttons->callbackData = "student_buttons";

    TgBot::InlineKeyboardButton::Ptr information(new TgBot::InlineKeyboardButton);
    information->text = "Информация";
    information->callbackData = "student_information";


    inline_keyboard->inlineKeyboard.push_back({buttons});
    inline_keyboard->inlineKeyboard.push_back({information});
    return inline_keyboard;
}

TgBot::InlineKeyboardMarkup::Ptr Student::back_button() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = "🔙 Назад";
    button->callbackData = "student_back";
    keyboard->inlineKeyboard.push_back({button});
    return keyboard;
}
}