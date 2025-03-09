#ifndef MANAGESOP_HPP
#define MANAGESOP_HPP

#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
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

private:
  std::string getEnvVar(const std::string &key);
  Config();
  std::string clientId;
  std::string clientSecret;
  std::string refreshToken;
};

std::string performHttpRequest(const std::string &url,
                               const std::string &method,
                               const std::string &accessToken,
                               const std::string &postData = "");
std::string refreshAccessToken(const Config &config);
std::string createForm(const std::string &jsonFilePath, const Config &config);
void deleteForm(const std::string &formId, const Config &config);
json readJsonFromFile(const std::string &filePath);
size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                     std::string *userp);
json generateQuestionsPerStudent(const ClassForJSONFormat &student);
void addFieldToForm(const std::string &formId, json jsonFile,
                    const Config &config);
std::string getFormUrl(const std::string &formId);
} // namespace sop

#endif // MANAGESOP_HPP
