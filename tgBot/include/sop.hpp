#ifndef SOP_HPP_
#define SOP_HPP_

#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace mtd {
struct Discipline {
    std::string name_subject;
    std::string lector;
    std::vector<std::string> seminarians;
};

struct Feedback {
    int grade = 0;
    int grade_home_work = -1;
    std::string advantages;
    std::string disadvantages;
    int step = 0;
    int index = 0;
};

struct LectionFeedback {
    int grade;
    std::string advantages;
    std::string disadvantages;
};

struct PracticeFeedback {
    std::string name_teacher;
    int grade;
    int grade_for_homework;
    std::string advantages;
    std::string disadvantages;
};

struct Subject {
    std::string name_subject;
    std::vector<LectionFeedback> lections_result;
    std::vector<PracticeFeedback> practice_result;
    std::vector<std::string> comments;
};
}  // namespace mtd

#endif