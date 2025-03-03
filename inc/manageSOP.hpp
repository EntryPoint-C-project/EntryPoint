#ifndef MANAGESOP_HPP
#define MANAGESOP_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <../DataBase/AllIncludes.hpp>

class ClassForJSONFormat{
    private : 
        std::vector < std::tuple <std::string , std::string , std::string >> vec_subject_name_and_professeion_for_json; 
        int student_id;
    public : 
        std::vector < std::tuple <std::string , std::string , std::string >> GetSubjectsNameAndProfessionForJSON() const {return vec_subject_name_and_professeion_for_json; }
    
        int GetStudenId()const { return student_id; }
    
        void SetStudentId(int new_student_id) {
            student_id = new_student_id; 
        }
        void SetSubjectsNameAndProfessionForJSON(std::vector < std::tuple <std::string , std::string , std::string >> new_vec_subject_name_and_professeion_for_json ){
            vec_subject_name_and_professeion_for_json = new_vec_subject_name_and_professeion_for_json; 
        }
    }; 

namespace sop {

using json = nlohmann::json;

const std::string refreshToken = "";
const std::string clientId = "";
const std::string clientSecret = "";

std::string performHttpRequest(const std::string &url, const std::string &method, const std::string &accessToken, const std::string &postData = "");
std::string refreshAccessToken();
std::string createForm(const std::string &jsonFilePath);
void deleteForm(const std::string &formId);
json readJsonFromFile(const std::string &filePath);
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
json generateQuestionsPerStudent(const ClassForJSONFormat &student);
void addFieldToForm(const std::string &formId, json jsonFile);
std::string getFormUrl(const std::string &formId);

} // namespace sop

#endif // MANAGESOP_HPP
