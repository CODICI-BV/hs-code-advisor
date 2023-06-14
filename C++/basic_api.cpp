/*
In C++, we use the libcurl library to make HTTP requests. We define a callback function WriteCallback to handle the response data. Inside the main function, we initialize the necessary variables and perform the request using libcurl.

We set the URL, write callback function, and response data using curl_easy_setopt. We also set the headers using curl_slist and pass it to libcurl with CURLOPT_HTTPHEADER.

After performing the request with curl_easy_perform, we parse the serverOutput as JSON using the nlohmann/json library. Finally, we print the HS code from the parsed JSON.

Note that you need to have libcurl and nlohmann/json libraries installed and properly linked to your C++ project in order to compile and run the code.
*/

#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
{
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

int main()
{
    CURL* curl;
    CURLcode res;
    std::string baseURL = "https://api.fractus-ai.com/api/search";
    std::string searchText = "horse";
    std::string bearerToken = "2|tSWRRcFuIiw7spXvUIuN476I";
    std::string serverOutput;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        std::string url = baseURL + "?q=" + curl_easy_escape(curl, searchText.c_str(), searchText.length());
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &serverOutput);
        curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        std::string authHeader = "Authorization: Bearer " + bearerToken;
        headers = curl_slist_append(headers, authHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        res = curl_easy_perform(curl);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    json json_data = json::parse(serverOutput);
    std::cout << "Found HS code: " << json_data["data"][0]["hs_code"] << std::endl;

    curl_global_cleanup();

    return 0;
}
