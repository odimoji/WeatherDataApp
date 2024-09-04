//
// Created by Odinaka on 21/04/2024.
//

#include "AdvancedWeatherForecast.h"
#include "Location_management.h"

/*AdvancedWeatherForecast::AdvancedWeatherForecast(){
    temperature = temp;
    humidity = hum;
    dewPoint = dew;
    apparentTemperature = appTemp;
    precipitationProbability = precipProb;
    precipitation = precip;
    rain = rain;
    showers = showers;
    snowfall = snowfall;
    snowDepth = snowDepth;
    weatherCode = weatherCode;
    pressureMSL = pressureMSL;
    surfacePressure = surfacePressure;
    cloudCover = cloudCover;
    cloudCoverLow = cloudCoverLow;
    cloudCoverMid = cloudCoverMid;
    cloudCoverHigh = cloudCoverHigh;
    visibility = visibility;
    evapotranspiration = evapotranspiration;
    et0FaoEvapotranspiration = et0FaoEvapotranspiration;
    vapourPressureDeficit = vapourPressureDeficit;
    windSpeed10m = windSpeed10m;
    windSpeed80m = windSpeed80m;
    windSpeed120m = windSpeed120m;
    windSpeed180m = windSpeed180m;
    windDir10m = windDir10m;
    windDir80m = windDir80m;
    windDir120m = windDir120m;
    windDir180m = windDir180m;
    windGusts10m = windGusts10m;
    temp80m = temp80m;
    temp120m = temp120m;
    temp180m = temp180m;
    soilTemp0cm = soilTemp0cm;
    soilTemp6cm = soilTemp6cm;
    soilTemp18cm = soilTemp18cm;
    soilTemp54cm = soilTemp54cm;
    soilMoisture0to1cm = soilMoisture0to1cm;
    soilMoisture1to3cm = soilMoisture1to3cm;
    soilMoisture3to9cm = soilMoisture3to9cm;
    soilMoisture9to27cm = soilMoisture9to27cm;
    soilMoisture27to81cm = soilMoisture27to81cm;
}

AdvancedWeatherForecast::AdvancedWeatherForecast() {}*/


size_t AdvancedWeatherForecast::writeCallback(void *contents, size_t size, size_t nmemb, string *data) {
    size_t totalSize = size * nmemb;
    data->append((char *)contents, totalSize);
    return totalSize;
}

