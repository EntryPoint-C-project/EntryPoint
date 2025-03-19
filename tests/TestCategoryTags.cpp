#include "../include/CategoryTags.hpp"
#include "../include/Categories.hpp"
#include "../include/Tags.hpp"
#include <pqxx/pqxx>
#include <fmt/core.h>

int main() {
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";

    try {
        pqxx::connection conn(conn_str);

        // Проверка и создание записи в таблице filters
        fmt::print("\n[CREATE] Проверка и создание записи в filters...\n");
        pqxx::work txn(conn);
        pqxx::result result = txn.exec("SELECT 1 FROM filters WHERE filter_id = 1");
        if (result.empty()) {
            txn.exec("INSERT INTO filters (filter_id) VALUES (1)");
            fmt::print("\u2713 Запись в filters создана!!!!\n");
        } else {
            fmt::print("\u2713 Запись в filters уже существует!!!!\n");
        }
        txn.commit();

        // Создание категории
        Categories category;
        category.category_name = "test_category";
        category.filter_id = 1;
        category.required = true;

        fmt::print("\n[CREATE] Создание категории...\n");
        BaseCrud<Categories>::Create(conn, category);
        fmt::print("\u2713 Запись создана!!!!\n");

        // Создание тега
        Tags tag;
        tag.tag_name = "test_tag";

        fmt::print("\n[CREATE] Создание тега...\n");
        BaseCrud<Tags>::Create(conn, tag);
        fmt::print("\u2713 Запись создана!!!!\n");

        // Создание связи категории и тега
        CategoryTags category_tag;
        category_tag.category_id = 1;
        category_tag.tag_id = 1;

        fmt::print("\n[CREATE] Создание категории-тега...\n");
        BaseCrud<CategoryTags>::Create(conn, category_tag);
        fmt::print("\u2713 Запись создана!!!!\n");

        // Обновление связи категории и тега
        fmt::print("\n[UPDATE] Обновление категорий-тегов...\n");
        CategoryTags updated_category_tag;
        updated_category_tag.category_id = 2;
        updated_category_tag.tag_id = 2;
        BaseCrud<CategoryTags>::UpdateLinkingPlates(conn, std::make_pair(category_tag.category_id, category_tag.tag_id), std::make_pair(updated_category_tag.category_id, updated_category_tag.tag_id));
        fmt::print("\u2713 Запись обновлена\n");

        // Удаление связи категории и тега
        fmt::print("\n[DELETE] Удаление категорий-тегов...\n");
        BaseCrud<CategoryTags>::DeleteFromLinkingPlates(conn, std::make_pair(category_tag.category_id, category_tag.tag_id));
        fmt::print("\u2713 Запись удалена\n");

    } catch (const std::exception& e) {
        fmt::print("Exception: {}\n", e.what());
    }
}