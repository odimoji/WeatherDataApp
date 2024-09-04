//
// Created by Odinaka on 22/04/2024.
//

#include "AdvancedHistoricalWeather.h"
#include "Location_management.h"

size_t AdvancedHistoricalWeather::writeCallback(void *contents, size_t size, size_t nmemb, string *data) {
    size_t totalSize = size * nmemb;
    data->append((char *)contents, totalSize);
    return totalSize;
}
AdvancedHistoricalWeather AdvancedHistoricalWeather::FetchDataFromAPI(double latitude, double longitude) {
    CURL *curl = curl_easy_init();
    CURLcode result;
    if (!curl) {
        cerr << "Error initializing curl." << endl;
        // Handle error appropriately
    }

    // Variables to store start and end dates
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
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        cerr << "Error performing curl operation: " << curl_easy_strerror(result) << endl;
        // Handle error appropriately
    } else {
        try {
            // Parse JSON response
            json jsonResponse = json::parse(response);
            vector<AdvancedHistoricalWeather> weatherData;

            for (size_t i = 0; i < jsonResponse["hourly"]["temperature_2m"].size(); ++i) {
                AdvancedHistoricalWeather ahw;
                ahw.setTemperature(to_string(jsonResponse["hourly"]["temperature_2m"][i]));
                ahw.setHumidity(to_string(jsonResponse["hourly"]["relative_humidity_2m"][i]));
                ahw.setCloudCover(to_string(jsonResponse["hourly"]["cloud_cover"][i]));
                ahw.setVapourPressureDeficit(to_string(jsonResponse["hourly"]["vapour_pressure_deficit"][i]));
                ahw.setWindSpeed10M(to_string(jsonResponse["hourly"]["wind_speed_10m"][i]));
                ahw.setDewPoint(to_string(jsonResponse["hourly"]["dew_point_2m"][i]));
                ahw.setApparentTemperature(to_string(jsonResponse["hourly"]["apparent_temperature"][i]));
                ahw.setPrecipitationProbability(to_string(jsonResponse["hourly"]["precipitation_probability"][i]));
                ahw.setRain(to_string(jsonResponse["hourly"]["rain"][i]));
                ahw.setShowers(to_string(jsonResponse["hourly"]["showers"][i]));
                ahw.setSnowfall(to_string(jsonResponse["hourly"]["snowfall"][i]));
                ahw.setSnowDepth(to_string(jsonResponse["hourly"]["snow_depth"][i]));
                ahw.setWeatherCode(to_string(jsonResponse["hourly"]["weather_code"][i]));
                ahw.setPressureMsl(to_string(jsonResponse["hourly"]["pressure_msl"][i]));
                ahw.setSurfacePressure(to_string(jsonResponse["hourly"]["surface_pressure"][i]));
                ahw.setCloudCoverLow(to_string(jsonResponse["hourly"]["cloud_cover_low"][i]));
                ahw.setCloudCoverMid(to_string(jsonResponse["hourly"]["cloud_cover_mid"][i]));
                ahw.setCloudCoverHigh(to_string(jsonResponse["hourly"]["cloud_cover_high"][i]));
                ahw.setVisibility(to_string(jsonResponse["hourly"]["visibility"][i]));
                ahw.setEvapotranspiration(to_string(jsonResponse["hourly"]["evapotranspiration"][i]));
                ahw.setEt0FaoEvapotranspiration(to_string(jsonResponse["hourly"]["et0_fao_evapotranspiration"][i]));
                ahw.setWindSpeed80M(to_string(jsonResponse["hourly"]["wind_speed_80m"][i]));
                ahw.setWindSpeed120M(to_string(jsonResponse["hourly"]["wind_speed_120m"][i]));
                ahw.setWindSpeed180M(to_string(jsonResponse["hourly"]["wind_speed_180m"][i]));
                ahw.setWindDir10M(to_string(jsonResponse["hourly"]["wind_direction_10m"][i]));
                ahw.setWindDir80M(to_string(jsonResponse["hourly"]["wind_direction_80m"][i]));
                ahw.setWindDir120M(to_string(jsonResponse["hourly"]["wind_direction_120m"][i]));
                ahw.setWindDir180M(to_string(jsonResponse["hourly"]["wind_direction_180m"][i]));
                ahw.setWindGusts10M(to_string(jsonResponse["hourly"]["wind_gusts_10m"][i]));
                ahw.setTemp80M(to_string(jsonResponse["hourly"]["temperature_80m"][i]));
                ahw.setTemp120M(to_string(jsonResponse["hourly"]["temperature_120m"][i]));
                ahw.setTemp180M(to_string(jsonResponse["hourly"]["temperature_180m"][i]));
                ahw.setSoilTemp0Cm(to_string(jsonResponse["hourly"]["soil_temperature_0cm"][i]));
                ahw.setSoilTemp6Cm(to_string(jsonResponse["hourly"]["soil_temperature_6cm"][i]));
                ahw.setSoilTemp18Cm(to_string(jsonResponse["hourly"]["soil_temperature_18cm"][i]));
                ahw.setSoilTemp54Cm(to_string(jsonResponse["hourly"]["soil_temperature_54cm"][i]));
                ahw.setSoilMoisture0To1Cm(to_string(jsonResponse["hourly"]["soil_moisture_0_to_1cm"][i]));
                ahw.setSoilMoisture1To3Cm(to_string(jsonResponse["hourly"]["soil_moisture_1_to_3cm"][i]));
                ahw.setSoilMoisture3To9Cm(to_string(jsonResponse["hourly"]["soil_moisture_3_to_9cm"][i]));
                ahw.setSoilMoisture9To27Cm(to_string(jsonResponse["hourly"]["soil_moisture_9_to_27cm"][i]));
                ahw.setSoilMoisture27To81Cm(to_string(jsonResponse["hourly"]["soil_moisture_27_to_81cm"][i]));

                // Extract other required parameters similarly

                // Construct and return a WeatherForecast object with the retrieved data
                weatherData.push_back(ahw);
            }

            for (int i = 0; i < weatherData.size(); ++i) {
                cout << "Time: " << i << " hours\n";
                cout << "Temperature: " << weatherData[i].getTemperature() << " °C\n";
                cout << "Humidity: " << weatherData[i].getHumidity() << " %\n";
                cout << "Dew Point: " << weatherData[i].getDewPoint() << " °C\n";
                cout << "Apparent Temperature: " << weatherData[i].getApparentTemperature() << " °C\n";
                cout << "Precipitation Probability: " << weatherData[i].getPrecipitationProbability() << " %\n";
                cout << "Precipitation: " << weatherData[i].getPrecipitation() << " mm\n";
                cout << "Rain: " << weatherData[i].getRain() << " mm\n";
                cout << "Showers: " << weatherData[i].getShowers() << " mm\n";
                cout << "Snowfall: " << weatherData[i].getSnowfall() << " mm\n";
                cout << "Snow Depth: " << weatherData[i].getSnowDepth() << " cm\n";
                cout << "Weather Code: " << weatherData[i].getWeatherCode() << endl;
                cout << "Pressure MSL: " << weatherData[i].getPressureMsl() << " hPa\n";
                cout << "Surface Pressure: " << weatherData[i].getSurfacePressure() << " hPa\n";
                cout << "Cloud Cover: " << weatherData[i].getCloudCover() << " %\n";
                cout << "Cloud Cover Low: " << weatherData[i].getCloudCoverLow() << " %\n";
                cout << "Cloud Cover Mid: " << weatherData[i].getCloudCoverMid() << " %\n";
                cout << "Cloud Cover High: " << weatherData[i].getCloudCoverHigh() << " %\n";
                cout << "Visibility: " << weatherData[i].getVisibility() << " km\n";
                cout << "Evapotranspiration: " << weatherData[i].getEvapotranspiration() << " mm\n";
                cout << "ET0 FAO Evapotranspiration: " << weatherData[i].getEt0FaoEvapotranspiration() << " mm\n";
                cout << "Vapour Pressure Deficit: " << weatherData[i].getVapourPressureDeficit() << " hPa\n";
                cout << "Wind Speed 10m: " << weatherData[i].getWindSpeed10M() << " m/s\n";
                cout << "Wind Speed 80m: " << weatherData[i].getWindSpeed80M() << " m/s\n";
                cout << "Wind Speed 120m: " << weatherData[i].getWindSpeed120M() << " m/s\n";
                cout << "Wind Speed 180m: " << weatherData[i].getWindSpeed180M() << " m/s\n";
                cout << "Wind Direction 10m: " << weatherData[i].getWindDir10M() << " degrees\n";
                cout << "Wind Direction 80m: " << weatherData[i].getWindDir80M() << " degrees\n";
                cout << "Wind Direction 120m: " << weatherData[i].getWindDir120M() << " degrees\n";
                cout << "Wind Direction 180m: " << weatherData[i].getWindDir180M() << " degrees\n";
                cout << "Wind Gusts 10m: " << weatherData[i].getWindGusts10M() << " m/s\n";
                cout << "Temperature 80m: " << weatherData[i].getTemp80M() << " °C\n";
                cout << "Temperature 120m: " << weatherData[i].getTemp120M() << " °C\n";
                cout << "Temperature 180m: " << weatherData[i].getTemp180M() << " °C\n";
                cout << "Soil Temperature 0cm: " << weatherData[i].getSoilTemp0Cm() << " °C\n";
                cout << "Soil Temperature 6cm: " << weatherData[i].getSoilTemp6Cm() << " °C\n";
                cout << "Soil Temperature 18cm: " << weatherData[i].getSoilTemp18Cm() << " °C\n";
                cout << "Soil Temperature 54cm: " << weatherData[i].getSoilTemp54Cm() << " °C\n";
                cout << "Soil Moisture 0-1cm: " << weatherData[i].getSoilMoisture0To1Cm() << " %\n";
                cout << "Soil Moisture 1-3cm: " << weatherData[i].getSoilMoisture1To3Cm() << " %\n";
                cout << "Soil Moisture 3-9cm: " << weatherData[i].getSoilMoisture3To9Cm() << " %\n";
                cout << "Soil Moisture 9-27cm: " << weatherData[i].getSoilMoisture9To27Cm() << " %\n";
                cout << "Soil Moisture 27-81cm: " << weatherData[i].getSoilMoisture27To81Cm() << " %\n";

                cout << endl;
            }
        } catch (const json::exception &e) {
            cerr << "JSON parsing error: " << e.what() << endl;
            // Handle parsing error appropriately
            // For example, return a default AdvancedHistoricalWeather object or re-throw the exception
        }
    }

    // Clean up the curl session
    curl_easy_cleanup(curl);

    // Return a default AdvancedHistoricalWeather object or handle the error case
    return AdvancedHistoricalWeather();
}


