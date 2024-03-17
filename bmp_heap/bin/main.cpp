#include "bitmap.h"
#include "parsing.h"

#include <iostream>

void Disperse(uint64_t* arr, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    if (x + 1 < width) {
        arr[y * width + x + 1] += 1;
    }
    if (x > 0) {
        arr[y * width + x - 1] += 1;
    }
    if (y + 1 < height) {
        arr[(y + 1) * width + x] += 1;
    }
    if (y > 0) {
        arr[(y - 1) * width + x] += 1;
    }
}

void SandPile(uint64_t *arr, const std::vector<Coordinates>& buffer, uint32_t width, uint32_t height) {
    for (Coordinates coord: buffer) {
        uint32_t x = coord.x;
        uint32_t y = coord.y;

        arr[y * width + x] -= 4;

        Disperse(arr, x, y, width, height);
    }
}

int main(int argc, char *argv[]) {

    Arguments arguments = GetArguments(argc, argv);

    uint32_t width = arguments.width;
    uint32_t height = arguments.height;
    std::string in_path = arguments.input_path;
    std::string out_path = arguments.output_path;
    uint32_t max_iters = arguments.iters;
    uint32_t freq = arguments.frequence;

    std::vector<PointWithValue> heaps = GetPointsFromTSV(in_path);

    std::vector<Coordinates> buffer;
    uint64_t *arr = new uint64_t[width * height]{};

    //записываем в массив данные из tsv файла
    for (PointWithValue point: heaps) {
        arr[point.coordinate.y * height + point.coordinate.x] = point.value;
        buffer.push_back(point.coordinate);
    }

    for (int i = 0; i < max_iters; ++i) {
        SandPile(arr, buffer, width, height);
        buffer.clear();

        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                if (arr[h * width + w] > 3) {
                    Coordinates c(w, h);
                    buffer.push_back(c);
                }
            }
        }

        if (buffer.empty()) {
            break;
        }

        if (freq != 0 and i % freq == 0) {
            std::string file_name = GenerateBmpName(i);
            GenerateBmpFromArr(file_name, out_path, width, height, arr);
        }
    }

    GenerateBmpFromArr("last.bmp", out_path, width, height, arr);

    std::cout << "Done!";
    return 0;
}
