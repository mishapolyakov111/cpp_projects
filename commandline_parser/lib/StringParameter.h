#pragma once

#include <string>
#include <vector>

class StringParameter {
private:
    std::string long_name_;
    std::string short_name_;
    std::string description_;
    std::string* value_ = new std::string;
    bool multi_mode_ = false;
    bool positional_ = false;
    bool default_ = false;
    size_t min_number_of_arguments_ = - 1;
    std::vector<std::string>* multi_values_ = new std::vector <std::string>;

public:
    void SetValue(const std::string& value_to_set);
    void SetDescription(const std::string& description);
    void AddValue(const std::string& value_to_set);

    std::string GetLongName() const;
    std::string GetShortName() const;
    std::string GetValue() const;
    std::string GetValue(int index) const;
    std::string GetDescription() const;
    bool IsMultiMode() const;
    bool IsDefault() const;
    bool IsPositional() const;
    size_t GetNumberOfArguments() const;
    size_t GetSizeOfVector() const;

    explicit StringParameter(const std::string& parameter_long_name){
        long_name_ = "--" + parameter_long_name;
        short_name_ = "  ";
    }

    explicit StringParameter(char parameter_short_name = 0, const std::string& parameter_long_name = "", const std::string& description = ""){
        long_name_ = "--" + parameter_long_name;
        if(parameter_short_name == 0){
            short_name_ = "  ";
        } else{
            short_name_ = "-";
            short_name_ += parameter_short_name;
        }

        description_ = description;
    }

    StringParameter& Default(const std::string& default_value);
    StringParameter& StoreValue(std::string& stored_value);
    StringParameter& MultiValue(size_t number = -1);
    StringParameter& StoreValues(std::vector<std::string>& values_to_store);
};
