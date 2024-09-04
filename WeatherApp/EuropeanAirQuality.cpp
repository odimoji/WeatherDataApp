//
// Created by Odinaka on 22/04/2024.
//

#include "EuropeanAirQuality.h"
#include "Location_management.h"


size_t EuropeanAirQuality::writeCallback(void *contents, size_t size, size_t nmemb, string *data) {
    size_t totalSize = size * nmemb;
    data->append((char *)contents, totalSize);
    return totalSize;
}


EuropeanAirQuality EuropeanAirQuality::FetchDataFromAPI(double latitude, double longitude) {
    CURL *curl = curl_easy_init();
    CURLcode result;
    if (!curl) {
        cerr << "Error initializing curl." << endl;
        // Handle error appropriately
    }

    stringstream urlStream;
    urlStream << "https://air-quality-api.open-meteo.com/v1/air-quality?";
    urlStream << "latitude=" << latitude << "&longitude=" << longitude;
    urlStream << "&hourly=european_aqi,european_aqi_pm2_5,european_aqi_pm10,european_aqi_nitrogen_dioxide,european_aqi_ozone,european_aqi_sulphur_dioxide";
    string url = urlStream.str();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        cerr << "Error performing curl operation: " << curl_easy_strerror(result) << endl;
        // Handle error appropriately
    } else {
        try {
            json jsonResponse = json::parse(response);
            EuropeanAirQuality eaq;
            for (size_t i = 0; i < jsonResponse["hourly"]["european_aqi_pm10"].size(); ++i) {
                eaq.setPm10(to_string(jsonResponse["hourly"]["european_aqi_pm10"]));
                eaq.setPm25(to_string(jsonResponse["hourly"]["european_aqi_pm2_5"]));
                eaq.setCarbonMonoxide(to_string(jsonResponse["hourly"]["european_aqi_carbon_monoxide"]));
                eaq.setNitrogenDioxide(to_string(jsonResponse["hourly"]["european_aqi_nitrogen_dioxide"]));
                eaq.setSulphurDioxide(to_string(jsonResponse["hourly"]["european_aqi_sulphur_dioxide"]));
                eaq.setOzone(to_string(jsonResponse["hourly"]["european_aqi_ozone"]));

                weatherData.push_back(eaq);
            }


        } catch (const json::exception& e) {
            cerr << "JSON parsing error: " << e.what() << endl;
            // Handle parsing error appropriately
            // For example, return a default AirQuality object or re-throw the exception
        }


    }
    curl_easy_cleanup(curl);

    for (size_t i = 0; i < weatherData.size(); ++i) {
        cout << "Air Quality Data:" << endl;
        cout << "PM10: " << weatherData[i].getPm10() << endl;
        cout << "PM25: " <<  weatherData[i].getPm25() << endl;
        cout << "Carbon Monoxide: " <<  weatherData[i].getCarbonMonoxide() << endl;
        cout << "Nitrogen Dioxide: " <<  weatherData[i].getNitrogenDioxide() << endl;
        cout << "Sulphur Dioxide: " <<  weatherData[i].getSulphurDioxide() << endl;
        cout << "Ozone: " <<  weatherData[i].getOzone() << endl;
    }

    return EuropeanAirQuality(); // Return a default AirQuality object or handle the error case
}


const string &EuropeanAirQuality::getPm10() const {
    return pm10;
}

void EuropeanAirQuality::setPm10(const string &pm10) {
    EuropeanAirQuality::pm10 = pm10;
}

const string &EuropeanAirQuality::getPm25() const {
    return pm25;
}

void EuropeanAirQuality::setPm25(const string &pm25) {
    EuropeanAirQuality::pm25 = pm25;
}

const string &EuropeanAirQuality::getCarbonMonoxide() const {
    return carbonMonoxide;
}

void EuropeanAirQuality::setCarbonMonoxide(const string &carbonMonoxide) {
    EuropeanAirQuality::carbonMonoxide = carbonMonoxide;
}

const string &EuropeanAirQuality::getNitrogenDioxide() const {
    return nitrogenDioxide;
}

void EuropeanAirQuality::setNitrogenDioxide(const string &nitrogenDioxide) {
    EuropeanAirQuality::nitrogenDioxide = nitrogenDioxide;
}

const string &EuropeanAirQuality::getSulphurDioxide() const {
    return sulphurDioxide;
}

void EuropeanAirQuality::setSulphurDioxide(const string &sulphurDioxide) {
    EuropeanAirQuality::sulphurDioxide = sulphurDioxide;
}

const string &EuropeanAirQuality::getOzone() const {
    return ozone;
}

void EuropeanAirQuality::setOzone(const string &ozone) {
    EuropeanAirQuality::ozone = ozone;
}
