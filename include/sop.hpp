#ifndef SOP_HPP_
#define SOP_HPP_

#include <string>
#include <vector>
#include <map>
#include <mutex>

namespace mtd {
struct Discipline {
    std::string name_subject = "ОМП";
    std::string lector = "Сайфулин Д.Т";
    std::vector<std::string> seminarians = {"Сайфулин Д.Т.", "Галоев И.Б.", "Иванцов И.С."};
};
// эта структура -- кусочек сопа для какого-то предмета
// например, если говорим про ОМП, то это часть типа практика группы 2
// или оценивание лекции 
/*
    Данная структура находится в каждого студента в классе,
    он заполняет чать сопа, из этой структуры все перекидывается в другие две (которые ниже),
    потом в эту структуру записываются новые данные (у каждого студента своя)
*/
struct Feedback {
    int grade = 0;              // оценка преподавания
    int grade_home_work = -1;   // проверка дз (-1 -- это лекция, нет дз)
    std::string advantages;     // что нравится
    std::string disadvantages;  // что не нравится
    int step = 0; // Вроде бесполезная херня, но лучше пока не трогать 
    int index = 0; // Чтобы итерироваться по практикам
};

// Для каждого студента саздается одна такая по каждому прежмету
struct LectionFeedback {
    int grade;
    std::string advantages;     // что нравится
    std::string disadvantages;  // что не нравится
};

// таки создается для каждого студента столько, сколько всего групп
struct PracticeFeedback {
    std::string name_teacher;
    int grade;
    int grade_for_homework;
    std::string advantages;     // что нравится
    std::string disadvantages;  // что не нравится
};

struct Subject {
    std::string name_subject;
    std::vector<LectionFeedback> lections_result; // все фидбеки по лекциям
    std::vector<PracticeFeedback> practice_result; // по практикам
    std::vector<std::string> comments; // дополнительные комментарии к предмету
};

// Если ты это читаешь, то искренне сочувствую тебе. Может, тебе удастся что-то понять

}  // namespace mtd

#endif