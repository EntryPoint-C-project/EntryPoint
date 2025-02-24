#include "Tutor.hpp"

namespace mtd {
Tutor::Tutor(int64_t chat_id) : User(chat_id, UserRole::TUTOR) {}

TgBot::InlineKeyboardMarkup::Ptr Tutor::GetInlineKeyboard() {
    TgBot::InlineKeyboardMarkup::Ptr inlineKeyboard(new TgBot::InlineKeyboardMarkup);

    // Добавление кнопки для добавления предмета
    TgBot::InlineKeyboardButton::Ptr addSubject(new TgBot::InlineKeyboardButton);
    addSubject->text = "Добавить предмет";
    addSubject->callbackData = "tutor_add_subject";
    inlineKeyboard->inlineKeyboard.push_back({addSubject});

    // Добавление кнопки для добавления людей в группы
    TgBot::InlineKeyboardButton::Ptr addPeople(new TgBot::InlineKeyboardButton);
    addPeople->text = "Добавить людей в группы";
    addPeople->callbackData = "tutor_add_people";
    inlineKeyboard->inlineKeyboard.push_back({addPeople});

    // Добавление кнопки для создания SOP
    TgBot::InlineKeyboardButton::Ptr createSop(new TgBot::InlineKeyboardButton);
    createSop->text = "Создать SOP";
    createSop->callbackData = "tutor_create_sop";
    inlineKeyboard->inlineKeyboard.push_back({createSop});

    TgBot::InlineKeyboardButton::Ptr view_sop(new TgBot::InlineKeyboardButton);
    view_sop->text = "Посмотреть СОП";
    view_sop->callbackData = "tutor_view_sop";
    inlineKeyboard->inlineKeyboard.push_back({view_sop});

    // Добавление кнопки "Назад"
    TgBot::InlineKeyboardButton::Ptr back(new TgBot::InlineKeyboardButton);
    back->text = "🔙 Назад";
    back->callbackData = "tutor_back";
    inlineKeyboard->inlineKeyboard.push_back({back});

    return inlineKeyboard;
}

TgBot::InlineKeyboardMarkup::Ptr Tutor::GetMenu() {
    TgBot::InlineKeyboardMarkup::Ptr inlineKeyboard(new TgBot::InlineKeyboardMarkup);

    // Пример кнопки меню (можно добавить другие кнопки по необходимости)
    TgBot::InlineKeyboardButton::Ptr buttons(new TgBot::InlineKeyboardButton);
    buttons->text = "Меню для куратора";
    buttons->callbackData = "tutor_buttons";
    
    inlineKeyboard->inlineKeyboard.push_back({buttons});
    return inlineKeyboard;
}

TgBot::InlineKeyboardMarkup::Ptr Tutor::BackButton() {
    TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);
    TgBot::InlineKeyboardButton::Ptr button(new TgBot::InlineKeyboardButton);
    button->text = "🔙 Назад";
    button->callbackData = "tutor_back";
    keyboard->inlineKeyboard.push_back({button});
    return keyboard;
}
}
