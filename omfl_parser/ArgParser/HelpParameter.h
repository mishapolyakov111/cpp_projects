#pragma once

#include <string>

class HelpParameter {
private:
    std::string long_name_;
    std::string short_name_;
    std::string progmramm_descripion_;
    bool need_help_ = false;
public:
    std::string GetLongName() const;
    std::string GetShortName() const;
    std::string GetDescription() const;
    bool GetNeedHelp() const;

    void SetTrue();
    explicit HelpParameter(char help_short_name = 0, const std::string& help_long_name = "", const std::string& description = "") {
        long_name_ = "--" + help_long_name;
        if(help_short_name == 0){
            short_name_ = "  ";
        } else{
            short_name_ = "-";
            short_name_ += help_short_name;
        }

        progmramm_descripion_ = description;
    }
};
