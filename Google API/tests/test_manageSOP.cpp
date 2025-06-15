#include <gtest/gtest.h>

#include "../inc/manageSOP.hpp"

TEST(ConfigTest, EnvVariablesLoadCorrectly) {
    sop::Config config = sop::Config::getInstance();
    EXPECT_FALSE(config.getClientId().empty());
    EXPECT_FALSE(config.getClientSecret().empty());
    EXPECT_FALSE(config.getRefreshToken().empty());
}

using json = nlohmann::json;

TEST(GenerateFormTest, GeneratesExpectedQuestions) {
    ClassForJSONFormat student;
    std::vector<std::tuple<std::string, std::string, std::string>> params
        = {{"Джонни Деппа", "Математический анализ", "лекции"},
           {"Тома Круза", "Математический анализ", "практик"},
           {"Тома Хэнкса", "Алгебра", "лекции"},
           {"Тома Холланда", "Алгебра", "практик"},
           {"Тома Харди", "Программирование C++", "лекции"},
           {"Леонардо ди Каприо", "Программирование C++", "практик"}};
    student.SetStudentId(1);
    student.SetSubjects(params);

    json result = sop::generateQuestionsPerStudent(student);

    ASSERT_TRUE(result.contains("requests"));
    ASSERT_GT(result["requests"].size(), 0);

    size_t expected = 0;
    std::string lastHeader;
    for (const auto &entry : params) {
        expected += 4;
        if (lastHeader != std::get<1>(entry)) {
            lastHeader = std::get<1>(entry);
            expected++;
        }
    }

    EXPECT_EQ(result["requests"].size(), expected);
}

TEST(HttpIntegrationTest, CreateFormAndAddFields) {
    sop::Config config = sop::Config::getInstance();
    sop::HttpClient httpClient;

    std::string file_path = "json/formTitle.json";
    std::string formId = createForm(file_path, config, httpClient);

    ASSERT_FALSE(formId.empty()) << "Form ID is empty";

    ClassForJSONFormat student;
    std::vector<std::tuple<std::string, std::string, std::string>> params
        = {{"Джонни Деппа", "Математический анализ", "лекции"},
           {"Тома Круза", "Математический анализ", "практик"},
           {"Тома Хэнкса", "Алгебра", "лекции"},
           {"Тома Холланда", "Алгебра", "практик"},
           {"Тома Харди", "Программирование C++", "лекции"},
           {"Леонардо ди Каприо", "Программирование C++", "практик"}};
    student.SetStudentId(1);
    student.SetSubjects(params);

    json question = sop::generateQuestionsPerStudent(student);
    ASSERT_FALSE(question.empty()) << "Generated question JSON is empty";

    sop::addFieldToForm(formId, question, config, httpClient);

    std::string formUrl = sop::getFormUrl(formId);
    ASSERT_FALSE(formUrl.empty());
    ASSERT_NE(formUrl.find("https://docs.google.com/forms/d/"), std::string::npos);

    std::cout << "Form created at: " << formUrl << std::endl;
}
