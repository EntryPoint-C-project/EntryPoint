#include "../inc/manageSOP.hpp"
#include <vector>

int main() {
    sop::Config config = sop::Config::getInstance();
    std::string file_path = "json/formTitle.json";
    std::string formId = sop::createForm(file_path, config);
  ClassForJSONFormat student;
  std::vector<std::tuple<std::string, std::string, std::string>> params;
  params.emplace_back(
      std::make_tuple("Джонни Деппа", "Математический анализ", "лекции"));
  params.emplace_back(
      std::make_tuple("Тома Круза", "Математический анализ", "практик"));
  params.emplace_back(std::make_tuple("Тома Хэнкса", "Алгебра", "лекции"));
  params.emplace_back(std::make_tuple("Тома Холланда", "Алгебра", "практик"));
  params.emplace_back(
      std::make_tuple("Тома Харди", "Программирование C++", "лекции"));
  params.emplace_back(
      std::make_tuple("Леонардо ди Каприо", "Программирование C++", "практик"));
  student.SetStudentId(1);
  student.SetSubjects(params);
  nlohmann::json question = sop::generateQuestionsPerStudent(student);
  std::cout << question.dump() << '\n';
  sop::addFieldToForm(formId, question, config);
  std::cout << sop::getFormUrl(formId) << '\n';
}