//
// Created by Odinaka on 22/04/2024.
//

#include "AdditionalWeatherVariables.h"
#include "Location_management.h"

size_t AdditionalWeatherVariables::writeCallback(void *contents, size_t size, size_t nmemb, string *data) {
    size_t totalSize = size * nmemb;
    data->append((char *)contents, totalSize);
    return totalSize;
}


AdditionalWeatherVariables AdditionalWeatherVariables::FetchDataFromAPI(double latitude, double longitude) {
    CURL *curl = curl_easy_init();
    CURLcode result;
    if (!curl) {
        cerr << "Error initializing curl." << endl;
        // Handle error appropriately
    }

    // Construct the URL using latitude and longitude
    stringstream urlStream;
    urlStream << "https://api.open-meteo.com/v1/forecast?";
    urlStream << "latitude=" << latitude << "&longitude=" << longitude;
    urlStream << "&hourly=temperature_2m,relative_humidity_2m,precipitation,cloud_cover,vapour_pressure_deficit,wind_speed_10m";

    // Convert the URL to a string
    string url = urlStream.str();

    // Set the URL for the curl request
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Perform the curl request
    string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        cerr << "Error performing curl operation: " << curl_easy_strerror(result) << endl;
        // Handle error appropriately
    } else {
        try {

            // Parse JSON response
            json jsonResponse = json::parse(response);
            AdditionalWeatherVariables adi;
            for (size_t i = 0; i < jsonResponse["hourly"]["temperature_2m"].size(); ++i){
                adi.setUvIndex(to_string(jsonResponse["hourly"]["uv_index"][i]));
                adi.setUvIndexClearSky(to_string(jsonResponse["hourly"]["uv_index_clear_sky"][i]));
                adi.setIsDay(to_string(jsonResponse["hourly"]["is_day"][i]));
                adi.setCape(to_string(jsonResponse["hourly"]["cape"][i]));
                adi.setFreezingLevelHeight(to_string(jsonResponse["hourly"]["freezing_level_height"][i]));
                adi.setSunshineDuration(to_string(jsonResponse["hourly"]["sunshine_duration"][i]));

                // Extract other required parameters similarly

                // Construct and return a WeatherForecast object with the retrieved data
                weatherData.push_back(adi);

            }

        } catch (const json::exception& e) {
            cerr << "JSON parsing error: " << e.what() << endl;
            // Handle parsing error appropriately
            // For example, return a default WeatherForecast object or re-throw the exception
        }
    }


    // Clean up the curl session
    curl_easy_cleanup(curl);

    for (int i = 0; i < weatherData.size(); ++i) {
        cout << "Time: " << i << " hours\n";
        cout << "UV Index: " << weatherData[i].getUvIndex() << "\n";
        cout << "UV Index Clear Sky: " << weatherData[i].getUvIndexClearSky() << "\n";
        cout << "Is Day: " << weatherData[i].getIsDay() << "\n";
        cout << "CAPE: " << weatherData[i].getCape() << "\n";
        cout << "Freezing Level Height: " << weatherData[i].getFreezingLevelHeight() << " m\n";
        cout << "Sunshine Duration: " << weatherData[i].getSunshineDuration() << " hours\n\n";
    }
    // Return a default WeatherForecast object or handle the error case
    return AdditionalWeatherVariables();


}

const string &AdditionalWeatherVariables::getUvIndex() const {
    return UVIndex;
}

void AdditionalWeatherVariables::setUvIndex(const string &uvIndex) {
    UVIndex = uvIndex;
}

const string &AdditionalWeatherVariables::getUvIndexClearSky() const {
    return UVIndexClearSky;
}

void AdditionalWeatherVariables::setUvIndexClearSky(const string &uvIndexClearSky) {
    UVIndexClearSky = uvIndexClearSky;
}

const string &AdditionalWeatherVariables::getIsDay() const {
    return IsDay;
}

void AdditionalWeatherVariables::setIsDay(const string &isDay) {
    IsDay = isDay;
}

const string &AdditionalWeatherVariables::getCape() const {
    return Cape;
}

void AdditionalWeatherVariables::setCape(const string &cape) {
    Cape = cape;
}

const string &AdditionalWeatherVariables::getFreezingLevelHeight() const {
    return FreezingLevelHeight;
}

void AdditionalWeatherVariables::setFreezingLevelHeight(const string &freezingLevelHeight) {
    FreezingLevelHeight = freezingLevelHeight;
}

const string &AdditionalWeatherVariables::getSunshineDuration() const {
    return SunshineDuration;
}

void AdditionalWeatherVariables::setSunshineDuration(const string &sunshineDuration) {
    SunshineDuration = sunshineDuration;
}
