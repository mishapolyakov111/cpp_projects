#include <fstream>
#include <string>
#include <vector>

struct Arguments{
    uint32_t height;
    uint32_t width;
    std::string input_path;
    std::string output_path;
    uint32_t iters;
    uint32_t frequence;
};

struct Coordinates{
    uint32_t x;
    uint32_t y;

    Coordinates(uint32_t first, uint32_t second){
        x = first;
        y = second;
    }

    Coordinates() {
        x = 0;
        y = 0;
    }
};

struct PointWithValue{
    Coordinates coordinate;
    int64_t value;

    PointWithValue(uint32_t first, uint32_t second, int64_t value_in){
        coordinate = Coordinates(first, second);
        value = value_in;
    }
};

Arguments GetArguments(int n, char* arr[]);

std::vector<PointWithValue> GetPointsFromTSV(const std::string& file_path);
