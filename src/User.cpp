#include "User.hpp"

namespace mtd {
int &User::get_step() {
    return step;
}
std::vector<int> &User::get_evaluations() {
    return evaluations;
}
int64_t User::id() const {
    return chat_id;
}
UserRole User::get_role() const {
    return role;
}
UserState &User::get_state() {
    return state;
}
}