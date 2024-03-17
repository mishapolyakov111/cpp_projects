#include "parser.h"

namespace omfl{
    OMFLparser parse(const std::string &str_to_parse) {
        OMFLparser tmp_parser;

        std::string str = str_to_parse + '\n';
        std::string line_to_parse;
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == '\n') {
                tmp_parser.ParseLine(line_to_parse);
                if (!tmp_parser.valid()) {
                    break;
                }
                line_to_parse = "";
            } else {
                line_to_parse += str[i];
            }
        }

        return tmp_parser;
    }

    OMFLparser parse(const std::filesystem::path& path){
        if (path.extension() != ".omfl"){
            std::cerr << "wrong extension" << '\n';
            return {};
        }

        std::string str = StringFromFile(path);
        if (str.empty()){
            return {};
        }

        return parse(str);
    }

    void OMFLparser::ParseLine(const std::string& str) {
        std::string line_to_check = DeleteComments(str);
        valid_ = IsLineValid(line_to_check);

        std::string name;
        std::string value;
        if (valid_) {
            line_to_check = DeleteSpaces(line_to_check);
            if (!line_to_check.empty()){
                if (SectionValid(line_to_check)){
                    AddSection(line_to_check);
                } else {
                    AddKey(line_to_check);
                }
            }
        }
    }

    bool OMFLparser::valid() const {
        return valid_;
    }

    void OMFLparser::AddKey(const std::string& str) {
        std::string name = DeleteSpaces(str.substr(0, str.find('=')));
        std::string value = DeleteSpaces(str.substr(str.find('=') + 1));
        Parameter p(name, value);
        if (current_section_->FindName(name)){
            valid_ = false;
        } else {
            Parameter* p = new Parameter(name, value);
            current_section_->AddKey(p);
        }
    }

    void OMFLparser::AddSection(const std::string& str) {
        current_section_ = main_section_->AddSection(str);
    }

    Parameter OMFLparser::Get(const std::string &str) const {
        Parameter param = main_section_->Get(str);
        return param;
    }

    std::string StringFromFile(const std::filesystem::path& path){
        std::fstream file(path.string(), std::ios::binary | std::ios::in);

        std::string str;
        if (!file) {
            std::cerr << "File hasn't opened" << '\n';
            return str;
        }

        char byte;
        while (!file.eof()){
            file.read(&byte, 1);
            str += byte;
        }

        file.close();
        return str;
    }
}
