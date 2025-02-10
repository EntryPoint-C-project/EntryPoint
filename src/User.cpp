#include "User.hpp"

namespace mtd {
int64_t User::id() const {
    return chat_id;
}
UserRole User::get_role() const {
    return role;
}
}