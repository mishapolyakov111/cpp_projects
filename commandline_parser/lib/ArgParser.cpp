#include <sstream>
#include "ArgParser.h"

namespace ArgumentParser {
    bool ArgParser::Parse(const std::vector<std::string>& input) {

        for (int i = 1; i < input.size(); ++i) {
            if (input[i][0] == '-'){
                if(input[i].find('=') != -1) {
                    StringParse(input[i]);
                    IntParse(input[i]);
                } else if (help.GetLongName() == input[i] or help.GetShortName() == input[i]) {
                    help.SetTrue();
                } else {
                    FlagParse(input[i]);
                }
            } else{
                PositionalParse(input[i]);
            }
        }

        bool flag = true;
        for (auto& string_parametr : string_parametrs_) {
            if (string_parametr.GetValue().empty()) {
                flag = false;
                break;
            }

            flag = string_parametr.GetNumberOfArguments() < string_parametr.GetSizeOfVector() or string_parametr.GetNumberOfArguments() == -1;
            if(!flag){
                break;
            }
        }

        for (int i = 0; i < int_parametrs_.size(); ++i) {
            if (int_parametrs_[i].GetValuePointer() == nullptr) {
                flag = false;
                break;
            }

            flag = int_parametrs_[i].GetNumberOfArguments() < int_parametrs_[i].GetSizeOfVector() or int_parametrs_[i].GetNumberOfArguments() == -1;

            if (!flag) {
                break;
            }
        }

        return flag;
    }

    void ArgParser::StringParse(const std::string& input){
        std::string str_value_from_input;
        std::string parameter_name;
        parameter_name = input.substr(0, input.find('='));
        for (int j = 0; j < string_parametrs_.size(); ++j) {
            if (parameter_name == string_parametrs_[j].GetLongName() or parameter_name == string_parametrs_[j].GetShortName()) {
                str_value_from_input = input.substr(input.find('=') + 1);
                if (string_parametrs_[j].IsMultiMode()) {
                    string_parametrs_[j].AddValue(str_value_from_input);
                } else{
                    string_parametrs_[j].SetValue(str_value_from_input);
                }
            }
        }
    }

    void ArgParser::IntParse(const std::string& input){
        int int_value_from_input;
        std::string parameter_name;
        parameter_name = input.substr(0, input.find('='));

        for (int j = 0; j < int_parametrs_.size(); ++j) {
            if (parameter_name == int_parametrs_[j].GetLongName() or parameter_name == int_parametrs_[j].GetShortName()) {
                int_value_from_input = stoi(input.substr(input.find('=') + 1));
                if (int_parametrs_[j].IsMultiMode()) {
                    int_parametrs_[j].AddValue(int_value_from_input);
                } else{
                    int_parametrs_[j].SetValue(int_value_from_input);
                }
            }
        }
    }

    void ArgParser::FlagParse(const std::string& input){
        for (int i = 0; i < flags_.size(); ++i) {
            if (input == flags_[i].GetLongName() or input.find(flags_[i].GetShortName()[1]) != -1){
                flags_[i].SetTrue();
            }
        }
    }

    void ArgParser::PositionalParse(const std::string& input) {
        for (int i = 0; i < int_parametrs_.size(); ++i) {
            if (int_parametrs_[i].IsPositional()){
                int_parametrs_[i].AddValue(std::stoi(input));
            }
        }
    }

    StringParameter& ArgParser::AddStringArgument(const std::string& parameter, const std::string& description) {
        StringParameter parameter1(0, parameter, description);
        string_parametrs_.push_back(parameter1);

        return string_parametrs_[string_parametrs_.size() - 1];
    }

    StringParameter& ArgParser::AddStringArgument(char short_parameter, const std::string& long_parameter, const std::string& description) {
        StringParameter parameter1(short_parameter, long_parameter, description);
        string_parametrs_.push_back(parameter1);
        return string_parametrs_[string_parametrs_.size() - 1];
    }

    std::string ArgParser::GetStringValue(const std::string& parameter_name) {
        std::string value;
        for (int i = 0; i < string_parametrs_.size(); ++i) {
            if (string_parametrs_[i].GetLongName() == "--" + parameter_name) {
                value = string_parametrs_[i].GetValue();
            }
        }
        return value;
    }

    IntParameter& ArgParser::AddIntArgument(const std::string& parameter, const std::string& description) {
        IntParameter parameter1(0, parameter, description);
        int_parametrs_.push_back(parameter1);

        return int_parametrs_[int_parametrs_.size() - 1];
    }

    IntParameter& ArgParser::AddIntArgument(char short_parameter, const std::string& long_parameter,  const std::string& description) {
        IntParameter parameter1(short_parameter, long_parameter, description);
        int_parametrs_.push_back(parameter1);
        return int_parametrs_[int_parametrs_.size() - 1];
    }

