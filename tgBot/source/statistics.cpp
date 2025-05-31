#include "statistics.hpp"

#include <sstream>

float calculate_average_grade(const std::vector<mtd::LectionFeedback>& lections,
                              const std::vector<mtd::PracticeFeedback>& practices) {
    int total_grade = 0;
    int total_count = 0;

    // Суммируем оценки по лекциям
    for (const auto& lection : lections) {
        total_grade += lection.grade;
        total_count++;
    }

    // Суммируем оценки по практикам
    for (const auto& practice : practices) {
        total_grade += practice.grade;
        total_count++;
    }

    return total_count > 0 ? static_cast<float>(total_grade) / total_count : 0.0f;
}

std::string generate_statistics(const mtd::Subject& subject) {
    std::stringstream ss;

    ss << "Статистика по предмету: " << subject.name_subject << "\n\n";

    ss << "Лекции:\n";
    if (subject.lections_result.empty()) {
        ss << "Нет отзывов по лекциям.\n";
    } else {
        for (const auto& lection : subject.lections_result) {
            ss << "Оценка: " << lection.grade << "\n";
            ss << "Что нравится: " << (lection.advantages.empty() ? "Нет" : lection.advantages)
               << "\n";
            ss << "Что не нравится: "
               << (lection.disadvantages.empty() ? "Нет" : lection.disadvantages) << "\n\n";
        }
    }

    ss << "Практики:\n";
    if (subject.practice_result.empty()) {
        ss << "Нет отзывов по практикам.\n";
    } else {
        for (const auto& practice : subject.practice_result) {
            ss << "Преподаватель: " << practice.name_teacher << "\n";
            ss << "Оценка: " << practice.grade << "\n";
            ss << "Оценка за домашку: " << practice.grade_for_homework << "\n";
            ss << "Что нравится: " << (practice.advantages.empty() ? "Нет" : practice.advantages)
               << "\n";
            ss << "Что не нравится: "
               << (practice.disadvantages.empty() ? "Нет" : practice.disadvantages) << "\n\n";
        }
    }

    if (!subject.comments.empty()) {
        ss << "Комментарии:\n";
        for (const auto& comment : subject.comments) {
            ss << "- " << comment << "\n";
        }
    } else {
        ss << "Нет комментариев.\n";
    }

    float average_grade = calculate_average_grade(subject.lections_result, subject.practice_result);
    ss << "\nСредняя оценка по предмету: " << average_grade << "\n";

    return ss.str();
}
