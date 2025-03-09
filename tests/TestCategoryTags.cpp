#include "../inc/CategoryTags.hpp"
#include "../inc/Categories.hpp"
#include "../inc/Tags.hpp"
#include <pqxx/pqxx>
#include <fmt/core.h>


int main(){
    const std::string conn_str = "dbname=postgres user=postgres password=spelaya_melon hostaddr=127.0.0.1 port=5432";

    try {
        // Подключение к БД
        Categories category;
        category.category_name = "test_category";
        category.filter_id = 1;
        category.required = true;

        fmt::print("\n[CREATE] Создание категории...\n");
        BaseCrud<Categories>::Create(conn, category);
        fmt::print("\u2713 Запись созданА!!!!\n");

        Tags tag;
        tag.tag_name = "test_tag";

        fmt::print("\n[CREATE] Создание тега...\n");
        BaseCrud<Tags>::Create(conn, tag);
        fmt::print("\u2713 Запись созданА!!!!\n");

        CategoryTags category_tag;
        category_tag.category_id = 1;
        category_tag.tag_id = 1;

        fmt::print("\n[CREATE] Создание категории-тега...\n");
        BaseCrud<CategoryTags>::Create(conn, category_tag);
        fmt::print("\u2713 Запись созданА!!!!\n");

        fmt::print("\n[READ] Чтение всех категорий-тегов:\n");
        auto category_tags = BaseCrud<CategoryTags>::Read(conn);
        for (const auto& ct : category_tags) {
            fmt::print("• {}\n", ct);
        }

        fmt::print("\n[UPDATE] Обновление категорий-тегов...\n");
        CategoryTags updated_category_tag = category_tag;
        updated_category_tag.category_id = 2;
        updated_category_tag.tag_id = 2;
        BaseCrud<CategoryTags>::Update(conn, category_tag.category_tag_id , updated_category_tag);
        fmt::print("\u2713 Запись обновлена\n");

        fmt::print("\n[READ] Чтение всех категорий-тегов:\n");
        auto category_tagss = BaseCrud<CategoryTags>::Read(conn);
        for (const auto& ct : category_tagss) {
            fmt::print("• {}\n", ct);
        }

        fmt::print("\n[DELETE] Удаление категорий-тегов...\n");
        BaseCrud<CategoryTags>::Delete(conn, category_tag.category_tag_id);
        fmt::print("\u2713 Запись удалена\n");

        fmt::print("\n[READ] Чтение всех категорий-тегов:\n");
        auto category_tagsss = BaseCrud<CategoryTags>::Read(conn);
        for (const auto& ct : category_tagsss) {
            fmt::print("• {}\n", ct);
        }
    } catch (const std::exception& e) {
        fmt::print("Exception: {}\n", e.what());
    }
}







