//
// Created by Odinaka on 17/04/2024.
//

#include "WeatherForecast.h"
#include "Location_management.h"
#include "AdvancedWeatherForecast.h"
#include "AdditionalWeatherVariables.h"


// Constructor to initialize the weather data
WeatherForecast::WeatherForecast(double temp, double hum, double precip, double cloud, double vapour, double wind){
    temperature = temp;
    humidity = hum;
    precipitation = precip;
    cloudCover = cloud;
    vapourPressureDeficit = vapour;
    windSpeed = wind;

}
WeatherForecast::WeatherForecast() {}

void WeatherForecast::menu() {
    // void password_user();//login declaration
    //password_user();//login screen
    while (true)
    {
        int choice;
        char x;
        system("cls");
        cout << "\n\t\t\t-------------------------------------------";
        cout << "\n\t\t\t        WEATHER FORECAST                ";
        cout << "\n\t\t\t-------------------------------------------";
        cout << "\n\t\t\t|1|      Basic weather Forecast            ";
        cout << "\n\t\t\t|2|      Advanced Weather Forecast         ";
        cout << "\n\t\t\t|3|      Additional Weather Information    ";
        cout << "\n\t\t\t|4|      Solar Radiation Information       ";
        cout << "\n\t\t\t|5|      Pressure Level Information        ";
        cout << "\n\t\t\t|6|      Weather Models                    ";
        cout << "\n\t\t\t|7|      Daily Weather Information         ";
        cout << "\n\t\t\t|8|      Settings                          ";
        cout << "\n\t\t\t       ENTER [1][2][3][4][5][6][7][8]      ";
        cout << "\n\n            Please Enter a Value:              ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                do{
                    BasicWeatherForecast();
                    cout <<"\n\n\t\t\t Check Another Forecast(Y/N):";
                    cin>>x;
                }while(x == 'Y' || x == 'y' );
//                waitforenter();
                break;
            case 2:
                WeatherForecastAdvanced();
                break;
            case 3:
                AdditionalWeatherInformation();
                do{
//                    modify();
                    cout <<"\n\n\t\t\t Would you like to modify another Employee Record(Y/N):";
                    cin>>x;
                }while(x == 'Y' || x == 'y' );
//                waitforenter();
                break;
            case 4:
                //SolarRadiationInformation();
                break;
                system("cls");
                cout<<"\n\t\t\t>>Weather App System by Odi Dimoji<<\n\n";
                system("pause");
                //password_user();
            case 5:
                //PressureLevelInformation();
                break;
            case 6:
                //WeatherModels();
                break;
            case 7:
                //DailyWeatherInformation();
                break;

            default:
                cout<<"\n\n\t\t\t Invalid Entry, Please try again.\n\n\t\t\t";
                break;

        }
        getch();

    }
}

size_t writeCallback(void *contents, size_t size, size_t nmemb, string *data) {
    size_t totalSize = size * nmemb;
    data->append((char *)contents, totalSize);
    return totalSize;
}

WeatherForecast WeatherForecast::FetchDataFromAPI(double latitude, double longitude) {
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
            for (size_t i = 0; i < jsonResponse["hourly"]["temperature_2m"].size(); ++i){
                double temperature = jsonResponse["hourly"]["temperature_2m"][i];
                double humidity = jsonResponse["hourly"]["relative_humidity_2m"][i];
                double precipitation = jsonResponse["hourly"]["precipitation"][i];
                double cloudCover = jsonResponse["hourly"]["cloud_cover"][i];
                double vapourPressureDeficit = jsonResponse["hourly"]["vapour_pressure_deficit"][i];
                double windSpeed = jsonResponse["hourly"]["wind_speed_10m"][i];
                // Extract other required parameters similarly
                WeatherForecast wf(temperature, humidity, precipitation, cloudCover, vapourPressureDeficit, windSpeed);

                // Construct and return a WeatherForecast object with the retrieved data
                weatherData.push_back(wf);

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
        cout << "Temperature: " << weatherData[i].getTemperature() << " °C\n";
        cout << "Humidity: " << weatherData[i].getHumidity() << " %\n";
        cout << "Precipitation: " << weatherData[i].getPrecipitation() << " mm\n";
        cout << "Cloud Cover: " << weatherData[i].getCloudCover() << " %\n";
        cout << "Vapour Pressure Deficit: " << weatherData[i].getVapourPressureDeficit() << " Pa\n";
        cout << "Wind Speed: " << weatherData[i].getWindSpeed() << " m/s\n\n";
    }
    // Return a default WeatherForecast object or handle the error case
    return WeatherForecast();


}

WeatherForecast WeatherForecast::BasicWeatherForecast() {
    Location_management WeatherLocation;
    Location_management selectedLocation = WeatherLocation.chooseLocation();

    // Assuming FetchDataFromAPI() takes latitude and longitude as arguments
    FetchDataFromAPI(selectedLocation.getLatitude(), selectedLocation.getLongitude());

    return WeatherForecast();
}

WeatherForecast WeatherForecast::WeatherForecastAdvanced() {
    Location_management WeatherLocation;
    Location_management selectedLocation = WeatherLocation.chooseLocation();

    AdvancedWeatherForecast awf;
    awf.FetchDataFromAPI(selectedLocation.getLatitude(), selectedLocation.getLongitude());


    return WeatherForecast();
}

WeatherForecast WeatherForecast::AdditionalWeatherInformation() {
    Location_management WeatherLocation;
    Location_management selectedLocation = WeatherLocation.chooseLocation();

    AdditionalWeatherVariables awv;
    awv.FetchDataFromAPI(selectedLocation.getLatitude(), selectedLocation.getLongitude());


    return WeatherForecast();
}



double WeatherForecast::getTemperature() const {
    return temperature;
}

void WeatherForecast::setTemperature(double temperature) {
    WeatherForecast::temperature = temperature;
}

double WeatherForecast::getHumidity() const {
    return humidity;
}

void WeatherForecast::setHumidity(double humidity) {
    WeatherForecast::humidity = humidity;
}

double WeatherForecast::getPrecipitation() const {
    return precipitation;
}

void WeatherForecast::setPrecipitation(double precipitation) {
    WeatherForecast::precipitation = precipitation;
}

double WeatherForecast::getCloudCover() const {
    return cloudCover;
}

void WeatherForecast::setCloudCover(double cloudCover) {
    WeatherForecast::cloudCover = cloudCover;
}

double WeatherForecast::getVapourPressureDeficit() const {
    return vapourPressureDeficit;
}

void WeatherForecast::setVapourPressureDeficit(double vapourPressureDeficit) {
    WeatherForecast::vapourPressureDeficit = vapourPressureDeficit;
}

double WeatherForecast::getWindSpeed() const {
    return windSpeed;
}

void WeatherForecast::setWindSpeed(double windSpeed) {
    WeatherForecast::windSpeed = windSpeed;
}
/*
 WeatherForecast::weatherData(double, double, double, double, double, double) {
    return 0;
}*/
