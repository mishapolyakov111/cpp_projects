#include <iostream>
#include <fstream>
#include <vector>
#include <getopt.h>

int countLines(std::string filePath) { //const std::string& filePath
    std::fstream file(filePath);

    int count = 0;//count_lines
    std::string s;

    while (!file.eof()) {
        getline(file, s);
        count++;
    }
    //файл нужно закрыватб
    return count;
}

int countBytes(std::string filePath) {
    std::fstream file(filePath);

    file.seekg(0, std::ios_base::end);
    int bytes = file.tellg();

    return bytes;
}

int countWords(std::string filePath) {
    std::fstream file(filePath);

    int count = 0;
    std::string s;
    while (!file.eof()) {
        getline(file, s);
        s += ' ';
        for (int i = 0; i < s.length() - 1; ++i) {
            if (s[i] != '\t' and s[i] != '\n' and s[i] != ' '
                and (s[i + 1] == '\t' or s[i + 1] == '\n' or s[i + 1] == ' ')) {
                count++;
            }
        }
    }

    return count;
};

double averageBytesPerWords(const std::string& filePath){
    return double(countBytes(filePath)) / countWords(filePath);
};

int countChars(std::string filePath) {
    std::fstream file(filePath);

    int count = 0;
    std::string s;
    while (!file.eof()) {
        getline(file, s);
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] != '\t' and s[i] != '\n' and s[i] != ' ') { // буквой считаю любой прописной символ
                count++;
            }
        }
    }

    return count;
};

int main(int argc, char **argv) {
    std::cout << "Labwork1!\n";
    std::vector<std::string> file_pathes;

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            file_pathes.emplace_back(argv[i]);
        }
    }

    struct option long_opt[] = {
            {"lines", 0, 0, 'l'},
            {"bytes", 0, 0, 'c'},
            {"words", 0, 0, 'w'},
            {"chars", 0, 0, 'm'},
            {"average", 0, 0, 'a'}
    };

    int optidx;
    int opt;
    bool l_flag = false,
            c_flag = false,
            w_flag = false,
            m_flag = false,
            a_flag = false;

    while ((opt = getopt_long(argc, argv, "lcwma", long_opt, &optidx)) != -1) {
        switch (opt) {
            case 'l': {
                l_flag = true;
                break;
            }
            case 'c': {
                c_flag = true;
                break;
            }
            case 'w': {
                w_flag = true;
                break;
            }
            case 'm': {
                m_flag = true;
                break;
            }
            case 'a':{
                a_flag = true;
                break;
            }
            default:{
                std::cout << "Errrrror!! Wrong Input" << std::endl;
            }
        }
    }

    for (std::string file: file_pathes) {
        if (l_flag) {
            std::cout << countLines(file) << " lines ";
        }
        if (c_flag) {
            std::cout << countBytes(file) << " bytes ";
        }
        if (w_flag) {
            std::cout << countWords(file) << " words ";
        }
        if (m_flag) {
            std::cout << countChars(file) << " chars ";
        }
        if (a_flag) {
            std::cout << averageBytesPerWords(file) << std::endl;
        }
        if (!(l_flag or c_flag or w_flag or m_flag)) {
            std::cout << "Default output:" << '\n'
                      << countLines(file) << " lines "
                      << countBytes(file) << " bytes "
                      << countWords(file) << " words "
                      << countChars(file) << " chars ";
        }
        std::cout << '\n';
    }
    return 0;
}

