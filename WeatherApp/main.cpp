#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
#include "Location_management.h"
#include "MainMenu.h"
#include "WeatherForecast.h"


using Json = nlohmann::json;
using namespace std;


void fetchDataFromAPI() {
    CURL *curl = curl_easy_init();
    CURLcode result;
    if (!curl) {
        cerr << "Error initializing curl." << endl;
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.open-meteo.com/v1/forecast?latitude=52.52&longitude=13.41&current=temperature_2m,wind_speed_10m&hourly=temperature_2m,relative_humidity_2m,wind_speed_10m");

    result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        cerr << "Error performing curl operation: " << curl_easy_strerror(result) << endl;
        return;
    }

    curl_easy_cleanup(curl);
}

/*

void queryApi(const std::string& city, const std::string& country) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl = curl_easy_init();
    if (curl) {
        // API endpoint URL
        std::string url = "https://api.example.com/data";

        // Construct the query URL with parameters
        std::string queryUrl = url + "?city=" + city + "&country=" + country;

        // Set the URL to query
        curl_easy_setopt(curl, CURLOPT_URL, queryUrl.c_str());

        // Perform the HTTP GET request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize libcurl" << std::endl;
    }
    // Cleanup libcurl
    curl_global_cleanup();
}
*/

int main() {


    MainMenu mm;
    mm.menu();

   /* Location_management lm;

    lm.menu();
    Location_management location = lm.queryLocation(lm.getCity(), lm.getCountry());
*/
    return 0;

}



