# 🚀 EntryPoint

A **Telegram Bot** designed for students, teachers, administration, and educational process organizers.

## 📌 Project Description

EntryPoint is a Telegram bot with an authorization system for different roles in the educational process:

- **Students** — can anonymously evaluate teaching quality and receive important announcements.
- **Teachers & Curators** — can send notifications to students with read confirmation.
- **Administration** — can manage information distribution within the university.

🔹 The bot also allows storing useful subject-related information (links, tables, files, chats).  
🔹 Any student can edit the materials **Wiki-style**, with a change history feature.

---

## 🛠 Installation & Build

### 🔹 1. Clone the repository
```sh
git clone git@github.com:EntryPoint-C-project/EntryPoint.git
cd EntryPoint
# You need to make a telegram-bot token
mkdir build && cd build  
cmake -G Ninja ..
ninja
``` 