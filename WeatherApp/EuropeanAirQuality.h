//
// Created by Odinaka on 22/04/2024.
//

#ifndef UNTITLED7_EUROPEANAIRQUALITY_H
#define UNTITLED7_EUROPEANAIRQUALITY_H

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

class EuropeanAirQuality {
private:
    string pm10;
    string pm25;
    string carbonMonoxide;
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

    const string &getOzone() const;

    void setOzone(const string &ozone);

private:
    string nitrogenDioxide;
    string sulphurDioxide;
    string ozone;

public:
    vector<EuropeanAirQuality> weatherData;
    static size_t writeCallback(void*, size_t, size_t, string*);
    EuropeanAirQuality FetchDataFromAPI(double, double);

};


#endif //UNTITLED7_EUROPEANAIRQUALITY_H
