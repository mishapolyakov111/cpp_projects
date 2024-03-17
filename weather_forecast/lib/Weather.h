#pragma once

#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

#include <vector>
#include <cmath>

using namespace cpr;
using namespace nlohmann;

const uint8_t MORNING_TIME = 6;
const uint8_t DAY_TIME = 12;
const uint8_t EVENING_TIME = 18;
const uint8_t NIGHT_TIME = 23;
const uint8_t HOURS_PER_DAY = 24;
const uint8_t MAX_NUM_OF_DAYS = 9;

struct Weather {
    double temperature_ = -1;
    int16_t humidity_ = -1;
    int16_t wind_speed_ = -1;
    int16_t weather_code_ = -1;
};

struct DayForecast {
    std::string date_;
    Weather morning_;
    Weather day_;
    Weather evening_;
    Weather night_;
};

struct City {
    std::string name_;
    float latitude_ = 0;
    float longitude_ = 0;
    DayForecast forecasts_[MAX_NUM_OF_DAYS];

    City(const std::string& name, float latitude, float longitude) : name_(name), latitude_(latitude), longitude_(longitude) {
        GetWeather();
    }

private:
    void GetWeather() {
        Response weather_response = Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
                                        Parameters{{"latitude",      std::to_string(latitude_)},
                                                   {"longitude",     std::to_string(longitude_)},
                                                   {"hourly",        "temperature_2m"},
                                                   {"hourly",        "windspeed_10m"},
                                                   {"hourly",        "relativehumidity_2m"},
                                                   {"hourly",        "weathercode"},
                                                   {"forecast_days", "10"}});
        if (weather_response.status_code != 200) {
            return;
        }

        json weather_json = json::parse(weather_response.text);

        for (int i = 0; i < MAX_NUM_OF_DAYS; ++i) {
            forecasts_[i].date_ = weather_json["hourly"]["time"][HOURS_PER_DAY * i];
            forecasts_[i].date_ = forecasts_[i].date_.substr(0, forecasts_[i].date_.length() - 6);

            double temperature = weather_json["hourly"]["temperature_2m"][HOURS_PER_DAY * i + MORNING_TIME];
            uint8_t humidity = weather_json["hourly"]["relativehumidity_2m"][HOURS_PER_DAY * i + MORNING_TIME];
            uint8_t wind_speed = weather_json["hourly"]["windspeed_10m"][HOURS_PER_DAY * i + MORNING_TIME];
            uint8_t weather_code = weather_json["hourly"]["weathercode"][HOURS_PER_DAY * i + MORNING_TIME];
            forecasts_[i].morning_ = {temperature, humidity, wind_speed, weather_code};

            temperature = weather_json["hourly"]["temperature_2m"][HOURS_PER_DAY * i + DAY_TIME];
            humidity = weather_json["hourly"]["relativehumidity_2m"][HOURS_PER_DAY * i + DAY_TIME];
            wind_speed = weather_json["hourly"]["windspeed_10m"][HOURS_PER_DAY * i + DAY_TIME];
            weather_code = weather_json["hourly"]["weathercode"][HOURS_PER_DAY * i + DAY_TIME];
            forecasts_[i].day_ = {temperature, humidity, wind_speed, weather_code};

            temperature = weather_json["hourly"]["temperature_2m"][HOURS_PER_DAY * i + EVENING_TIME];
            humidity = weather_json["hourly"]["relativehumidity_2m"][HOURS_PER_DAY * i + EVENING_TIME];
            wind_speed = weather_json["hourly"]["windspeed_10m"][HOURS_PER_DAY * i + EVENING_TIME];
            weather_code = weather_json["hourly"]["weathercode"][HOURS_PER_DAY * i + EVENING_TIME];
            forecasts_[i].evening_ = {temperature, humidity, wind_speed, weather_code};

            temperature = weather_json["hourly"]["temperature_2m"][HOURS_PER_DAY * i + NIGHT_TIME];
            humidity = weather_json["hourly"]["relativehumidity_2m"][HOURS_PER_DAY * i + NIGHT_TIME];
            wind_speed = weather_json["hourly"]["windspeed_10m"][HOURS_PER_DAY * i + NIGHT_TIME];
            weather_code = weather_json["hourly"]["weathercode"][HOURS_PER_DAY * i + NIGHT_TIME];
            forecasts_[i].night_ = {temperature, humidity, wind_speed, weather_code};
        }
    }
};

