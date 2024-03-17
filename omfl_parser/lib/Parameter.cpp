#include "Parameter.h"

std::string Parameter::GetName() const {
    return key_;
}

void Parameter::SetType() {
    if (ArrayValid(value_)) {
        type_ = ARRAY;
    } else if (IntValid(value_)) {
        type_ = INT;
    } else if (StringValid(value_)) {
        type_ = STRING;
    } else if (FloatValid(value_)) {
        type_ = FLOAT;
    } else if (BoolValid(value_)) {
        type_ = BOOL;
    } else if (IsNameValid(key_)){
        type_ = SECTION;
    } else {
        std::cerr << "some cringe" << '\n';
    }
}

bool Parameter::IsInt() const {
    return type_ == INT;
}

uint32_t Parameter::AsInt() const {
    if (IsInt()) {
        return std::stoi(value_);
    }

    std::cerr << "No INT" << '\n';
    return 0;
}

uint32_t Parameter::AsIntOrDefault(uint32_t val) const {
    if (IsInt()) {
        return AsInt();
    }
    return val;
}

bool Parameter::IsFloat() const {
    return type_ == FLOAT;
}

float Parameter::AsFloat() const {
    if (IsFloat()) {
        return std::stof(value_);
    }
    std::cerr << "No FLOAT" << '\n';
    return 0;
}

float Parameter::AsFloatOrDefault(float val) const {
    if (IsFloat()) {
        return AsFloat();
    }

    return val;
}

bool Parameter::IsString() const {
    return type_ == STRING;
}

std::string Parameter::AsString() const {
    if (IsString()) {
        return value_.substr(1, value_.size() - 2);
    }

    std::cerr << "not a string" << '\n';
    return "";
}

std::string Parameter::AsStringOrDefault(const std::string& str) const {
    if (IsString()) {
        return AsString();
    }
    return str;
}

void Parameter::AddKey(Parameter* p) {
    subsections_.push_back(p);
}

Parameter* Parameter::FindName(const std::string& name) const {
    for (int i = 0; i < subsections_.size(); ++i) {
        if (subsections_[i]->GetName() == name) {
            return subsections_[i];
        }
    }
    return nullptr;
}

std::vector<std::string> PointSplit(const std::string& name){
    std::vector<std::string> result;
    std::string section_name;

    if (name[0] == '[' and name[name.size() - 1] == ']'){
        section_name = name.substr(1, name.size() - 2);
    } else {
        section_name = name;
    }

    std::string tmp;
    for (int i = 0; i < section_name.size(); ++i) {
        if (section_name[i] == '.'){
            result.push_back(tmp);
            tmp = "";
        } else {
            tmp += section_name[i];
        }
    }

    result.push_back(tmp);
    return result;
}

Parameter* Parameter::AddSection(const std::string& section_name) const {
    Parameter* current_section = const_cast <Parameter*> (this);
    std::vector <std::string> sections = PointSplit(section_name);

    for (int i = 0; i < sections.size(); ++i) {
        Parameter* tmp = current_section->FindName(sections[i]);
        if (tmp) {
            current_section = tmp;
        } else {
            tmp = new Parameter(sections[i]);
            current_section->AddKey(tmp);
            current_section = tmp;
        }
    }
    return current_section;
}

Parameter Parameter::Get(const std::string& str) const {
    Parameter* current_section = const_cast <Parameter*> (this);
    std::vector <std::string> sections = PointSplit(str);

    for (int i = 0; i < sections.size(); ++i) {
        Parameter* tmp = current_section->FindName(sections[i]);
        if (!tmp){
            std::cerr << "Can't find this key or section" << '\n';
            return {};
        }
        current_section = tmp;
    }

    return *current_section;
}

bool Parameter::IsBool() const {
    return type_ == BOOL;
}

bool Parameter::AsBool() const {
    if (IsBool()){
        if (key_ == "false"){
            return false;
        } else {
            return true;
        }
    }

    std::cerr << "No Bool" << '\n';
    return false;
}

bool Parameter::AsBoolOrDefault(bool q) const {
    if (IsBool()){
        return AsBool();
    }

    return q;
}

Parameter Parameter::operator[](int i) const {
    if (IsArray()){
        std::vector<std::string> array = SplitArray(value_);
        if (i > array.size() - 1){
            return {};
        }
        Parameter tmp("tmp_param", array[i]);
        return tmp;
    }
    std::cerr << "Man, it is not array" << '\n';
    return {};
}

bool Parameter::IsArray() const{
    return type_ == ARRAY;
}

bool Parameter::IsSection() const {
    return type_ == SECTION;
}

std::vector<Parameter *> Parameter::GetSubsections() const {
    return subsections_;
}

std::string Parameter::GetValue() const{
    return value_;
}

int8_t Parameter::GetType() const{
    return type_;
}

void operator << (std::ostream& os, const Parameter& param){
    if (param.IsSection()){
        std::cout << "In section [" + param.GetName() + "]:" << "\n\n";
        std::vector<Parameter*> subsections = param.GetSubsections();
        for (int i = 0; i < subsections.size(); ++i) {
            if (subsections[i]->IsSection()){
                std::cout << '[' << subsections[i]->GetName() << ']' << '\n';
            } else {
                std::cout << subsections[i]->GetName() << " = " << subsections[i]->GetValue() << '\n';
            }
        }
    } else {
        if (param.GetType() != -1){
            std::cout << param.GetName() << " = " << param.GetValue() << '\n';
        }
    }
}
