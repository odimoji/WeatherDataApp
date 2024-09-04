
//
// Created by Odinaka on 22/04/2024.
//

#ifndef UNTITLED7_HISTORICALWEATHER_H
#define UNTITLED7_HISTORICALWEATHER_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <conio.h>
#include <curl/curl.h>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;


class HistoricalWeather {
private:
    double temperature;
    double humidity;
    double precipitation;
    double cloudCover;
    double vapourPressureDeficit;
    double windSpeed;

public:
    double getTemperature() const;

    void setTemperature(double temperature);

    double getHumidity() const;

    void setHumidity(double humidity);

    double getPrecipitation() const;

    void setPrecipitation(double precipitation);

    double getCloudCover() const;

    void setCloudCover(double cloudCover);

    double getVapourPressureDeficit() const;

    void setVapourPressureDeficit(double vapourPressureDeficit);

    double getWindSpeed() const;

    void setWindSpeed(double windSpeed);

private:
    vector<HistoricalWeather> weatherData;


public:
    static size_t writeCallback( void*, size_t,size_t, string*);
    HistoricalWeather(double, double, double , double, double, double);
    HistoricalWeather();
    void menu();
    HistoricalWeather FetchDataFromAPI(double, double);
    HistoricalWeather BasicHistoricalWeather();
    HistoricalWeather HistoricalWeatherAdvanced();
    HistoricalWeather AdditionalWeatherInformation();


};


#endif //UNTITLED7_HISTORICALWEATHER_H
