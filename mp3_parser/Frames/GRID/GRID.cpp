#include "GRID.h"

void GRID::GetInfo() const {
    Frame::GetInfo();

    std::cout << "Owner identifier: " << identifier_ << '\n';
    std::cout << "Group symbol: " << group_symbol_ << '\n';
}

GRID* ReadGRID(std::istream& file, const FrameHeader& frame_header) {
    int i = 0;
    std::string identifier;
    std::string data;
    uint8_t symbol;

    char byte = 1;
    while (byte != 0) {
        file.read(&byte, 1);
        identifier += byte;
        i++;
    }

    file.read(&byte, 1);
    symbol = byte;
    i++;

    while (i < frame_header.size_) {
        i++;
        file.read(&byte, 1);
        data += byte;
    }

    GRID* frame = new GRID(frame_header, identifier, symbol, data);
    return frame;
}