AdvancedWeatherForecast AdvancedWeatherForecast::FetchDataFromAPI(double latitude, double longitude) {
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
    urlStream
            << "&hourly=temperature_2m,relative_humidity_2m,precipitation,cloud_cover,vapour_pressure_deficit,wind_speed_10m";

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
            AdvancedWeatherForecast awf;
            for (size_t i = 0; i < jsonResponse["hourly"]["temperature_2m"].size(); ++i) {
                awf.setTemperature(to_string(jsonResponse["hourly"]["temperature_2m"][i]));
                awf.setHumidity(to_string(jsonResponse["hourly"]["relative_humidity_2m"][i]));
                awf.setCloudCover(to_string(jsonResponse["hourly"]["cloud_cover"][i]));
                awf.setVapourPressureDeficit(to_string(jsonResponse["hourly"]["vapour_pressure_deficit"][i]));
                awf.setWindSpeed10M(to_string(jsonResponse["hourly"]["wind_speed_10m"][i]));
                awf.setDewPoint(to_string(jsonResponse["hourly"]["dew_point_2m"][i]));
                awf.setApparentTemperature(to_string(jsonResponse["hourly"]["apparent_temperature"][i]));
                awf.setPrecipitationProbability(to_string(jsonResponse["hourly"]["precipitation_probability"][i]));
                awf.setRain(to_string(jsonResponse["hourly"]["rain"][i]));
                awf.setShowers(to_string(jsonResponse["hourly"]["showers"][i]));
                awf.setSnowfall(to_string(jsonResponse["hourly"]["snowfall"][i]));
                awf.setSnowDepth(to_string(jsonResponse["hourly"]["snow_depth"][i]));
                awf.setWeatherCode(to_string(jsonResponse["hourly"]["weather_code"][i]));
                awf.setPressureMsl(to_string(jsonResponse["hourly"]["pressure_msl"][i]));
                awf.setSurfacePressure(to_string(jsonResponse["hourly"]["surface_pressure"][i]));
                awf.setCloudCoverLow(to_string(jsonResponse["hourly"]["cloud_cover_low"][i]));
                awf.setCloudCoverMid(to_string(jsonResponse["hourly"]["cloud_cover_mid"][i]));
                awf.setCloudCoverHigh(to_string(jsonResponse["hourly"]["cloud_cover_high"][i]));
                awf.setVisibility(to_string(jsonResponse["hourly"]["visibility"][i]));
                awf.setEvapotranspiration(to_string(jsonResponse["hourly"]["evapotranspiration"][i]));
                awf.setEt0FaoEvapotranspiration(to_string(jsonResponse["hourly"]["et0_fao_evapotranspiration"][i]));
                awf.setWindSpeed80M(to_string(jsonResponse["hourly"]["wind_speed_80m"][i]));
                awf.setWindSpeed120M(to_string(jsonResponse["hourly"]["wind_speed_120m"][i]));
                awf.setWindSpeed180M(to_string(jsonResponse["hourly"]["wind_speed_180m"][i]));
                awf.setWindDir10M(to_string(jsonResponse["hourly"]["wind_direction_10m"][i]));
                awf.setWindDir80M(to_string(jsonResponse["hourly"]["wind_direction_80m"][i]));
                awf.setWindDir120M(to_string(jsonResponse["hourly"]["wind_direction_120m"][i]));
                awf.setWindDir180M(to_string(jsonResponse["hourly"]["wind_direction_180m"][i]));
                awf.setWindGusts10M(to_string(jsonResponse["hourly"]["wind_gusts_10m"][i]));
                awf.setTemp80M(to_string(jsonResponse["hourly"]["temperature_80m"][i]));
                awf.setTemp120M(to_string(jsonResponse["hourly"]["temperature_120m"][i]));
                awf.setTemp180M(to_string(jsonResponse["hourly"]["temperature_180m"][i]));
                awf.setSoilTemp0Cm(to_string(jsonResponse["hourly"]["soil_temperature_0cm"][i]));
                awf.setSoilTemp6Cm(to_string(jsonResponse["hourly"]["soil_temperature_6cm"][i]));
                awf.setSoilTemp18Cm(to_string(jsonResponse["hourly"]["soil_temperature_18cm"][i]));
                awf.setSoilTemp54Cm(to_string(jsonResponse["hourly"]["soil_temperature_54cm"][i]));
                awf.setSoilMoisture0To1Cm(to_string(jsonResponse["hourly"]["soil_moisture_0_to_1cm"][i]));
                awf.setSoilMoisture1To3Cm(to_string(jsonResponse["hourly"]["soil_moisture_1_to_3cm"][i]));
                awf.setSoilMoisture3To9Cm(to_string(jsonResponse["hourly"]["soil_moisture_3_to_9cm"][i]));
                awf.setSoilMoisture9To27Cm(to_string(jsonResponse["hourly"]["soil_moisture_9_to_27cm"][i]));
                awf.setSoilMoisture27To81Cm(to_string(jsonResponse["hourly"]["soil_moisture_27_to_81cm"][i]));

                // Extract other required parameters similarly



                // Construct and return a WeatherForecast object with the retrieved data
                weatherData.push_back(awf);

            }

        } catch (const json::exception &e) {
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
    // Return a default WeatherForecast object or handle the error case
    return AdvancedWeatherForecast();


}

AdvancedWeatherForecast AdvancedWeatherForecast::AdvancedWeatherForecastDisplay() {
    Location_management WeatherLocation;
    Location_management selectedLocation = WeatherLocation.chooseLocation();

    // Assuming FetchDataFromAPI() takes latitude and longitude as arguments
    FetchDataFromAPI(selectedLocation.getLatitude(), selectedLocation.getLongitude());

    return AdvancedWeatherForecast();
}

const string &AdvancedWeatherForecast::getTemperature() const {
    return temperature;
}

void AdvancedWeatherForecast::setTemperature(const string &temperature) {
    AdvancedWeatherForecast::temperature = temperature;
}

const string &AdvancedWeatherForecast::getHumidity() const {
    return humidity;
}

void AdvancedWeatherForecast::setHumidity(const string &humidity) {
    AdvancedWeatherForecast::humidity = humidity;
}

const string &AdvancedWeatherForecast::getDewPoint() const {
    return dewPoint;
}

void AdvancedWeatherForecast::setDewPoint(const string &dewPoint) {
    AdvancedWeatherForecast::dewPoint = dewPoint;
}

const string &AdvancedWeatherForecast::getApparentTemperature() const {
    return apparentTemperature;
}

void AdvancedWeatherForecast::setApparentTemperature(const string &apparentTemperature) {
    AdvancedWeatherForecast::apparentTemperature = apparentTemperature;
}

const string &AdvancedWeatherForecast::getPrecipitationProbability() const {
    return precipitationProbability;
}

void AdvancedWeatherForecast::setPrecipitationProbability(const string &precipitationProbability) {
    AdvancedWeatherForecast::precipitationProbability = precipitationProbability;
}

const string &AdvancedWeatherForecast::getPrecipitation() const {
    return precipitation;
}