AdvancedHistoricalWeather AdvancedHistoricalWeather::AdvancedHistoricalWeatherDisplay() {
    Location_management WeatherLocation;
    Location_management selectedLocation = WeatherLocation.chooseLocation();

    // Assuming FetchDataFromAPI() takes latitude and longitude as arguments
    FetchDataFromAPI(selectedLocation.getLatitude(), selectedLocation.getLongitude());

    return AdvancedHistoricalWeather();
}

const string &AdvancedHistoricalWeather::getTemperature() const {
    return temperature;
}

void AdvancedHistoricalWeather::setTemperature(const string &temperature) {
    AdvancedHistoricalWeather::temperature = temperature;
}

const string &AdvancedHistoricalWeather::getHumidity() const {
    return humidity;
}

void AdvancedHistoricalWeather::setHumidity(const string &humidity) {
    AdvancedHistoricalWeather::humidity = humidity;
}

const string &AdvancedHistoricalWeather::getDewPoint() const {
    return dewPoint;
}

void AdvancedHistoricalWeather::setDewPoint(const string &dewPoint) {
    AdvancedHistoricalWeather::dewPoint = dewPoint;
}

const string &AdvancedHistoricalWeather::getApparentTemperature() const {
    return apparentTemperature;
}

void AdvancedHistoricalWeather::setApparentTemperature(const string &apparentTemperature) {
    AdvancedHistoricalWeather::apparentTemperature = apparentTemperature;
}

