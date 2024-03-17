#include "StringParameter.h"
#include <iostream>

StringParameter& StringParameter::Default(const std::string& default_value) {
    *value_ = default_value;
    default_ = true;
    return *this;
}

StringParameter& StringParameter::StoreValue(std::string& stored_value){
    value_ = &stored_value;
    return *this;
}

std::string StringParameter::GetLongName() const{
    return long_name_;
}

std::string StringParameter::GetShortName() const {
    return short_name_;
}

std::string StringParameter::GetValue() const {
    return value_[0];
}

void StringParameter::SetValue(const std::string& value_to_set) {
    value_[0] = value_to_set;
}

StringParameter& StringParameter::MultiValue(size_t number){
    multi_mode_ = true;
    min_number_of_arguments_ = number;
    return *this;
}

void StringParameter::AddValue(const std::string &value_to_set) {
    multi_values_[0].push_back(value_to_set);
}

StringParameter &StringParameter::StoreValues(std::vector<std::string> &values_to_store) {
    multi_values_ = &values_to_store;
    return *this;
}

std::string StringParameter::GetValue(int index) const {
    if (multi_values_[0].size() < index){
        std::cerr << "ÄAAAAAAAAAAaaaaAAAAA ";
        return "";
    }
    return multi_values_[0][index];
}

bool StringParameter::IsMultiMode() const{
    return multi_mode_;
}

size_t StringParameter::GetNumberOfArguments() const {
    return min_number_of_arguments_;
}

size_t StringParameter::GetSizeOfVector() const {
    return multi_values_[0].size();
}

void StringParameter::SetDescription(const std::string& description) {
    description_ = description;
}

std::string StringParameter::GetDescription() const {
    return description_;
}

bool StringParameter::IsDefault() const {
    return default_;
}

bool StringParameter::IsPositional() const {
    return positional_;
}