void AdvancedWeatherForecast::setPrecipitation(const string &precipitation) {
    AdvancedWeatherForecast::precipitation = precipitation;
}

const string &AdvancedWeatherForecast::getRain() const {
    return rain;
}

void AdvancedWeatherForecast::setRain(const string &rain) {
    AdvancedWeatherForecast::rain = rain;
}

const string &AdvancedWeatherForecast::getShowers() const {
    return showers;
}

void AdvancedWeatherForecast::setShowers(const string &showers) {
    AdvancedWeatherForecast::showers = showers;
}

const string &AdvancedWeatherForecast::getSnowfall() const {
    return snowfall;
}

void AdvancedWeatherForecast::setSnowfall(const string &snowfall) {
    AdvancedWeatherForecast::snowfall = snowfall;
}

const string &AdvancedWeatherForecast::getSnowDepth() const {
    return snowDepth;
}

void AdvancedWeatherForecast::setSnowDepth(const string &snowDepth) {
    AdvancedWeatherForecast::snowDepth = snowDepth;
}

const string &AdvancedWeatherForecast::getWeatherCode() const {
    return weatherCode;
}

void AdvancedWeatherForecast::setWeatherCode(const string &weatherCode) {
    AdvancedWeatherForecast::weatherCode = weatherCode;
}

const string &AdvancedWeatherForecast::getPressureMsl() const {
    return pressureMSL;
}

void AdvancedWeatherForecast::setPressureMsl(const string &pressureMsl) {
    pressureMSL = pressureMsl;
}

const string &AdvancedWeatherForecast::getSurfacePressure() const {
    return surfacePressure;
}

void AdvancedWeatherForecast::setSurfacePressure(const string &surfacePressure) {
    AdvancedWeatherForecast::surfacePressure = surfacePressure;
}

const string &AdvancedWeatherForecast::getCloudCover() const {
    return cloudCover;
}

void AdvancedWeatherForecast::setCloudCover(const string &cloudCover) {
    AdvancedWeatherForecast::cloudCover = cloudCover;
}

const string &AdvancedWeatherForecast::getCloudCoverLow() const {
    return cloudCoverLow;
}

void AdvancedWeatherForecast::setCloudCoverLow(const string &cloudCoverLow) {
    AdvancedWeatherForecast::cloudCoverLow = cloudCoverLow;
}

const string &AdvancedWeatherForecast::getCloudCoverMid() const {
    return cloudCoverMid;
}

void AdvancedWeatherForecast::setCloudCoverMid(const string &cloudCoverMid) {
    AdvancedWeatherForecast::cloudCoverMid = cloudCoverMid;
}

const string &AdvancedWeatherForecast::getCloudCoverHigh() const {
    return cloudCoverHigh;
}

void AdvancedWeatherForecast::setCloudCoverHigh(const string &cloudCoverHigh) {
    AdvancedWeatherForecast::cloudCoverHigh = cloudCoverHigh;
}

const string &AdvancedWeatherForecast::getVisibility() const {
    return visibility;
}

void AdvancedWeatherForecast::setVisibility(const string &visibility) {
    AdvancedWeatherForecast::visibility = visibility;
}

const string &AdvancedWeatherForecast::getEvapotranspiration() const {
    return evapotranspiration;
}

void AdvancedWeatherForecast::setEvapotranspiration(const string &evapotranspiration) {
    AdvancedWeatherForecast::evapotranspiration = evapotranspiration;
}

const string &AdvancedWeatherForecast::getEt0FaoEvapotranspiration() const {
    return et0FaoEvapotranspiration;
}

void AdvancedWeatherForecast::setEt0FaoEvapotranspiration(const string &et0FaoEvapotranspiration) {
    AdvancedWeatherForecast::et0FaoEvapotranspiration = et0FaoEvapotranspiration;
}

const string &AdvancedWeatherForecast::getVapourPressureDeficit() const {
    return vapourPressureDeficit;
}

void AdvancedWeatherForecast::setVapourPressureDeficit(const string &vapourPressureDeficit) {
    AdvancedWeatherForecast::vapourPressureDeficit = vapourPressureDeficit;
}

const string &AdvancedWeatherForecast::getWindSpeed10M() const {
    return windSpeed10m;
}

void AdvancedWeatherForecast::setWindSpeed10M(const string &windSpeed10M) {
    windSpeed10m = windSpeed10M;
}

const string &AdvancedWeatherForecast::getWindSpeed80M() const {
    return windSpeed80m;
}

void AdvancedWeatherForecast::setWindSpeed80M(const string &windSpeed80M) {
    windSpeed80m = windSpeed80M;
}

const string &AdvancedWeatherForecast::getWindSpeed120M() const {
    return windSpeed120m;
}

