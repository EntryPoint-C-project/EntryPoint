#ifndef MANAGESOP_HPP
#define MANAGESOP_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

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
void addFieldToForm(const std::string &formId, std::string &jsonFilePath);
std::string getFormUrl(const std::string &formId);

} // namespace sop

#endif // MANAGESOP_HPP
