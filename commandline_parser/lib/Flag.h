#pragma once

#include <string>

class Flag {
private:
    std::string long_name_;
    std::string description_;
    std::string short_name_;
    bool default_ = false;
    bool *flag_ = new bool;
public:
    void SetTrue();
    void SetDescription(const std::string &description);

    std::string GetDescription() const;
    std::string GetLongName() const;
    std::string GetShortName() const;
    bool GetValue() const;
    bool IsDefault() const;

    explicit Flag(const std::string& flag_long_name, const std::string& description = "") {
        flag_[0] = false;
        long_name_ = "--" + flag_long_name;
        short_name_ = "  ";
        description_ = description;
    }

    explicit Flag(char flag_short_name = 0, const std::string& flag_long_name = "", const std::string& description = "") {
        long_name_ = "--" + flag_long_name;
        short_name_ = "-";
        short_name_ += flag_short_name;
        description_ = description;
    }

    Flag& Default(bool default_value);
    Flag& StoreValue(bool &stored_value);
};
