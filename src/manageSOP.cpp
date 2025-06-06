#include "../inc/manageSOP.hpp"

namespace sop {

bool comp(const Teacher &lhs, const Teacher &rhs) {
  if (lhs.subject_name != rhs.subject_name) {
    return lhs.subject_name < rhs.subject_name;
  }
  return lhs.his_roles[0] < rhs.his_roles[0];
}

std::string HttpClient::performHttpRequest(const std::string &url,
                                           const std::string &method,
                                           const std::string &accessToken,
                                           const std::string &postData) {
  if (!curl) {
    std::cerr << "Failed to initialize CURL" << std::endl;
    return "";
  }

  struct curl_slist *headers = nullptr;
  headers = curl_slist_append(headers, "Content-Type: application/json");
  std::string authorizationHeader = "Authorization: Bearer " + accessToken;
  headers = curl_slist_append(headers, authorizationHeader.c_str());

  if (!accessToken.empty()) {
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  }

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

  if (method == "POST") {
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    if (!postData.empty()) {
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    }
  } else if (method == "DELETE") {
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
  } else if (method == "GET") {
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
  }

  std::string response;
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
  }

  curl_slist_free_all(headers);
  return response;
}

size_t HttpClient::WriteCallback(void *contents, size_t size, size_t nmemb,
                                 std::string *userp) {
  size_t totalSize = size * nmemb;
  if (totalSize > 0) {
    userp->append((char *)contents, totalSize);
  }
  return totalSize;
}

json generateQuestionsPerStudent(pqxx::transaction_base &txn, int student_id) {
  json form;
  form["requests"] = json::array();

  json jsonScaleQuestion, jsonOverallQuestion, header;
  try {
    jsonScaleQuestion = readJsonFromFile("json/scaleQuestion.json");
    jsonOverallQuestion = readJsonFromFile("json/overallQuestion.json");
    header = readJsonFromFile("json/headerOfQuestionsBlock.json");
  } catch (const std::exception &e) {
    std::cerr << "Error reading JSON templates: " << e.what() << std::endl;
    return {};
  }

  std::vector<Teacher> teachers = GetAllTeachersForStudent(txn, student_id);
  sort(teachers.begin(), teachers.end(), comp);
  std::string currentHeader;

  for (const auto &teacher : teachers) {
    const std::string &teacherName =
        teacher.first_name + " " + teacher.last_name;
    const std::string &subjectName = teacher.subject_name;
    const std::string &groupName = teacher.his_roles[0];

    try {
      if (currentHeader != subjectName) {
        currentHeader = subjectName;
        header["createItem"]["item"]["title"] = subjectName;
        form["requests"].push_back(header);
      }

      std::string question =
          "Оцените качество " + groupName + " " + teacherName + " от 1 до 10";
      json scaleQuestion = jsonScaleQuestion;
      scaleQuestion["createItem"]["item"]["title"] = question;
      form["requests"].push_back(scaleQuestion);

      json overallQ1 = jsonOverallQuestion;
      overallQ1["createItem"]["item"]["title"] =
          "Что вам понравилось в преподавании " + teacherName + "?";
      form["requests"].push_back(overallQ1);

      json overallQ2 = jsonOverallQuestion;
      overallQ2["createItem"]["item"]["title"] =
          "Что вам не понравилось в преподавании " + teacherName + "?";
      form["requests"].push_back(overallQ2);

      json overallQ3 = jsonOverallQuestion;
      overallQ3["createItem"]["item"]["title"] =
          "Есть ли у вас какие-нибудь пожелания по поводу преподавания " +
          teacherName + "?";
      form["requests"].push_back(overallQ3);
    } catch (const std::exception &e) {
      std::cerr << "Error building questions for " << teacherName << ": "
                << e.what() << std::endl;
    }
  }

  std::size_t index = 0;
  for (auto &request : form["requests"]) {
    try {
      request["createItem"]["location"]["index"] = index++;
    } catch (const std::exception &e) {
      std::cerr << "Error setting index for form request: " << e.what()
                << std::endl;
    }
  }

  return form;
}

json readJsonFromFile(const std::string &filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "Failed to open file\n";
  }
  json jsonData;
  file >> jsonData;
  file.close();
  return jsonData;
}

std::string refreshAccessToken(Config &config, HttpClient &httpClient) {
  auto now = std::chrono::steady_clock::now();
  if (std::chrono::duration_cast<std::chrono::seconds>(
          now - config.getLastUpdateTime()) < config.getTokenExpirationTime()) {
    return config.getAccessToken();
  }
  std::string postData =
      "grant_type=refresh_token&client_id=" + config.getClientId() +
      "&client_secret=" + config.getClientSecret() +
      "&refresh_token=" + config.getRefreshToken();
  std::string response = httpClient.performHttpRequest(
      "https://oauth2.googleapis.com/token", "POST", "", postData);

  try {
    json jsonResponse = json::parse(response);
    if (jsonResponse.contains("access_token")) {
      config.setLastUpdateTime();
      std::string accessToken = jsonResponse["access_token"].get<std::string>();
      return config.setAccessToken(accessToken);
    } else {
      std::cerr << "Error: 'access_token' not found in response" << std::endl;
      if (jsonResponse.contains("error")) {
        std::cerr << "Error details: " << jsonResponse["error"].dump()
                  << std::endl;
      }
      return "";
    }
  } catch (const std::exception &e) {
    std::cerr << "JSON parsing error: " << e.what() << std::endl;
    return json();
  }
}

