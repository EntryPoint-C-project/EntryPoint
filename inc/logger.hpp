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
    log("[ERROR] " + fmt::format(message, args));
  }

  template <typename... Args>
  void warn(const std::string &message, const Args &...args) {
    log("[WARNING] " + fmt::format(message, args));
  }

  template <typename... Args>
  void info(const std::string &message, const Args &...args) {
    log("[INFO] " + fmt::format(message, args));
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