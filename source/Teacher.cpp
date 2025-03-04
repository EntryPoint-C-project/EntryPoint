#include "Teacher.hpp"

namespace mtd {
Teacher::Teacher(int64_t chat_id) : User(chat_id, UserRole::TEACHER) {
}
TgBot::InlineKeyboardMarkup::Ptr Teacher::GetInlineKeyboard() {
    TgBot::InlineKeyboardMarkup::Ptr inlineKeyboard(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr declaration(new TgBot::InlineKeyboardButton);
    declaration->text = "Уведомление студентам";
    declaration->callbackData = "teacher_declaration";
    inlineKeyboard->inlineKeyboard.push_back({declaration});

    TgBot::InlineKeyboardButton::Ptr back(new TgBot::InlineKeyboardButton);
    back->text = "🔙 Назад";
    back->callbackData = "teacher_back";
    inlineKeyboard->inlineKeyboard.push_back({back});

    return inlineKeyboard;
}

TgBot::InlineKeyboardMarkup::Ptr Teacher::GetMenu() {
    TgBot::InlineKeyboardMarkup::Ptr inlineKeyboard(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr buttons(new TgBot::InlineKeyboardButton);
    buttons->text = "кнопочки";
    buttons->callbackData = "teacher_buttons";

    TgBot::InlineKeyboardButton::Ptr information(new TgBot::InlineKeyboardButton);
    information->text = "Информация";
    information->callbackData = "teachert_information";

    inlineKeyboard->inlineKeyboard.push_back({buttons});
    inlineKeyboard->inlineKeyboard.push_back({information});

    return inlineKeyboard;
}

TgBot::InlineKeyboardMarkup::Ptr Teacher::BackButton() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = "🔙 Назад";
    button->callbackData = "teacher_back";
    keyboard->inlineKeyboard.push_back({button});
    return keyboard;
}
}  // namespace mtd