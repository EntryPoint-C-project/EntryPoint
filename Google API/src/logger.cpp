#include "logger.hpp"

void Logger::log(const std::string &message) {
  std::lock_guard<std::mutex> lock(mtx);
  auto now = std::chrono::system_clock::now();
  auto now_time_t = std::chrono::system_clock::to_time_t(now);
  char timestamp[20];
  std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S",
                std::localtime(&now_time_t));

  std::string log_message = fmt::format("[{}] {}", timestamp, message);
  if (logFile.is_open()) {
    logFile << log_message;
    logFile.flush();
  }
}