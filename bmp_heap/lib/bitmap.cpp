#include "bitmap.h"

const unsigned int FILE_HEADER_SIZE = 14;
const unsigned int INFO_HEADER_SIZE = 40;

BitMapFileHeader GenerateFileHeader(uint32_t width, uint32_t height) {
    BitMapFileHeader file_header{};

    unsigned int padding = (4 - width * 3 % 4) % 4;
    unsigned int file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + width * height * 3 + padding * height;
    file_header.bf_type = 0x4D42;
    file_header.bf_size = file_size;
    file_header.bf_reserved1 = 0;
    file_header.bf_reserved2 = 0;
    file_header.bf_off_bits = FILE_HEADER_SIZE + INFO_HEADER_SIZE;

    return file_header;
}

BitMapInfo GenerateInfoHeader(uint32_t width, uint32_t height) {
    BitMapInfo info_header{};

    info_header.bi_size = INFO_HEADER_SIZE;
    info_header.bi_width = width;
    info_header.bi_height = height;
    info_header.bi_planes = 1;
    info_header.bi_bit_count = 24;
    info_header.bi_compression = 0;
    info_header.bi_size_image = height * width;
    info_header.bi_x_pels_per_meter = 0;
    info_header.bi_y_pels_per_meter = 0;
    info_header.bi_color_used = 0;
    info_header.bi_color_important = 0;

    return info_header;
}

void WriteFileHeader(std::ofstream& file, BitMapFileHeader file_header) {
    file.write((char*) &file_header.bf_type, 2);
    file.write((char*) &file_header.bf_size, 4);
    file.write((char*) &file_header.bf_reserved1, 2);
    file.write((char*) &file_header.bf_reserved2, 2);
    file.write((char*) &file_header.bf_off_bits, 4);
}

void WriteInfoHeader(std::ofstream& file, BitMapInfo info_header) {
    file.write((char*) &info_header.bi_size, 4);
    file.write((char*) &info_header.bi_width, 4);
    file.write((char*) &info_header.bi_height, 4);
    file.write((char*) &info_header.bi_planes, 2);
    file.write((char*) &info_header.bi_bit_count, 2);
    file.write((char*) &info_header.bi_compression, 4);
    file.write((char*) &info_header.bi_size_image, 4);
    file.write((char*) &info_header.bi_x_pels_per_meter, 4);
    file.write((char*) &info_header.bi_y_pels_per_meter, 4);
    file.write((char*) &info_header.bi_color_used, 4);
    file.write((char*) &info_header.bi_color_important, 4);
}

std::string GenerateBmpName(int iteration) {
    return std::to_string(iteration) + ".bmp";
}

void GeneratePixel(uint64_t val, unsigned char* pixel) {
    pixel[0] = 0;
    pixel[1] = 0;
    pixel[2] = 0;
    if (val == 1) {
        //green
        pixel[1] = 255;
    } else if (val == 2) {
        //purple
        pixel[0] = 255;
        pixel[2] = 255;
    } else if (val == 3) {
        //yellow
        pixel[1] = 255;
        pixel[2] = 255;
    } else if (val == 0) {
        //white
        pixel[0] = 255;
        pixel[1] = 255;
        pixel[2] = 255;
    }
}

void
GenerateBmpFromArr(const std::string& name, const std::string& path, uint32_t width, uint32_t height, uint64_t* arr) {
    std::string full_name = path + "\\" + name;

    std::ofstream image(full_name);

    BitMapFileHeader file_header = GenerateFileHeader(width, height);
    BitMapInfo info_header = GenerateInfoHeader(width, height);

    WriteFileHeader(image, file_header);
    WriteInfoHeader(image, info_header);

    uint32_t padding = (4 - width * 3 % 4) % 4;
    char padding_amount[padding];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            unsigned char pixel[3];
            GeneratePixel(arr[i * width + j], pixel);

            image.write((char*) pixel, 3);
        }
        image.write(padding_amount, padding);
    }

    image.close();
}
