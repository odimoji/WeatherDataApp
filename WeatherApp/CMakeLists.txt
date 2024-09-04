cmake_minimum_required(VERSION 3.25)

project(untitled7)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
link_directories(${CURL_LINK_DIRS})



set(CMAKE_CXX_STANDARD 17)

add_executable(untitled7 main.cpp json.hpp Location_management.cpp Location_management.h Location_management.cpp WeatherForecast.cpp WeatherForecast.h MainMenu.cpp MainMenu.h AdvancedWeatherForecast.cpp AdvancedWeatherForecast.h AdditionalWeatherVariables.cpp AdditionalWeatherVariables.h HistoricalWeather.cpp HistoricalWeather.h AdvancedHistoricalWeather.cpp AdvancedHistoricalWeather.h AirQuality.cpp AirQuality.h EuropeanAirQuality.cpp EuropeanAirQuality.h)



target_link_libraries(untitled7 PRIVATE CURL::libcurl)


