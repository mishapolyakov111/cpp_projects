#pragma once

#include <string>
#include <vector>

class IntParameter{
private:
    std::string long_name_;
    std::string short_name_;
    std::string description_;
    int* value_ = new int;
    bool multi_mode_ = false;
    bool positional_ = false;
    bool default_ = false;
    size_t number_of_arguments_ = -1;
    std::vector<int>* multi_values_ = new std::vector <int>;

public:
    void SetValue(int value_to_set);
    void SetDescription(const std::string& description);
    void AddValue(int value_to_set);

    std::string GetLongName() const;
    std::string GetShortName() const;
    std::string GetDescription() const;
    bool IsMultiMode() const;
    int GetValue() const;
    size_t GetNumberOfArguments() const;
    size_t GetSizeOfVector() const;
    int* GetValuePointer() const;
    int GetValue(int index) const;
    bool IsPositional() const;
    bool IsDefault() const;

    explicit IntParameter(const std::string& parameter_long_name){
        long_name_ = "--" + parameter_long_name;
        short_name_ == "  ";
    };
    explicit IntParameter(char parameter_short_name = 0, const std::string& parameter_long_name = "", const std::string& description = ""){
        long_name_ = "--" + parameter_long_name;
        if(parameter_short_name == 0){
            short_name_ = "  ";
        } else{
            short_name_ = "-";
            short_name_ += parameter_short_name;
        }

        description_ = description;
    };


    IntParameter& Default(int& default_value);
    IntParameter& StoreValue(int& stored_value);
    IntParameter& MultiValue(size_t number = -1);
    IntParameter& Positional();
    IntParameter& StoreValues(std::vector<int>& values_to_store);
};
