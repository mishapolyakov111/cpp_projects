#include "ENCR.h"

void ENCR::GetInfo() const {
    Frame::GetInfo();
    std::cout << "Owner identifier: " << owner_identifier_ << '\n';
    std::cout << "Encryption data: " << encryption_data_ << '\n';
}

ENCR* ReadENCR(std::istream& file, const FrameHeader& frame_header) {
    char byte = 1;
    int i = 0;
    std::string identifier;
    std::string data;

    while (byte != 0) {
        file.read(&byte, 1);
        identifier += byte;
        i++;
    }

    file.read(&byte, 1);
    char method = byte;
    i++;

    while (i < frame_header.size_) {
        file.read(&byte, 1);
        data += byte;
        i++;
    }

    ENCR* frame = new ENCR(frame_header, identifier, method, data);
    return frame;
}
