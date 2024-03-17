#pragma once

#include <string>
#include <iostream>

#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

#include <ftxui/component/event.hpp>  // for Event
#include <ftxui/dom/elements.hpp>  // for text, separator, Element, operator|, vbox, border
#include <ftxui/component/component.hpp>  // for CatchEvent, Renderer, operator|=
#include <ftxui/component/loop.hpp>       // for Loop
#include <ftxui/component/screen_interactive.hpp>  // for ScreenInteractive

#include "Weather.h"

using namespace cpr;
using namespace nlohmann;

void WeatherForecast(const std::string& config_name = "config.json");


