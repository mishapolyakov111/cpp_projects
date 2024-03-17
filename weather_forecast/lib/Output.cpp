#include "Output.h"

using namespace ftxui;

std::vector<City> GetCitiesForecasts(const std::vector<std::string>& city_names) {
    std::vector<City> cities;
    for (const auto& city_name : city_names) {
        Response city_response = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                                          Parameters{{"name", city_name}},
                                          cpr::Header{{"X-Api-Key", "EjNCb4YGTOsbfblFg7a98w==KLjLXztQvbO2RsUQ"}});
        if(city_response.text == "[]" or city_response.text.empty()) {
            std::cerr << "SERVER DOES NOT ANSWER\n";
            continue;
        }

        json city_json = json::parse(city_response.text);

        if (!city_response.error) {
            City cur_city(city_json[0]["name"], city_json[0]["latitude"], city_json[0]["longitude"]);
            cities.push_back(cur_city);
        }
    }

    return cities;
}

void Correct(std::string& s) {
    s = s.substr(0, s.find('.') + 2);
}

std::string GetWeatherDescription(int code) {
    std::string s;
    switch (code) {
        case 0:
            s = "Clear sky";
            break;
        case 1:
            s = "Mainly clear";
            break;
        case 2:
            s = "Partly cloudy";
            break;
        case 3:
            s = "Overcast";
            break;
        case 45:
            s = "Fog";
            break;
        case 48:
            s = "Depositing rime fog";
            break;
        case 51:
        case 53:
        case 55:
            s = "Drizzle";
            break;
        case 56:
        case 57:
            s = "Freezing Drizzle";
            break;
        case 61:
        case 63:
        case 65:
            s = "Rain";
            break;
        case 66:
        case 67:
            s = "Freezing Rain";
            break;
        case 71:
        case 73:
        case 75:
            s = "Snow fall";
            break;
        case 77:
            s = "Snow grains";
            break;
        case 80:
        case 81:
        case 82:
            s = "Rain shower";
            break;
        case 85:
        case 86:
            s = "Snow shower";
            break;
        case 95:
        case 96:
        case 99:
            s = "Thunderstorm";
            break;
    }

    return s;
}

Element OneDayBox(const DayForecast& day_Forecast) {
    std::string temperature = std::to_string(day_Forecast.morning_.temperature_);
    Correct(temperature);
    auto morning = vbox(text("Morning") | center,
                        separator(),
                        text(temperature + "°C") | align_right,
                        text(std::to_string(day_Forecast.morning_.humidity_) + "%") | align_right,
                        text(std::to_string(day_Forecast.morning_.wind_speed_) + " km/h") | align_right,
                        text(GetWeatherDescription(day_Forecast.morning_.weather_code_)) | align_right) | border;

    temperature = std::to_string(day_Forecast.day_.temperature_);
    Correct(temperature);
    auto day = vbox(text("Day") | center,
                    separator(),
                    text(temperature + "°C") | align_right,
                    text(std::to_string(day_Forecast.day_.humidity_) + "%") | align_right,
                    text(std::to_string(day_Forecast.day_.wind_speed_) + " km/h") | align_right,
                    text(GetWeatherDescription(day_Forecast.day_.weather_code_)) | align_right) | border;

    temperature = std::to_string(day_Forecast.evening_.temperature_);
    Correct(temperature);
    auto evening = vbox(text("Evening") | center,
                        separator(),
                        text(temperature + "°C") | align_right,
                        text(std::to_string(day_Forecast.evening_.humidity_) + "%") | align_right,
                        text(std::to_string(day_Forecast.evening_.wind_speed_) + " km/h") | align_right,
                        text(GetWeatherDescription(day_Forecast.evening_.weather_code_)) | align_right) | border;

    temperature = std::to_string(day_Forecast.night_.temperature_);
    Correct(temperature);
    auto night = vbox(text("Night") | center,
                      separator(),
                      text(temperature + "°C") | align_right,
                      text(std::to_string(day_Forecast.night_.humidity_) + "%") | align_right,
                      text(std::to_string(day_Forecast.night_.wind_speed_) + " km/h") | align_right,
                      text(GetWeatherDescription(day_Forecast.night_.weather_code_)) | align_right) | border;

    auto box = vbox(morning,
                     day,
                     evening,
                     night) | size(WidthOrHeight::WIDTH, Constraint::EQUAL, 15);
    auto element = window(text(day_Forecast.date_) | center, box);
    return element;
}

Elements GetDaysBoxes(const City& city) {
    Elements days;

    for (const auto& forecast : city.forecasts_) {
        days.push_back(OneDayBox(forecast));
    }

    return days;
}

void WeatherForecast(const std::string& config_name) {
    std::fstream config_to_parse(config_name);
    if (!config_to_parse.is_open()) {
        return;
    }

    json config = json::parse(config_to_parse);
    if(config["cities"].is_null() or config["cities"].empty()) {
        return;
    }
    std::vector<City> cities = GetCitiesForecasts(config["cities"]);

    size_t num_cities_to_print = cities.size();
    int city_idx = 0;
    int default_num_days_to_print = config["default_number_of_days"];
    default_num_days_to_print = default_num_days_to_print > 9 ? 9 : default_num_days_to_print;
    int num_days_to_print = default_num_days_to_print;

    auto screen = ScreenInteractive::Fullscreen();

    Element city_box = flexbox({text(cities[city_idx].name_) | color(Color::BlueLight) | border/*, text(std::to_string(city_idx))*/});
    Elements vec = GetDaysBoxes(cities[city_idx]);

    auto renderer = Renderer([&] {
        Elements to_print;

        for (int i = 0; i < num_days_to_print; ++i) {
            to_print.push_back(vec[i]);
        }

        return vbox(city_box, hbox(to_print)) | frame;
    });


    auto component = CatchEvent(renderer, [&](Event event) {
        if (event == Event::Escape) {
            screen.ExitLoopClosure()();
            return true;
        }

        if (event == Event::Character('n')) {
            if (city_idx < num_cities_to_print - 1){
                num_days_to_print = default_num_days_to_print;
            }
            city_idx = (city_idx < num_cities_to_print - 1) ? city_idx + 1: city_idx;

            city_box = flexbox({text(cities[city_idx].name_) | color(Color::BlueLight) | border/*, text(std::to_string(city_idx))*/});
            vec = GetDaysBoxes(cities[city_idx]);
        }

        if (event == Event::Character('p')) {
            if (city_idx > 0){
                num_days_to_print = default_num_days_to_print;
            }
            city_idx = (city_idx > 0) ? city_idx - 1 : city_idx;

            city_box = flexbox({text(cities[city_idx].name_) | color(Color::BlueLight) | border/*, text(std::to_string(city_idx))*/});
            vec = GetDaysBoxes(cities[city_idx]);
        }

        if (event == Event::Character('+')) {
            num_days_to_print = (num_days_to_print < MAX_NUM_OF_DAYS) ? ++num_days_to_print : num_days_to_print;
        }

        if (event == Event::Character('-')) {
            num_days_to_print = (num_days_to_print > 1) ? --num_days_to_print : num_days_to_print;
        }

        return false;
    });

    screen.Loop(component);
}
