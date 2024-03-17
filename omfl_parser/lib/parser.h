#pragma once

#include "Parameter.h"

#include <filesystem>
#include <fstream>
#include <istream>


namespace omfl {

class OMFLparser{

public:
    bool valid() const;

    OMFLparser(){
        valid_ = true;
        main_section_ = new Parameter("main_section");
        current_section_ = main_section_;
    }

    void AddKey(const std::string& str);
    void AddSection(const std::string& str);
    void ParseLine(const std::string& line_to_check);
    Parameter Get(const std::string& str) const;
private:
    bool valid_;
    Parameter* main_section_;
    Parameter* current_section_;
};

OMFLparser parse(const std::filesystem::path& path);
OMFLparser parse(const std::string& str);
std::string StringFromFile(const std::filesystem::path& path);


}// namespace