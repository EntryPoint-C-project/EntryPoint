#ifndef SOP_HPP_
#define SOP_HPP_

#include <string>
#include <vector>
#include <map>
#include <mutex>

namespace mtd {
// эта структура -- кусочек сопа для какого-то предмета
// например, если говорим про ОМП, то это часть типа практика группы 2
// или оценивание лекции 
const int NO_HOMEWORK = -1;
struct Feedback {
    std::string teacher_name;   // имя преподавателя 
    int grade = 0;              // оценка преподавания
    int grade_home_work = -1;   // проверка дз (-1 -- это лекция, нет дз)
    std::string advantages;     // что нравится
    std::string disadvantages;  // что не нравится
    int step = 0; // шаг, на котоором сейчас студент, например 1 -- комментарий
};

struct Subject {
    std::string name_subject;
    std::vector<Feedback> lections_result; // все фидбеки по лекциям
    std::vector<Feedback> practice_result; // по практикам
    std::vector<std::string> comments; // дополнительные комментарии к предмету
};



}  // namespace mtd

#endif