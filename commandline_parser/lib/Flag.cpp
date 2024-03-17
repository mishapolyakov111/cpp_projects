#include "Flag.h"

void Flag::SetTrue() {
    *flag_ = true;
}

std::string Flag::GetLongName() const {
    return long_name_;
}

std::string Flag::GetShortName() const {
    return short_name_;
}

Flag& Flag::Default(bool default_value) {
    flag_[0] = default_value;
    default_ = true;
    return *this;
}

Flag& Flag::StoreValue(bool& stored_value) {
    flag_ = &stored_value;
    return *this;
}

bool Flag::GetValue() const {
    return flag_[0];
}

void Flag::SetDescription(const std::string& description) {
    description_ = description;
}

std::string Flag::GetDescription() const {
    return description_;
}

bool Flag::IsDefault() const {
    return default_;
}
