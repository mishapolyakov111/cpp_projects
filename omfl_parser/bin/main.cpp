#include "lib/parser.h"
#include "ArgParser/ArgParser.h"
#include <iostream>

int main(int argc, char** argv) {
    ArgumentParser::ArgParser arg_parser("OMFL Parser");
    std::string request;
    std::string file_path;
    bool output;

    arg_parser.AddFlag('o', "out", "Output the config").StoreValue(output);
    arg_parser.AddStringArgument('r', "request", "Enter full path of key or section. Example: \"level1.leve2.key\"").StoreValue(request);
    arg_parser.AddStringArgument('f', "file", "File path").StoreValue(file_path);
    arg_parser.AddHelp('h', "help", "Arguments");


    if(!arg_parser.Parse(argc, argv) and !arg_parser.Help()) {
        std::cerr << "Wrong argument" << "\n\n";
        std::cout << arg_parser.HelpDescription() << '\n';
        return 1;
    }

    if(arg_parser.Help()) {
        std::cout << arg_parser.HelpDescription() << std::endl;
        return 0;
    }

    std::filesystem::path path {file_path};
    if (output) {
        std::cout << omfl::StringFromFile(path);
    }

    omfl::OMFLparser omfl_parser = omfl::parse(path);
    Parameter parameter = omfl_parser.Get(request);
    std::cout << parameter;

    return 0;
}
