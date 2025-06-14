#pragma once
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

class Logger {
public:
  static Logger &getInstance() {
    static Logger instance;
    return instance;
  }

  template <typename... Args>
  void error(const std::string &message, const Args &...args) {
    std::string formatted = fmt::vformat(message, fmt::make_format_args(args...));
    log("[ERROR] " + formatted);
  }

  template <typename... Args>
  void warn(const std::string &message, const Args &...args) {
    std::string formatted = fmt::vformat(message, fmt::make_format_args(args...));
    log("[WARNING] " + formatted);
  }

  template <typename... Args>
  void info(const std::string &message, const Args &...args) {
    std::string formatted = fmt::vformat(message, fmt::make_format_args(args...));
    log("[INFO] " + formatted);
  }

private:
  std::ofstream logFile;
  std::mutex mtx;

  Logger() {
    logFile.open("app.log", std::ios::app);
    if (!logFile.is_open()) {
      std::cerr << "Failed to open log file" << std::endl;
    }
  }

  ~Logger() {
    if (logFile.is_open()) {
      logFile.close();
    }
  }

  void log(const std::string &message);
};
