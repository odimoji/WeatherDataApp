//
// Created by Odinaka on 22/04/2024.
//

#ifndef UNTITLED7_AIRQUALITY_H
#define UNTITLED7_AIRQUALITY_H

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

class AirQuality {
private:
    vector<AirQuality> weatherData;
    string pm10;
    string ozone;
public:
    const string &getOzone() const;

    void setOzone(const string &ozone);

public:
    const string &getPm10() const;

    void setPm10(const string &pm10);

    const string &getPm25() const;

    void setPm25(const string &pm25);

    const string &getCarbonMonoxide() const;

    void setCarbonMonoxide(const string &carbonMonoxide);

    const string &getNitrogenDioxide() const;

    void setNitrogenDioxide(const string &nitrogenDioxide);

    const string &getSulphurDioxide() const;

    void setSulphurDioxide(const string &sulphurDioxide);

private:
    string pm25;
    string carbonMonoxide;
    string nitrogenDioxide;
    string sulphurDioxide;


public:
    static size_t writeCallback( void*, size_t,size_t, string*);
    AirQuality(double, double, double , double, double, double);
    AirQuality();
    void menu();
    AirQuality FetchDataFromAPI(double, double);
    AirQuality HourlyAirQuality();
    AirQuality HistoricalWeatherAdvanced();

};


#endif //UNTITLED7_AIRQUALITY_H
