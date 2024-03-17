#include "LINK.h"

void LINK::GetInfo() const {
    Frame::GetInfo();
    std::cout << "Frame identifier: " << frame_identifier_ << '\n';
    std::cout << "URL: " << URL_ << '\n';
    std::cout << "ID and additional data: " << additional_data_ << '\n';
}

LINK* ReadLINK(std::istream& file, const FrameHeader& frame_header) {
    char byte;
    int i = 4;
    std::string identifier;
    std::string url;
    std::string data;

    for (int j = 0; j < 4; ++j) {
        file.read(&byte, 1);
        identifier += byte;
    }

    while (byte != 0){
        file.read(&byte, 1);
        url += byte;
        i++;
    }

    while (i < frame_header.size_){
        file.read(&byte, 1);
        data += byte;
        i++;
    }

    LINK* frame = new LINK(frame_header, identifier, url, data);
    return frame;
}