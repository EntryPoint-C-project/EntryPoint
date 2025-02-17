#include "../inc/manageSOP.hpp"

namespace sop {

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

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    if (totalSize > 0) {
        userp->append((char*)contents, totalSize);
    }
    return totalSize;
}

std::string refreshAccessToken() {
    std::string postData = "grant_type=refresh_token&client_id=" + clientId +
                               "&client_secret=" + clientSecret +
                               "&refresh_token=" + refreshToken;
    std::string response = performHttpRequest("https://oauth2.googleapis.com/token", "POST", "", postData);

    json jsonResponse = json::parse(response);
    if (jsonResponse.contains("access_token")) {
        return jsonResponse["access_token"].get<std::string>();
    } else {
        std::cerr << "Error: 'access_token' not found in response" << std::endl;
        if (jsonResponse.contains("error")) {
            std::cerr << "Error details: " << jsonResponse["error"].dump() << std::endl;
        }
        return "";
    }
}

std::string performHttpRequest(const std::string &url, const std::string &method, const std::string &accessToken, const std::string &postData) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize CURL" << std::endl;
        return "";
    }

    struct curl_slist* headers = nullptr;
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
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return response;
}

std::string createForm(const std::string &jsonFilePath) {
    std::string accessToken = refreshAccessToken();
    if (accessToken.empty()) {
        std::cerr << "Failed to refresh access token" << std::endl;
        return "";
    }

    std::string formTitle = readJsonFromFile(jsonFilePath).dump();
    std::string response = performHttpRequest("https://forms.googleapis.com/v1/forms", "POST", accessToken, formTitle);

    json jsonResponse = json::parse(response);
    if (jsonResponse.contains("formId")) {
        return jsonResponse["formId"].get<std::string>();
    } else {
        std::cerr << "Error: 'formId' not found in response" << std::endl;
        if (jsonResponse.contains("error")) {
            std::cerr << "Error details: " << jsonResponse["error"].dump() << std::endl;
        }
        return "";
    }
}

void addFieldToForm(const std::string &formId, std::string &jsonFilePath) {
    std::string accessToken = refreshAccessToken();
    if (accessToken.empty()) {
        std::cerr << "Failed to refresh access token" << std::endl;
        return;
    }

    std::string formField = readJsonFromFile(jsonFilePath).dump();
    std::string url = "https://forms.googleapis.com/v1/forms/" + formId + ":batchUpdate";
    std::string response = performHttpRequest(url, "POST", accessToken, formField);
}

std::string getFormUrl(const std::string &formId) {
    return "https://docs.google.com/forms/d/" + formId + "/viewform";
}

void deleteForm(const std::string &formId) {
    std::string accessToken = refreshAccessToken();
    if (accessToken.empty()) {
        std::cerr << "Failed to refresh access token" << std::endl;
        return;
    }

    std::string url = "https://forms.googleapis.com/v1/forms/" + formId;
    std::string response = performHttpRequest(url, "DELETE", accessToken);
}

} // namespace sop
