//
// Created by Odinaka on 17/04/2024.
//

#ifndef UNTITLED7_WEATHERFORECAST_H
#define UNTITLED7_WEATHERFORECAST_H

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


class WeatherForecast{
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
    vector<WeatherForecast> weatherData;

public:
    WeatherForecast(double, double, double , double, double, double);
    WeatherForecast();
    void menu();
    WeatherForecast FetchDataFromAPI(double, double);
    WeatherForecast BasicWeatherForecast();
    WeatherForecast WeatherForecastAdvanced();
    WeatherForecast AdditionalWeatherInformation();
    WeatherForecast SolarRadiationInformation();
    WeatherForecast PressureLevelInformation();
    WeatherForecast WeatherModels();
    WeatherForecast DailyWeatherInformation();
};


#endif //UNTITLED7_WEATHERFORECAST_H
