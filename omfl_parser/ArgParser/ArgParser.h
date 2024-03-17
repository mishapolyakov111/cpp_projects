#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Flag.h"
#include "HelpParameter.h"
#include "IntParameter.h"
#include "StringParameter.h"

namespace ArgumentParser {

    class ArgParser {
    private:
        std::string parser_name_;
        std::vector <StringParameter> string_parametrs_;
        std::vector <IntParameter> int_parametrs_;
        std::vector<Flag> flags_;
        HelpParameter help;
    public:
        explicit ArgParser(const std::string& name  = ""){
            parser_name_ = name;
        }
        bool Parse(const std::vector<std::string>& input);
        bool Help();
        std::string HelpDescription();

        void StringParse(const std::string& input);
        void IntParse(const std::string& input);
        void FlagParse(const std::string& input);
        void PositionalParse(const std::string& input);

        bool Parse(int argc, char** argv);
        StringParameter& AddStringArgument(const std::string& parameter, const std::string& description = "");
        IntParameter& AddIntArgument(const std::string& parameter,const std::string& description = "");
        Flag& AddFlag(const std::string& flag_long, const std::string& description = "");

        StringParameter& AddStringArgument(char short_parameter = 0, const std::string& long_parameter = "", const std::string& description = "");
        IntParameter& AddIntArgument(char short_parameter = 0, const std::string& long_parameter = "", const std::string& description = "");
        Flag& AddFlag(char short_flag, const std::string& long_flag, const std::string& description = "");

        void AddHelp(char help_short_name, const std::string& help_long_name, const std::string& discription);
        std::string GetStringValue(const std::string& parameter_name);
        int GetIntValue(const std::string& parameter_name, int index);
        int GetIntValue(const std::string& parameter_name);
        bool GetFlag(const std::string& flag_name);
    };

} // namespace ArgumentParser