void AdvancedWeatherForecast::setWindSpeed120M(const string &windSpeed120M) {
    windSpeed120m = windSpeed120M;
}

const string &AdvancedWeatherForecast::getWindSpeed180M() const {
    return windSpeed180m;
}

void AdvancedWeatherForecast::setWindSpeed180M(const string &windSpeed180M) {
    windSpeed180m = windSpeed180M;
}

const string &AdvancedWeatherForecast::getWindDir10M() const {
    return windDir10m;
}

void AdvancedWeatherForecast::setWindDir10M(const string &windDir10M) {
    windDir10m = windDir10M;
}

const string &AdvancedWeatherForecast::getWindDir80M() const {
    return windDir80m;
}

void AdvancedWeatherForecast::setWindDir80M(const string &windDir80M) {
    windDir80m = windDir80M;
}

const string &AdvancedWeatherForecast::getWindDir120M() const {
    return windDir120m;
}

void AdvancedWeatherForecast::setWindDir120M(const string &windDir120M) {
    windDir120m = windDir120M;
}

const string &AdvancedWeatherForecast::getWindDir180M() const {
    return windDir180m;
}

void AdvancedWeatherForecast::setWindDir180M(const string &windDir180M) {
    windDir180m = windDir180M;
}

const string &AdvancedWeatherForecast::getWindGusts10M() const {
    return windGusts10m;
}

void AdvancedWeatherForecast::setWindGusts10M(const string &windGusts10M) {
    windGusts10m = windGusts10M;
}

const string &AdvancedWeatherForecast::getTemp80M() const {
    return temp80m;
}

void AdvancedWeatherForecast::setTemp80M(const string &temp80M) {
    temp80m = temp80M;
}

const string &AdvancedWeatherForecast::getTemp120M() const {
    return temp120m;
}

void AdvancedWeatherForecast::setTemp120M(const string &temp120M) {
    temp120m = temp120M;
}

const string &AdvancedWeatherForecast::getTemp180M() const {
    return temp180m;
}

void AdvancedWeatherForecast::setTemp180M(const string &temp180M) {
    temp180m = temp180M;
}

const string &AdvancedWeatherForecast::getSoilTemp0Cm() const {
    return soilTemp0cm;
}

void AdvancedWeatherForecast::setSoilTemp0Cm(const string &soilTemp0Cm) {
    soilTemp0cm = soilTemp0Cm;
}

const string &AdvancedWeatherForecast::getSoilTemp6Cm() const {
    return soilTemp6cm;
}

void AdvancedWeatherForecast::setSoilTemp6Cm(const string &soilTemp6Cm) {
    soilTemp6cm = soilTemp6Cm;
}

const string &AdvancedWeatherForecast::getSoilTemp18Cm() const {
    return soilTemp18cm;
}

void AdvancedWeatherForecast::setSoilTemp18Cm(const string &soilTemp18Cm) {
    soilTemp18cm = soilTemp18Cm;
}

const string &AdvancedWeatherForecast::getSoilTemp54Cm() const {
    return soilTemp54cm;
}

void AdvancedWeatherForecast::setSoilTemp54Cm(const string &soilTemp54Cm) {
    soilTemp54cm = soilTemp54Cm;
}

const string &AdvancedWeatherForecast::getSoilMoisture0To1Cm() const {
    return soilMoisture0to1cm;
}

void AdvancedWeatherForecast::setSoilMoisture0To1Cm(const string &soilMoisture0To1Cm) {
    soilMoisture0to1cm = soilMoisture0To1Cm;
}

const string &AdvancedWeatherForecast::getSoilMoisture1To3Cm() const {
    return soilMoisture1to3cm;
}

void AdvancedWeatherForecast::setSoilMoisture1To3Cm(const string &soilMoisture1To3Cm) {
    soilMoisture1to3cm = soilMoisture1To3Cm;
}

const string &AdvancedWeatherForecast::getSoilMoisture3To9Cm() const {
    return soilMoisture3to9cm;
}

void AdvancedWeatherForecast::setSoilMoisture3To9Cm(const string &soilMoisture3To9Cm) {
    soilMoisture3to9cm = soilMoisture3To9Cm;
}

const string &AdvancedWeatherForecast::getSoilMoisture9To27Cm() const {
    return soilMoisture9to27cm;
}

void AdvancedWeatherForecast::setSoilMoisture9To27Cm(const string &soilMoisture9To27Cm) {
    soilMoisture9to27cm = soilMoisture9To27Cm;
}

const string &AdvancedWeatherForecast::getSoilMoisture27To81Cm() const {
    return soilMoisture27to81cm;
}

void AdvancedWeatherForecast::setSoilMoisture27To81Cm(const string &soilMoisture27To81Cm) {
    soilMoisture27to81cm = soilMoisture27To81Cm;
}
