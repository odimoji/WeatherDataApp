//
// Created by Odinaka on 24/03/2024.
//

#ifndef UNTITLED7_LOCATION_MANAGEMENT_H
#define UNTITLED7_LOCATION_MANAGEMENT_H

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

using Json = nlohmann::json;

using namespace std;
class Location_management {
private:
    string city;
    string country;
public:
    double getLatitude() const;
    void setLatitude(double latitude);
    double getLongitude() const;
    void setLongitude(double longitude);

private:
    double latitude;
    double longitude;

public:
    static size_t writeCallback(char* ptr, size_t size, size_t nmemb, std::string* data);

    Location_management(double, double, string, string);
    Location_management();

    void menu();
    void waitforenter();
    void insert();
    void display();
    void modify();

    Location_management queryLocation(string, string);
    Location_management chooseLocation();

    const string &getCity() const;
    const string &getCountry() const;
    void setCity(const string &city);
    void setCountry(const string &country);

};



#endif //UNTITLED7_LOCATION_MANAGEMENT_H



