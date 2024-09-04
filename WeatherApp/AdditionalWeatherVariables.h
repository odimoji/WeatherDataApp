//
// Created by Odinaka on 22/04/2024.
//

#ifndef UNTITLED7_ADDITIONALWEATHERVARIABLES_H
#define UNTITLED7_ADDITIONALWEATHERVARIABLES_H

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



class AdditionalWeatherVariables {
private:
    vector<AdditionalWeatherVariables> weatherData;
    string UVIndex;
    string UVIndexClearSky;
    string IsDay;
    string Cape;
public:
    const string &getUvIndex() const;

    void setUvIndex(const string &uvIndex);

    const string &getUvIndexClearSky() const;

    void setUvIndexClearSky(const string &uvIndexClearSky);

    const string &getIsDay() const;

    void setIsDay(const string &isDay);

    const string &getCape() const;

    void setCape(const string &cape);

    const string &getFreezingLevelHeight() const;

    void setFreezingLevelHeight(const string &freezingLevelHeight);

    const string &getSunshineDuration() const;

    void setSunshineDuration(const string &sunshineDuration);

private:
    string FreezingLevelHeight;
    string SunshineDuration;


public:
    AdditionalWeatherVariables FetchDataFromAPI(double, double);

    static size_t writeCallback( void*, size_t,size_t, string*);




};


#endif //UNTITLED7_ADDITIONALWEATHERVARIABLES_H
