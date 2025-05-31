#include "Student.hpp"

namespace mtd {
Student::Student(int64_t chat_id) : User(chat_id, UserRole::STUDENT) {
}
TgBot::InlineKeyboardMarkup::Ptr Student::GetInlineKeyboard() {
    TgBot::InlineKeyboardMarkup::Ptr inlineKeyboard(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr timeTable(new TgBot::InlineKeyboardButton);
    timeTable->text = "📅 Расписание";
    timeTable->callbackData = "student_time_table";

    TgBot::InlineKeyboardButton::Ptr declaration(new TgBot::InlineKeyboardButton);
    declaration->text = "📢 Объявления";
    declaration->callbackData = "student_declaration";

    TgBot::InlineKeyboardButton::Ptr connectWithTeacher(new TgBot::InlineKeyboardButton);
    connectWithTeacher->text = "📩 Связь с преподавателем";
    connectWithTeacher->callbackData = "student_connect_with_teacher";

    TgBot::InlineKeyboardButton::Ptr help(new TgBot::InlineKeyboardButton);
    help->text = "❓ Помощь";
    help->callbackData = "student_help";

    TgBot::InlineKeyboardButton::Ptr back(new TgBot::InlineKeyboardButton);
    back->text = "🔙 Назад";
    back->callbackData = "student_back";

    TgBot::InlineKeyboardButton::Ptr sop(new TgBot::InlineKeyboardButton);
    sop->text = "Пройти СОП";
    sop->callbackData = "student_sop";

    inlineKeyboard->inlineKeyboard.push_back({timeTable});
    inlineKeyboard->inlineKeyboard.push_back({declaration});
    inlineKeyboard->inlineKeyboard.push_back({connectWithTeacher});
    inlineKeyboard->inlineKeyboard.push_back({help});
    inlineKeyboard->inlineKeyboard.push_back({sop});
    inlineKeyboard->inlineKeyboard.push_back({back});

    return inlineKeyboard;
}

TgBot::InlineKeyboardMarkup::Ptr Student::GetMenu() {
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

TgBot::InlineKeyboardMarkup::Ptr Student::BackButton() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = "🔙 Назад";
    button->callbackData = "student_back";
    keyboard->inlineKeyboard.push_back({button});
    return keyboard;
}
}  // namespace mtd