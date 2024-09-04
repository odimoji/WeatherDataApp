//
// Created by Odinaka on 22/04/2024.
//

#include "HistoricalWeather.h"
#include "Location_management.h"
#include "AdvancedHistoricalWeather.h"

HistoricalWeather::HistoricalWeather(double temp, double hum, double precip, double cloud, double vapour, double wind){
    temperature = temp;
    humidity = hum;
    precipitation = precip;
    cloudCover = cloud;
    vapourPressureDeficit = vapour;
    windSpeed = wind;

}
HistoricalWeather::HistoricalWeather() {}

void HistoricalWeather::menu() {
    // void password_user();//login declaration
    //password_user();//login screen
    while (true)
    {
        int choice;
        char x;
        system("cls");
        cout << "\n\t\t\t-------------------------------------------";
        cout << "\n\t\t\t        HISTORICAL WEATHER                 ";
        cout << "\n\t\t\t-------------------------------------------";
        cout << "\n\t\t\t|1|      Basic Historical Weather          ";
        cout << "\n\t\t\t|2|      Advanced Historical Weather         ";
        cout << "\n\t\t\t|3|      Additional Historical Weather Information ";
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
                    BasicHistoricalWeather();
                    cout <<"\n\n\t\t\t Add another Employee Record (Y/N):";
                    cin>>x;
                }while(x == 'Y' || x == 'y' );
//                waitforenter();
                break;
            case 2:
                HistoricalWeatherAdvanced();
                break;
            case 3:
//                AdditionalWeatherInformation();
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

size_t HistoricalWeather::writeCallback(void *contents, size_t size, size_t nmemb, string *data) {
    size_t totalSize = size * nmemb;
    data->append((char *)contents, totalSize);
    return totalSize;
}

HistoricalWeather HistoricalWeather::FetchDataFromAPI(double latitude, double longitude) {
    CURL *curl = curl_easy_init();
    CURLcode result;
    if (!curl) {
        cerr << "Error initializing curl." << endl;
        // Handle error appropriately
    }
    string startDate, endDate;

    // Prompt the user to input start and end dates
    cout << "Enter start date (YYYY-MM-DD): ";
    cin >> startDate;
    cout << "Enter end date (YYYY-MM-DD): ";
    cin >> endDate;

    // Construct the URL using latitude, longitude, start date, and end date
    stringstream urlStream;
    urlStream << "https://archive-api.open-meteo.com/v1/archive?";
    urlStream << "latitude=" << latitude << "&longitude=" << longitude;
    urlStream << "&start_date=" << startDate << "&end_date=" << endDate;
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
                HistoricalWeather hw(temperature, humidity, precipitation, cloudCover, vapourPressureDeficit, windSpeed);

                // Construct and return a WeatherForecast object with the retrieved data
                weatherData.push_back(hw);

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
    return HistoricalWeather();


}

HistoricalWeather HistoricalWeather::BasicHistoricalWeather() {
    Location_management WeatherLocation;
    Location_management selectedLocation = WeatherLocation.chooseLocation();

    // Assuming FetchDataFromAPI() takes latitude and longitude as arguments
    FetchDataFromAPI(selectedLocation.getLatitude(), selectedLocation.getLongitude());

    return HistoricalWeather();
}

HistoricalWeather HistoricalWeather::HistoricalWeatherAdvanced() {
    Location_management WeatherLocation;
    Location_management selectedLocation = WeatherLocation.chooseLocation();


    AdvancedHistoricalWeather ahw;
    ahw.FetchDataFromAPI(selectedLocation.getLatitude(), selectedLocation.getLongitude());


    return HistoricalWeather();
}

double HistoricalWeather::getTemperature() const {
    return temperature;
}

void HistoricalWeather::setTemperature(double temperature) {
    HistoricalWeather::temperature = temperature;
}

double HistoricalWeather::getHumidity() const {
    return humidity;
}

void HistoricalWeather::setHumidity(double humidity) {
    HistoricalWeather::humidity = humidity;
}

double HistoricalWeather::getPrecipitation() const {
    return precipitation;
}

void HistoricalWeather::setPrecipitation(double precipitation) {
    HistoricalWeather::precipitation = precipitation;
}

double HistoricalWeather::getCloudCover() const {
    return cloudCover;
}

void HistoricalWeather::setCloudCover(double cloudCover) {
    HistoricalWeather::cloudCover = cloudCover;
}

double HistoricalWeather::getVapourPressureDeficit() const {
    return vapourPressureDeficit;
}

void HistoricalWeather::setVapourPressureDeficit(double vapourPressureDeficit) {
    HistoricalWeather::vapourPressureDeficit = vapourPressureDeficit;
}

double HistoricalWeather::getWindSpeed() const {
    return windSpeed;
}

void HistoricalWeather::setWindSpeed(double windSpeed) {
    HistoricalWeather::windSpeed = windSpeed;
}
