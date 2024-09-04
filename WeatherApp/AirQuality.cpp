//
// Created by Odinaka on 22/04/2024.
//

#include "AirQuality.h"
#include "Location_management.h"

AirQuality::AirQuality(double pm1, double pm2, double cM, double nD, double sD, double ozo) {
    pm10 = pm1;
    pm25 = pm2;
    carbonMonoxide = cM;
    nitrogenDioxide = nD;
    sulphurDioxide = sD;
    ozone = ozo;
}

AirQuality::AirQuality() {
    // Default constructor implementation
}

void AirQuality::menu() {
    // void password_user();//login declaration
    //password_user();//login screen
    while (true)
    {
        int choice;
        char x;
        system("cls");
        cout << "\n\t\t\t-------------------------------------------";
        cout << "\n\t\t\t              AIR QUALITY                  ";
        cout << "\n\t\t\t-------------------------------------------";
        cout << "\n\t\t\t|1|      Hourly Air Quality                ";
        cout << "\n\t\t\t|2|      European Air Quality Index        ";
        cout << "\n\t\t\t|3|      Settings                          ";
        cout << "\n\t\t\t       ENTER [1][2][3]                     ";
        cout << "\n\n            Please Enter a Value:              ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                do{
                    HourlyAirQuality();
                    cout <<"\n\n\t\t\t Add another Employee Record (Y/N):";
                    cin>>x;
                }while(x == 'Y' || x == 'y' );
//                waitforenter();
                break;
            case 2:
                   // EuropeanAirQualityIndex();
                break;
            case 3:
//                Settings();
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

size_t AirQuality::writeCallback(void *contents, size_t size, size_t nmemb, string *data) {
    size_t totalSize = size * nmemb;
    data->append((char *)contents, totalSize);
    return totalSize;
}


AirQuality AirQuality::FetchDataFromAPI(double latitude, double longitude) {
    CURL *curl = curl_easy_init();
    CURLcode result;
    if (!curl) {
        cerr << "Error initializing curl." << endl;
        // Handle error appropriately
    }

    stringstream urlStream;
    urlStream << "https://air-quality-api.open-meteo.com/v1/air-quality?";
    urlStream << "latitude=" << latitude << "&longitude=" << longitude;
    urlStream << "&hourly=pm10,pm2_5,carbon_monoxide,nitrogen_dioxide,sulphur_dioxide,ozone";
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
            for (size_t i = 0; i < jsonResponse["hourly"]["pm10"].size(); ++i) {
                double pm10 = jsonResponse["hourly"]["pm10"];
                double pm25 = jsonResponse["hourly"]["pm2_5"];
                double carbonMonoxide = jsonResponse["hourly"]["carbon_monoxide"];
                double nitrogenDioxide = jsonResponse["hourly"]["nitrogen_dioxide"];
                double sulphurDioxide = jsonResponse["hourly"]["sulphur_dioxide"];
                double ozone = jsonResponse["hourly"]["ozone"];
                AirQuality aq(pm10, pm25, carbonMonoxide, nitrogenDioxide, sulphurDioxide, ozone);
                weatherData.push_back(aq);
            }


        } catch (const json::exception& e) {
            cerr << "JSON parsing error: " << e.what() << endl;
            // Handle parsing error appropriately
            // For example, return a default AirQuality object or re-throw the exception
        }
    }
    curl_easy_cleanup(curl);


    // Print extracted data
    for (int i = 0; i < weatherData.size(); ++i) {
    cout << "Air Quality Data:" << endl;
    cout << "PM10: " << pm10 << endl;
    cout << "PM2.5: " << pm25 << endl;
    cout << "Carbon Monoxide: " << carbonMonoxide << endl;
    cout << "Nitrogen Dioxide: " << nitrogenDioxide << endl;
    cout << "Sulphur Dioxide: " << sulphurDioxide << endl;
    cout << "Ozone: " << ozone << endl;
    }



    return AirQuality(); // Return a default AirQuality object or handle the error case
}




AirQuality AirQuality::HourlyAirQuality() {
    Location_management WeatherLocation;
    Location_management selectedLocation = WeatherLocation.chooseLocation();

    FetchDataFromAPI(selectedLocation.getLatitude(), selectedLocation.getLongitude());


    return AirQuality();
}

const string &AirQuality::getPm10() const {
    return pm10;
}

void AirQuality::setPm10(const string &pm10) {
    AirQuality::pm10 = pm10;
}

const string &AirQuality::getPm25() const {
    return pm25;
}

void AirQuality::setPm25(const string &pm25) {
    AirQuality::pm25 = pm25;
}

const string &AirQuality::getCarbonMonoxide() const {
    return carbonMonoxide;
}

void AirQuality::setCarbonMonoxide(const string &carbonMonoxide) {
    AirQuality::carbonMonoxide = carbonMonoxide;
}

const string &AirQuality::getNitrogenDioxide() const {
    return nitrogenDioxide;
}

void AirQuality::setNitrogenDioxide(const string &nitrogenDioxide) {
    AirQuality::nitrogenDioxide = nitrogenDioxide;
}

const string &AirQuality::getSulphurDioxide() const {
    return sulphurDioxide;
}

void AirQuality::setSulphurDioxide(const string &sulphurDioxide) {
    AirQuality::sulphurDioxide = sulphurDioxide;
}

const string &AirQuality::getOzone() const {
    return ozone;
}

void AirQuality::setOzone(const string &ozone) {
    AirQuality::ozone = ozone;
}
/*
HistoricalWeather HistoricalWeather::HistoricalWeatherAdvanced() {
    Location_management WeatherLocation;
    Location_management selectedLocation = WeatherLocation.chooseLocation();


    AdvancedHistoricalWeather ahw;
    ahw.FetchDataFromAPI(selectedLocation.getLatitude(), selectedLocation.getLongitude());


    return HistoricalWeather();
}*/

