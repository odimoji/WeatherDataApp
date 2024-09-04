//
// Created by Odinaka on 21/04/2024.
//

#ifndef UNTITLED7_ADVANCEDWEATHERFORECAST_H
#define UNTITLED7_ADVANCEDWEATHERFORECAST_H

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


class AdvancedWeatherForecast {
private:
    vector<AdvancedWeatherForecast> weatherData;
    string temperature;
    string humidity;
    string dewPoint;
    string apparentTemperature;


public:
    const string &getTemperature() const;

    void setTemperature(const string &temperature);

    const string &getHumidity() const;

    void setHumidity(const string &humidity);

    const string &getDewPoint() const;

    void setDewPoint(const string &dewPoint);

    const string &getApparentTemperature() const;

    void setApparentTemperature(const string &apparentTemperature);

    const string &getPrecipitationProbability() const;

    void setPrecipitationProbability(const string &precipitationProbability);

    const string &getPrecipitation() const;

    void setPrecipitation(const string &precipitation);

    const string &getRain() const;

    void setRain(const string &rain);

    const string &getShowers() const;

    void setShowers(const string &showers);

    const string &getSnowfall() const;

    void setSnowfall(const string &snowfall);

    const string &getSnowDepth() const;

    void setSnowDepth(const string &snowDepth);

    const string &getWeatherCode() const;

    void setWeatherCode(const string &weatherCode);

    const string &getPressureMsl() const;

    void setPressureMsl(const string &pressureMsl);

    const string &getSurfacePressure() const;

    void setSurfacePressure(const string &surfacePressure);

    const string &getCloudCover() const;

    void setCloudCover(const string &cloudCover);

    const string &getCloudCoverLow() const;

    void setCloudCoverLow(const string &cloudCoverLow);

    const string &getCloudCoverMid() const;

    void setCloudCoverMid(const string &cloudCoverMid);

    const string &getCloudCoverHigh() const;

    void setCloudCoverHigh(const string &cloudCoverHigh);

    const string &getVisibility() const;

    void setVisibility(const string &visibility);

    const string &getEvapotranspiration() const;

    void setEvapotranspiration(const string &evapotranspiration);

    const string &getEt0FaoEvapotranspiration() const;

    void setEt0FaoEvapotranspiration(const string &et0FaoEvapotranspiration);

    const string &getVapourPressureDeficit() const;

    void setVapourPressureDeficit(const string &vapourPressureDeficit);

    const string &getWindSpeed10M() const;

    void setWindSpeed10M(const string &windSpeed10M);

    const string &getWindSpeed80M() const;

    void setWindSpeed80M(const string &windSpeed80M);

    const string &getWindSpeed120M() const;

    void setWindSpeed120M(const string &windSpeed120M);

    const string &getWindSpeed180M() const;

    void setWindSpeed180M(const string &windSpeed180M);

    const string &getWindDir10M() const;

    void setWindDir10M(const string &windDir10M);

    const string &getWindDir80M() const;

    void setWindDir80M(const string &windDir80M);

    const string &getWindDir120M() const;

    void setWindDir120M(const string &windDir120M);

    const string &getWindDir180M() const;

    void setWindDir180M(const string &windDir180M);

    const string &getWindGusts10M() const;

    void setWindGusts10M(const string &windGusts10M);

    const string &getTemp80M() const;

    void setTemp80M(const string &temp80M);

    const string &getTemp120M() const;

    void setTemp120M(const string &temp120M);

    const string &getTemp180M() const;

    void setTemp180M(const string &temp180M);

    const string &getSoilTemp0Cm() const;

    void setSoilTemp0Cm(const string &soilTemp0Cm);

    const string &getSoilTemp6Cm() const;

    void setSoilTemp6Cm(const string &soilTemp6Cm);

    const string &getSoilTemp18Cm() const;

    void setSoilTemp18Cm(const string &soilTemp18Cm);

    const string &getSoilTemp54Cm() const;

    void setSoilTemp54Cm(const string &soilTemp54Cm);

    const string &getSoilMoisture0To1Cm() const;

    void setSoilMoisture0To1Cm(const string &soilMoisture0To1Cm);

    const string &getSoilMoisture1To3Cm() const;

    void setSoilMoisture1To3Cm(const string &soilMoisture1To3Cm);

    const string &getSoilMoisture3To9Cm() const;

    void setSoilMoisture3To9Cm(const string &soilMoisture3To9Cm);

private:
    string precipitationProbability;
    string precipitation;
    string rain;
    string showers;
    string snowfall;
    string snowDepth;
    string weatherCode;
    string pressureMSL;
    string surfacePressure;
    string cloudCover;
    string cloudCoverLow;
    string cloudCoverMid;
    string cloudCoverHigh;
    string visibility;
    string evapotranspiration;
    string et0FaoEvapotranspiration;
    string vapourPressureDeficit;
    string windSpeed10m;
    string windSpeed80m;
    string windSpeed120m;
    string windSpeed180m;
    string windDir10m;
    string windDir80m;
    string windDir120m;
    string windDir180m;
    string windGusts10m;
    string temp80m;
    string temp120m;
    string temp180m;
    string soilTemp0cm;
    string soilTemp6cm;
    string soilTemp18cm;
    string soilTemp54cm;
    string soilMoisture0to1cm;
    string soilMoisture1to3cm;
    string soilMoisture3to9cm;
    string soilMoisture9to27cm;
public:
    const string &getSoilMoisture9To27Cm() const;

    void setSoilMoisture9To27Cm(const string &soilMoisture9To27Cm);

    const string &getSoilMoisture27To81Cm() const;

    void setSoilMoisture27To81Cm(const string &soilMoisture27To81Cm);

private:
    string soilMoisture27to81cm;

public:
    const vector<AdvancedWeatherForecast> &getWeatherData() const;


private:



public:
    AdvancedWeatherForecast AdvancedWeatherForecastDisplay();

    AdvancedWeatherForecast FetchDataFromAPI(double, double);

    static size_t writeCallback( void*, size_t,size_t, string*);


};


#endif //UNTITLED7_ADVANCEDWEATHERFORECAST_H
