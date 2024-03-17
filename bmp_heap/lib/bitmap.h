#include <string>
#include <fstream>

struct BitMapFileHeader{
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reserved1;
    uint16_t bf_reserved2;
    uint32_t bf_off_bits;
};

struct BitMapInfo{
    uint32_t bi_size;
    uint32_t bi_width;
    uint32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_count;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    uint32_t bi_x_pels_per_meter;
    uint32_t bi_y_pels_per_meter;
    uint32_t bi_color_used;
    uint32_t bi_color_important;
};

void GenerateBmpFromArr(const std::string& name, const std::string& path, uint32_t width, uint32_t height, uint64_t* arr);

BitMapFileHeader GenerateFileHeader(uint32_t width, uint32_t height);

BitMapInfo GenerateInfoHeader(uint32_t width, uint32_t height);

std::string GenerateBmpName(int iteration);

void GeneratePixel(uint64_t val, unsigned char* pixel);

void WriteFileHeader(std::ofstream &file, BitMapFileHeader file_header);

void WriteInfoHeader(std::ofstream &file, BitMapInfo info_header);
