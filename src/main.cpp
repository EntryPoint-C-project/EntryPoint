#include "../inc/manageSOP.hpp"

int main() {
    std::string file_path = "../json/formTitle.json";
    std::string formId = sop::createForm(file_path);
    std::string question = "../json/formQuestion1.json";
    sop::addFieldToForm(formId, question);
    std::cout << sop::getFormUrl(formId) << '\n';
}