const string &AdvancedHistoricalWeather::getPrecipitationProbability() const {
    return precipitationProbability;
}

void AdvancedHistoricalWeather::setPrecipitationProbability(const string &precipitationProbability) {
    AdvancedHistoricalWeather::precipitationProbability = precipitationProbability;
}

const string &AdvancedHistoricalWeather::getPrecipitation() const {
    return precipitation;
}

void AdvancedHistoricalWeather::setPrecipitation(const string &precipitation) {
    AdvancedHistoricalWeather::precipitation = precipitation;
}

const string &AdvancedHistoricalWeather::getRain() const {
    return rain;
}

void AdvancedHistoricalWeather::setRain(const string &rain) {
    AdvancedHistoricalWeather::rain = rain;
}

const string &AdvancedHistoricalWeather::getShowers() const {
    return showers;
}

void AdvancedHistoricalWeather::setShowers(const string &showers) {
    AdvancedHistoricalWeather::showers = showers;
}

const string &AdvancedHistoricalWeather::getSnowfall() const {
    return snowfall;
}

void AdvancedHistoricalWeather::setSnowfall(const string &snowfall) {
    AdvancedHistoricalWeather::snowfall = snowfall;
}

const string &AdvancedHistoricalWeather::getSnowDepth() const {
    return snowDepth;
}

