#include "Tutor.hpp"

namespace mtd {
Tutor::Tutor(int64_t chat_id) : User(chat_id, UserRole::TUTOR) {}

TgBot::InlineKeyboardMarkup::Ptr Tutor::get_inline_keyboard() {
    TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(new TgBot::InlineKeyboardMarkup);

    // Добавление кнопки для добавления предмета
    TgBot::InlineKeyboardButton::Ptr add_subject(new TgBot::InlineKeyboardButton);
    add_subject->text = "Добавить предмет";
    add_subject->callbackData = "tutor_add_subject";
    inline_keyboard->inlineKeyboard.push_back({add_subject});

    // Добавление кнопки для добавления людей в группы
    TgBot::InlineKeyboardButton::Ptr add_people(new TgBot::InlineKeyboardButton);
    add_people->text = "Добавить людей в группы";
    add_people->callbackData = "tutor_add_people";
    inline_keyboard->inlineKeyboard.push_back({add_people});

    // Добавление кнопки для создания SOP
    TgBot::InlineKeyboardButton::Ptr create_sop(new TgBot::InlineKeyboardButton);
    create_sop->text = "Создать SOP";
    create_sop->callbackData = "tutor_create_sop";
    inline_keyboard->inlineKeyboard.push_back({create_sop});

    TgBot::InlineKeyboardButton::Ptr view_sop(new TgBot::InlineKeyboardButton);
    view_sop->text = "Посмотреть СОП";
    view_sop->callbackData = "tutor_view_sop";
    inline_keyboard->inlineKeyboard.push_back({view_sop});

    // Добавление кнопки "Назад"
    TgBot::InlineKeyboardButton::Ptr back(new TgBot::InlineKeyboardButton);
    back->text = "🔙 Назад";
    back->callbackData = "tutor_back";
    inline_keyboard->inlineKeyboard.push_back({back});

    return inline_keyboard;
}

TgBot::InlineKeyboardMarkup::Ptr Tutor::get_menu() {
    TgBot::InlineKeyboardMarkup::Ptr inline_keyboard(new TgBot::InlineKeyboardMarkup);

    // Пример кнопки меню (можно добавить другие кнопки по необходимости)
    TgBot::InlineKeyboardButton::Ptr buttons(new TgBot::InlineKeyboardButton);
    buttons->text = "Меню для куратора";
    buttons->callbackData = "tutor_buttons";
    
    inline_keyboard->inlineKeyboard.push_back({buttons});
    return inline_keyboard;
}

TgBot::InlineKeyboardMarkup::Ptr Tutor::back_button() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = "🔙 Назад";
    button->callbackData = "tutor_back";
    keyboard->inlineKeyboard.push_back({button});
    return keyboard;
}
}
