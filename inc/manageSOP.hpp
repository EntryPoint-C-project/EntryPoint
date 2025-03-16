#ifndef MANAGESOP_HPP
#define MANAGESOP_HPP

#include <chrono>
#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <pqxx/pqxx>
#include <string>
class ClassForJSONFormat {
private:
  std::vector<std::tuple<std::string, std::string, std::string>> subjects;
  int student_id;

public:
  std::vector<std::tuple<std::string, std::string, std::string>>
  GetSubjects() const {
    return subjects;
  }

  int GetStudenId() const { return student_id; }

  void SetStudentId(int new_student_id) { student_id = new_student_id; }

  void
  AddSubject(std::tuple<std::string, std::string, std::string> new_subject) {
    subjects.push_back(new_subject);
  }

  void SetSubjects(
      const std::vector<std::tuple<std::string, std::string, std::string>>
          &params) {
    subjects = params;
  }
};

namespace sop {

using json = nlohmann::json;

class Config {
public:
  static Config &getInstance() {
    static Config instance;
    return instance;
  }

  std::string getClientId() const { return clientId; }

  std::string getClientSecret() const { return clientSecret; }

  std::string getRefreshToken() const { return refreshToken; }

  std::string getAccessToken() const { return accessToken; }

  std::chrono::steady_clock::time_point getLastUpdateTime() const {
    return lastUpdateTime;
  }

  std::chrono::seconds getTokenExpirationTime() const {
    return TOKEN_EXPIRATION_TIME;
  }

  std::string setAccessToken(std::string &accessToken_) {
    return accessToken = accessToken_;
  }

  void setLastUpdateTime() {
    lastUpdateTime = std::chrono::steady_clock::now();
  }

private:
  std::string getEnvVar(const std::string &key);
  Config();
  std::string clientId;
  std::string clientSecret;
  std::string refreshToken;
  std::string accessToken;
  std::chrono::steady_clock::time_point lastUpdateTime;
  const std::chrono::seconds TOKEN_EXPIRATION_TIME{3600};
};

class HttpClient {
public:
  HttpClient() {
    curl = curl_easy_init();
    if (!curl) {
      throw std::runtime_error("Failed to initialize CURL");
      curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
      curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 120L);
      curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 60L);
    }
  }

  ~HttpClient() {
    if (curl) {
      curl_easy_cleanup(curl);
    }
  }

  std::string performHttpRequest(const std::string &url,
                                 const std::string &method,
                                 const std::string &accessToken,
                                 const std::string &postData = "");

private:
  CURL *curl;
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                              std::string *userp);
};

std::vector<ClassForJSONFormat> getStudents(pqxx::connection &conn);
std::string refreshAccessToken(Config &config, HttpClient &httpClient);
std::string createForm(const std::string &jsonFilePath, Config &config,
                       HttpClient &httpClient);
void deleteForm(const std::string &formId, Config &config);
json readJsonFromFile(const std::string &filePath);
json generateQuestionsPerStudent(const ClassForJSONFormat &student);
void addFieldToForm(const std::string &formId, json jsonFile, Config &config,
                    HttpClient &httpClient);
std::string getFormUrl(const std::string &formId);
} // namespace sop

#endif // MANAGESOP_HPP
