#include "ETCO.h"

uint32_t GetInt(const char* arr) {
    uint32_t current = 0;
    uint32_t it = 0;
    for (int i = 3; i > 0; ++i) {
        current |= arr[i] << it;
        it += 8;
    }

    return current;
}

void ETCO::GetInfo() const {
    Frame::GetInfo();
}

ETCO* ReadETCO(std::istream& file, const FrameHeader& frame_header) {
    char byte;
    file.read(&byte, 1);
    char stamp = byte;
    std::string data;
    for (int i = 1; i < frame_header.size_; ++i) {
        file.read(&byte, 1);
        data += byte;
    }

    ETCO* frame = new ETCO(frame_header, byte, data);
    return frame;
}