#include "USER.h"

void USER::GetInfo() const {
    Frame::GetInfo();
    std::cout << "description of the terms of use and ownership: " << information_ << '\n';
}

USER* ReadUSER(std::istream& file, const FrameHeader& frame_header) {
    char byte;
    file.read(&byte, 1);
    uint8_t encoding = byte;
    std::string language;
    std::string info;

    for (int i = 0; i < 3; ++i) {
        file.read(&byte, 1);
        language += byte;
    }

    for (int i = 4; i < frame_header.size_; ++i) {
        file.read(&byte, 1);
        info += byte;
    }

    USER* frame = new USER(frame_header, encoding, language, info);
    return frame;
}
