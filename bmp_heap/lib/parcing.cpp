#include "parsing.h"

Arguments GetArguments(int n, char* arr[]){
    Arguments arguments{};
    std::string current;

    for (int i = 1; i < n; ++i) {
        current = arr[i];

        if (current == "-l" or current == "--lenght"){
            arguments.height = std::stoi(arr[i+1]);
        } else if (current == "-w" or current == "--width"){
            arguments.width = std::stoi(arr[i+1]);
        } else if (current == "-i" or current == "--input"){
            arguments.input_path = arr[i+1];
        } else if (current == "-o" or current == "--output"){
            arguments.output_path = arr[i+1];
        } else if (current == "-m" or current == "--max-iter"){
            arguments.iters = std::stoi(arr[i+1]);
        } else if (current == "-f" or current == "--freq"){
            arguments.frequence = std::stoi(arr[i+1]);
        }
    }

    return arguments;
}

std::vector<PointWithValue> GetPointsFromTSV(const std::string& file_path){
    std::fstream input(file_path);

    std::vector<PointWithValue> points;
    uint32_t x;
    uint32_t y;
    int64_t value;

    while (input >> x >> y >> value){
        PointWithValue p(x, y, value);
        points.push_back(p);
    }

    return points;
}