void AdvancedHistoricalWeather::setSnowDepth(const string &snowDepth) {
    AdvancedHistoricalWeather::snowDepth = snowDepth;
}

const string &AdvancedHistoricalWeather::getWeatherCode() const {
    return weatherCode;
}

void AdvancedHistoricalWeather::setWeatherCode(const string &weatherCode) {
    AdvancedHistoricalWeather::weatherCode = weatherCode;
}

const string &AdvancedHistoricalWeather::getPressureMsl() const {
    return pressureMSL;
}

void AdvancedHistoricalWeather::setPressureMsl(const string &pressureMsl) {
    pressureMSL = pressureMsl;
}

const string &AdvancedHistoricalWeather::getSurfacePressure() const {
    return surfacePressure;
}

void AdvancedHistoricalWeather::setSurfacePressure(const string &surfacePressure) {
    AdvancedHistoricalWeather::surfacePressure = surfacePressure;
}

const string &AdvancedHistoricalWeather::getCloudCover() const {
    return cloudCover;
}

void AdvancedHistoricalWeather::setCloudCover(const string &cloudCover) {
    AdvancedHistoricalWeather::cloudCover = cloudCover;
}

const string &AdvancedHistoricalWeather::getCloudCoverLow() const {
    return cloudCoverLow;
}

void AdvancedHistoricalWeather::setCloudCoverLow(const string &cloudCoverLow) {
    AdvancedHistoricalWeather::cloudCoverLow = cloudCoverLow;
}

const string &AdvancedHistoricalWeather::getCloudCoverMid() const {
    return cloudCoverMid;
}

void AdvancedHistoricalWeather::setCloudCoverMid(const string &cloudCoverMid) {
    AdvancedHistoricalWeather::cloudCoverMid = cloudCoverMid;
}

const string &AdvancedHistoricalWeather::getCloudCoverHigh() const {
    return cloudCoverHigh;
}

void AdvancedHistoricalWeather::setCloudCoverHigh(const string &cloudCoverHigh) {
    AdvancedHistoricalWeather::cloudCoverHigh = cloudCoverHigh;
}

const string &AdvancedHistoricalWeather::getVisibility() const {
    return visibility;
}

void AdvancedHistoricalWeather::setVisibility(const string &visibility) {
    AdvancedHistoricalWeather::visibility = visibility;
}

const string &AdvancedHistoricalWeather::getEvapotranspiration() const {
    return evapotranspiration;
}

void AdvancedHistoricalWeather::setEvapotranspiration(const string &evapotranspiration) {
    AdvancedHistoricalWeather::evapotranspiration = evapotranspiration;
}

const string &AdvancedHistoricalWeather::getEt0FaoEvapotranspiration() const {
    return et0FaoEvapotranspiration;
}

void AdvancedHistoricalWeather::setEt0FaoEvapotranspiration(const string &et0FaoEvapotranspiration) {
    AdvancedHistoricalWeather::et0FaoEvapotranspiration = et0FaoEvapotranspiration;
}

const string &AdvancedHistoricalWeather::getVapourPressureDeficit() const {
    return vapourPressureDeficit;
}

void AdvancedHistoricalWeather::setVapourPressureDeficit(const string &vapourPressureDeficit) {
    AdvancedHistoricalWeather::vapourPressureDeficit = vapourPressureDeficit;
}

const string &AdvancedHistoricalWeather::getWindSpeed10M() const {
    return windSpeed10m;
}

void AdvancedHistoricalWeather::setWindSpeed10M(const string &windSpeed10M) {
    windSpeed10m = windSpeed10M;
}

const string &AdvancedHistoricalWeather::getWindSpeed80M() const {
    return windSpeed80m;
}

void AdvancedHistoricalWeather::setWindSpeed80M(const string &windSpeed80M) {
    windSpeed80m = windSpeed80M;
}

const string &AdvancedHistoricalWeather::getWindSpeed120M() const {
    return windSpeed120m;
}

void AdvancedHistoricalWeather::setWindSpeed120M(const string &windSpeed120M) {
    windSpeed120m = windSpeed120M;
}

const string &AdvancedHistoricalWeather::getWindSpeed180M() const {
    return windSpeed180m;
}

void AdvancedHistoricalWeather::setWindSpeed180M(const string &windSpeed180M) {
    windSpeed180m = windSpeed180M;
}

