#include "../inc/manageSOP.hpp"
#include <gtest/gtest.h>

TEST(ConfigTest, EnvVariablesLoadCorrectly) {
  sop::Config config;
  EXPECT_FALSE(config.getClientId().empty());
  EXPECT_FALSE(config.getClientSecret().empty());
  EXPECT_FALSE(config.getRefreshToken().empty());
}

TEST(GenerateFormTest, GeneratesExpectedQuestions) {
  ClassForJSONFormat student;
  std::vector<std::tuple<std::string, std::string, std::string>> params = {
      {"Джонни Деппа", "Математический анализ", "лекции"},
      {"Тома Круза", "Математический анализ", "практик"},
      {"Тома Хэнкса", "Алгебра", "лекции"},
      {"Тома Холланда", "Алгебра", "практик"},
      {"Тома Харди", "Программирование C++", "лекции"},
      {"Леонардо ди Каприо", "Программирование C++", "практик"}};
  student.SetStudentId(1);
  student.SetSubjects(params);

  json result = generateQuestionsPerStudent(student);

  ASSERT_TRUE(result.contains("requests"));
  ASSERT_GT(result["requests"].size(), 0);

  std::map<std::string, int> groupCounters;
  for (const auto &entry : params) {
    groupCounters[std::get<2>(entry)] += 4;
  }

  size_t expected = groupCounters.size();
  for (const auto &[group, count] : groupCounters) {
    expected += count;
  }

  EXPECT_EQ(result["requests"].size(), expected);
}

TEST(HttpIntegrationTest, CreateFormAndAddFields) {
  Config config = Config::getInstance();
  HttpClient httpClient;

  std::string file_path = "json/formTitle.json";
  std::string formId = createForm(file_path, config, httpClient);

  ASSERT_FALSE(formId.empty()) << "Form ID is empty";

  ClassForJSONFormat student;
  std::vector<std::tuple<std::string, std::string, std::string>> params = {
      {"Джонни Деппа", "Математический анализ", "лекции"},
      {"Тома Круза", "Математический анализ", "практик"},
      {"Тома Хэнкса", "Алгебра", "лекции"},
      {"Тома Холланда", "Алгебра", "практик"},
      {"Тома Харди", "Программирование C++", "лекции"},
      {"Леонардо ди Каприо", "Программирование C++", "практик"}};
  student.SetStudentId(1);
  student.SetSubjects(params);

  json question = generateQuestionsPerStudent(student);
  ASSERT_FALSE(question.empty()) << "Generated question JSON is empty";

  addFieldToForm(formId, question, config, httpClient);

  std::string formUrl = getFormUrl(formId);
  ASSERT_FALSE(formUrl.empty());
  ASSERT_NE(formUrl.find("https://docs.google.com/forms/d/"),
            std::string::npos);

  std::cout << "Form created at: " << formUrl << std::endl;
}