    int ArgParser::GetIntValue(const std::string& parameter_name) {
        int value;
        for (int i = 0; i < int_parametrs_.size(); ++i) {
            if (int_parametrs_[i].GetLongName() == "--" + parameter_name) {
                value = int_parametrs_[i].GetValue();
            }
        }
        return value;
    }

    int ArgParser::GetIntValue(const std::string& parameter_name, int index){
        int value;
        for (int i = 0; i < int_parametrs_.size(); ++i) {
            if (int_parametrs_[i].GetLongName() == "--" + parameter_name) {
                value = int_parametrs_[i].GetValue(index);
            }
        }
        return value;
    }

    Flag& ArgParser::AddFlag(const std::string& flag_long, const std::string& description) {
        Flag flag1(flag_long, description);
        flags_.push_back(flag1);

        return flags_[flags_.size() - 1];
    }

    Flag &ArgParser::AddFlag(char short_flag, const std::string& long_flag,  const std::string& description) {
        Flag flag1(short_flag, long_flag, description);
        flags_.push_back(flag1);
        return flags_[flags_.size() - 1];
    }

    bool ArgParser::GetFlag(const std::string& flag_name) {
        bool value;
        for (int i = 0; i < flags_.size(); ++i) {
            if("--" + flag_name == flags_[i].GetLongName()){
                value = flags_[i].GetValue();
            }
        }
        return value;
    }

    void ArgParser::AddHelp(char help_short_name, const std::string& help_long_name, const std::string& discription) {
        HelpParameter help1(help_short_name, help_long_name, discription);
        help = help1;
    }

    bool ArgParser::Help() {
        return help.GetNeedHelp();
    }

    std::string ArgParser::HelpDescription() {
        std::string result = parser_name_ + "\n";
        result += help.GetDescription() + "\n\n";
        for (int i = 0; i < string_parametrs_.size(); ++i) {
            result += string_parametrs_[i].GetShortName();
            if (string_parametrs_[i].GetShortName() == "  ") {
                result += "   ";
            } else {
                result += ",  ";
            }
            result += string_parametrs_[i].GetLongName() + "=<string>,  "
                    + string_parametrs_[i].GetDescription() + " ";
            if (string_parametrs_[i].IsMultiMode()) {
                result += "[repeated";
                if (string_parametrs_[i].IsPositional()){
                    result += ", positional";
                }
                if (string_parametrs_[i].GetNumberOfArguments() != -1) {
                    result += ", min args = " + std::to_string(string_parametrs_[i].GetNumberOfArguments());
                }
                result += "]";
            }
            if (string_parametrs_[i].IsDefault()) {
                result += "[default = " + string_parametrs_[i].GetValue() + "]";
            }
            result += "\n";
        }

        for (int i = 0; i < flags_.size(); ++i) {
            result += flags_[i].GetShortName();
            if (flags_[i].GetShortName() == "  ") {
                result += "   ";
            } else {
                result += ",  ";
            }
            result += flags_[i].GetLongName() + ",  "
                      + flags_[i].GetDescription();
            if (flags_[i].IsDefault()) {
                result += " [default = ";
                if (flags_[i].GetValue()) {
                    result += "true";
                } else {
                    result += "false";
                }
                result += "]";
            }
            result += "\n";
        }

        for (int i = 0; i < int_parametrs_.size(); ++i) {
            result += int_parametrs_[i].GetShortName();
            if (int_parametrs_[i].GetShortName() == "  ") {
                result += "   ";
            } else {
                result += ",  ";
            }
            result += int_parametrs_[i].GetLongName() + "=<int>,  "
                    + int_parametrs_[i].GetDescription();
            if (int_parametrs_[i].IsMultiMode()) {
                result += " [repeated";
                if (int_parametrs_[i].IsPositional()) {
                    result += ", positional";
                }
                if (int_parametrs_[i].GetNumberOfArguments() != -1) {
                    result += ", min args = " + std::to_string(int_parametrs_[i].GetNumberOfArguments()) + "]";
                }
            }

            if (int_parametrs_[i].IsDefault()) {
                result += "[default = " + std::to_string(int_parametrs_[i].GetValue()) + "]";
            }
            result += "\n";
        }
        result += "\n";

        result += help.GetShortName();
        if (help.GetShortName() == "  "){
            result += "  ";
        } else {
            result += ", ";
        }
        result += help.GetLongName() + " Display this help and exit\n";

        return result;
    }

    bool ArgParser::Parse(int argc, char** argv) {
        std::vector<std::string> comands;
        std::string tmp;
        for (int i = 0; i < argc; ++i) {
            tmp = argv[i];
            comands.push_back(tmp);
        }

        return Parse(comands);
    }
}