#include "IntParameter.h"

void IntParameter::SetValue(int value_to_set) {
    value_[0] = value_to_set;
}

std::string IntParameter::GetLongName() const {
    return long_name_;
}

IntParameter& IntParameter::Default(int &default_value) {
    *value_ = default_value;
    default_ = true;
    return *this;
}

IntParameter& IntParameter::StoreValue(int &stored_value) {
    value_ = &stored_value;
    return *this;
}

std::string IntParameter::GetShortName() const {
    return short_name_;
}

int IntParameter::GetValue() const {
    return value_[0];
}

int IntParameter::GetValue(int index) const {
    return multi_values_[0][index];
}

IntParameter& IntParameter::MultiValue(size_t number) {
    multi_mode_ = true;
    number_of_arguments_ = number;
    return *this;
}

IntParameter &IntParameter::StoreValues(std::vector<int>& values_to_store) {
    multi_values_ = &values_to_store;
    return *this;
}

void IntParameter::AddValue(int value_to_set) {
    multi_values_[0].push_back(value_to_set);
}

bool IntParameter::IsMultiMode() const {
    return multi_mode_;
}

int *IntParameter::GetValuePointer() const {
    return value_;
}

size_t IntParameter::GetNumberOfArguments() const{
    return number_of_arguments_;
}

size_t IntParameter::GetSizeOfVector() const {
    return multi_values_[0].size();
}

IntParameter& IntParameter::Positional() {
    positional_ = true;
    return *this;
}

bool IntParameter::IsPositional() const {
    return positional_;
}

void IntParameter::SetDescription(const std::string& description) {
    description_ = description;
}

std::string IntParameter::GetDescription() const {
    return description_;
}

bool IntParameter::IsDefault() const {
    return default_;
}
