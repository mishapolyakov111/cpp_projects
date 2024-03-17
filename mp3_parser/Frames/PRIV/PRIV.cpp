#include "PRIV.h"

void PRIV::GetInfo() const {
    Frame::GetInfo();
    std::cout << "Owner identifier: " << identifier_ + '\n';
    std::cout << "The private data: " << private_data_ + '\n';
}

PRIV* ReadPRIV(std::istream& file, const FrameHeader& frame_header) {
    int i = 0;
    char byte = 1;
    std::string identifier;
    std::string data;

    while (byte != 0) {
        file.read(&byte, 1);
        identifier += byte;
        i++;
    }

    while (i < frame_header.size_) {
        file.read(&byte, 1);
        data += byte;
        i++;
    }

    PRIV* frame  = new PRIV(frame_header, identifier, data);
    return frame;
}
