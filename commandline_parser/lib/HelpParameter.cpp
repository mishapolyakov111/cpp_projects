#include "HelpParameter.h"

std::string HelpParameter::GetLongName() const {
    return long_name_;
}

std::string HelpParameter::GetShortName() const {
    return short_name_;
}

std::string HelpParameter::GetDescription() const {
    return progmramm_descripion_;
}

void HelpParameter::SetTrue() {
    need_help_ = true;
}

bool HelpParameter::GetNeedHelp() const {
    return need_help_;
}
