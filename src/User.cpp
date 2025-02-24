#include "User.hpp"

namespace mtd {
int &User::GetStep() {
    return step;
}
std::vector<int> &User::GetEvaluations() {
    return evaluations;
}
int64_t User::id() const {
    return chat_id;
}
UserRole User::GetRole() const {
    return role;
}
UserState &User::GetState() {
    return state;
}
}  // namespace mtd