const string &AdvancedHistoricalWeather::getWindDir10M() const {
    return windDir10m;
}

void AdvancedHistoricalWeather::setWindDir10M(const string &windDir10M) {
    windDir10m = windDir10M;
}

const string &AdvancedHistoricalWeather::getWindDir80M() const {
    return windDir80m;
}

void AdvancedHistoricalWeather::setWindDir80M(const string &windDir80M) {
    windDir80m = windDir80M;
}

const string &AdvancedHistoricalWeather::getWindDir120M() const {
    return windDir120m;
}

void AdvancedHistoricalWeather::setWindDir120M(const string &windDir120M) {
    windDir120m = windDir120M;
}

const string &AdvancedHistoricalWeather::getWindDir180M() const {
    return windDir180m;
}

void AdvancedHistoricalWeather::setWindDir180M(const string &windDir180M) {
    windDir180m = windDir180M;
}

const string &AdvancedHistoricalWeather::getWindGusts10M() const {
    return windGusts10m;
}

void AdvancedHistoricalWeather::setWindGusts10M(const string &windGusts10M) {
    windGusts10m = windGusts10M;
}

const string &AdvancedHistoricalWeather::getTemp80M() const {
    return temp80m;
}

void AdvancedHistoricalWeather::setTemp80M(const string &temp80M) {
    temp80m = temp80M;
}

const string &AdvancedHistoricalWeather::getTemp120M() const {
    return temp120m;
}

void AdvancedHistoricalWeather::setTemp120M(const string &temp120M) {
    temp120m = temp120M;
}

const string &AdvancedHistoricalWeather::getTemp180M() const {
    return temp180m;
}

void AdvancedHistoricalWeather::setTemp180M(const string &temp180M) {
    temp180m = temp180M;
}

const string &AdvancedHistoricalWeather::getSoilTemp0Cm() const {
    return soilTemp0cm;
}

void AdvancedHistoricalWeather::setSoilTemp0Cm(const string &soilTemp0Cm) {
    soilTemp0cm = soilTemp0Cm;
}

const string &AdvancedHistoricalWeather::getSoilTemp6Cm() const {
    return soilTemp6cm;
}

void AdvancedHistoricalWeather::setSoilTemp6Cm(const string &soilTemp6Cm) {
    soilTemp6cm = soilTemp6Cm;
}

const string &AdvancedHistoricalWeather::getSoilTemp18Cm() const {
    return soilTemp18cm;
}

void AdvancedHistoricalWeather::setSoilTemp18Cm(const string &soilTemp18Cm) {
    soilTemp18cm = soilTemp18Cm;
}

const string &AdvancedHistoricalWeather::getSoilTemp54Cm() const {
    return soilTemp54cm;
}

void AdvancedHistoricalWeather::setSoilTemp54Cm(const string &soilTemp54Cm) {
    soilTemp54cm = soilTemp54Cm;
}

const string &AdvancedHistoricalWeather::getSoilMoisture0To1Cm() const {
    return soilMoisture0to1cm;
}

void AdvancedHistoricalWeather::setSoilMoisture0To1Cm(const string &soilMoisture0To1Cm) {
    soilMoisture0to1cm = soilMoisture0To1Cm;
}

const string &AdvancedHistoricalWeather::getSoilMoisture1To3Cm() const {
    return soilMoisture1to3cm;
}

void AdvancedHistoricalWeather::setSoilMoisture1To3Cm(const string &soilMoisture1To3Cm) {
    soilMoisture1to3cm = soilMoisture1To3Cm;
}

const string &AdvancedHistoricalWeather::getSoilMoisture3To9Cm() const {
    return soilMoisture3to9cm;
}

void AdvancedHistoricalWeather::setSoilMoisture3To9Cm(const string &soilMoisture3To9Cm) {
    soilMoisture3to9cm = soilMoisture3To9Cm;
}

const string &AdvancedHistoricalWeather::getSoilMoisture9To27Cm() const {
    return soilMoisture9to27cm;
}

void AdvancedHistoricalWeather::setSoilMoisture9To27Cm(const string &soilMoisture9To27Cm) {
    soilMoisture9to27cm = soilMoisture9To27Cm;
}

const string &AdvancedHistoricalWeather::getSoilMoisture27To81Cm() const {
    return soilMoisture27to81cm;
}

void AdvancedHistoricalWeather::setSoilMoisture27To81Cm(const string &soilMoisture27To81Cm) {
    soilMoisture27to81cm = soilMoisture27To81Cm;
}
