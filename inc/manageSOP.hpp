#ifndef MANAGESOP_HPP
#define MANAGESOP_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

namespace sop {

using json = nlohmann::json;

const std::string refreshToken = "1//0cOYQ-Gkp10-iCgYIARAAGAwSNwF-L9IreQZryzVc8uBz3yUtRDfVRr-U2n2hVu619cXzHBWPlsfM8bK4PvpJGXbXDCDdyH7CHOo";
const std::string clientId = "314611394476-nscobighgst0lhnglrvh45l3nrioth77.apps.googleusercontent.com";
const std::string clientSecret = "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";

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