std::string createForm(const std::string &jsonFilePath, Config &config,
                       HttpClient &httpClient) {
  std::string accessToken = refreshAccessToken(config, httpClient);
  if (accessToken.empty()) {
    std::cerr << "Failed to refresh access token" << std::endl;
    return "";
  }

  std::string formTitle = readJsonFromFile(jsonFilePath).dump();
  std::string response = httpClient.performHttpRequest(
      "https://forms.googleapis.com/v1/forms", "POST", accessToken, formTitle);

  try {
    json jsonResponse = json::parse(response);
    if (jsonResponse.contains("formId")) {
      return jsonResponse["formId"].get<std::string>();
    } else {
      std::cerr << "Error: 'formId' not found in response" << std::endl;
      if (jsonResponse.contains("error")) {
        std::cerr << "Error details: " << jsonResponse["error"].dump()
                  << std::endl;
      }
      return "";
    }
  } catch (const std::exception &e) {
    std::cerr << "JSON parsing error: " << e.what() << std::endl;
    return json();
  }
}

void addFieldToForm(const std::string &formId, json jsonFile, Config &config,
                    HttpClient &httpClient) {
  std::string accessToken = refreshAccessToken(config, httpClient);
  if (accessToken.empty()) {
    std::cerr << "Failed to refresh access token" << std::endl;
    return;
  }
  std::string questionForm = jsonFile.dump();
  std::string url =
      "https://forms.googleapis.com/v1/forms/" + formId + ":batchUpdate";
  std::string response =
      httpClient.performHttpRequest(url, "POST", accessToken, questionForm);
  try {
    json responseJson = json::parse(response);
    if (responseJson.contains("error")) {
      std::cerr << "Error: " << responseJson.dump() << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "JSON parsing error: " << e.what() << std::endl;
  }
}

std::string getFormUrl(const std::string &formId) {
  return "https://docs.google.com/forms/d/" + formId + "/viewform";
}

void deleteForm(const std::string &formId, Config &config,
                HttpClient &httpClient) {
  std::string accessToken = refreshAccessToken(config, httpClient);
  if (accessToken.empty()) {
    std::cerr << "Failed to refresh access token" << std::endl;
    return;
  }

  std::string url = "https://forms.googleapis.com/v1/forms/" + formId;
  std::string response =
      httpClient.performHttpRequest(url, "DELETE", accessToken);
}

json getFormResponses(const std::string &formId, Config &config,
                      HttpClient &httpClient) {
  std::string accessToken = refreshAccessToken(config, httpClient);
  if (accessToken.empty()) {
    std::cerr << "Failed to refresh access token" << std::endl;
    return json();
  }

  std::string url =
      "https://forms.googleapis.com/v1/forms/" + formId + "/responses";
  std::string response =
      httpClient.performHttpRequest(url, "GET", accessToken, "");

  try {
    json jsonResponse = json::parse(response);
    if (jsonResponse.contains("responses")) {
      return jsonResponse;
    } else {
      std::cerr << "Error: 'responses' not found in response" << std::endl;
      if (jsonResponse.contains("error")) {
        std::cerr << "Error details: " << jsonResponse["error"].dump()
                  << std::endl;
      }
      return json();
    }
  } catch (const std::exception &e) {
    std::cerr << "JSON parsing error: " << e.what() << std::endl;
    return json();
  }
}

json readGoogleTable(const std::string &tableName, const std::string &range,
                     Config &config, HttpClient &httpClient) {
  std::string accessToken = refreshAccessToken(config, httpClient);
  if (accessToken.empty()) {
    std::cerr << "Failed to refresh access token" << std::endl;
    return json();
  }

  std::string url = "https://sheets.googleapis.com/v4/spreadsheets/" +
                    tableName + "/values:batchGet?ranges=" + range;
  std::string response =
      httpClient.performHttpRequest(url, "GET", accessToken, "");

  try {
    json jsonResponse = json::parse(response);
    if (jsonResponse.contains("valueRanges")) {
      return jsonResponse;
    } else {
      std::cerr << "Error: 'valueRanges' not found in response" << std::endl;
      if (jsonResponse.contains("error")) {
        std::cerr << "Error details: " << jsonResponse["error"].dump()
                  << std::endl;
      }
      return json();
    }
  } catch (const std::exception &e) {
    std::cerr << "JSON parsing error: " << e.what() << std::endl;
    return json();
  }
}

void fillDataBaseWithStudents(pqxx::transaction_base &txn,
                              const std::string &tableName, int cnt_students,
                              Config &config, HttpClient &httpClient) {
  std::string range = "A2:E" + std::to_string(cnt_students + 1);
  json StudentTable = readGoogleTable(tableName, range, config, httpClient);
  if (StudentTable.contains("valueRanges")) {
    auto valueRanges = StudentTable["valueRanges"];
    if (!valueRanges.contains("values")) {
      std::cerr << "Error 'values' not found in table" << std::endl;
      return;
    }
    Person person;
    for (int i = 1; i <= cnt_students; i++) {
      const auto row = valueRanges["values"][i];
      bool isEmpty = true;
      for (const auto &cell : row) {
        if (!cell.get<std::string>().empty()) {
          isEmpty = false;
          break;
        }
      }
      if (!isEmpty) {
        person.last_name = row[0];
        person.first_name = row[1];
        person.snils = row[2];
        person.tg_nick = row[3];
        person.people_group_name = row[4];
      }
      CreatePersonWithParams(txn, person);
    }
  }
}

std::string Config::getEnvVar(const std::string &key) {
  const char *value = std::getenv(key.c_str());
  if (value == nullptr) {
    std::cerr << "Unable to get: " + key + '\n';
    return "";
  } else {
    return std::string(value);
  }
}

Config::Config() {
  clientId = getEnvVar("GOOGLE_CLIENT_ID");
  clientSecret = getEnvVar("GOOGLE_CLIENT_SECRET");
  refreshToken = getEnvVar("GOOGLE_REFRESH_TOKEN");
}

} // namespace sop
