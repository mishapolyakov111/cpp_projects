#include "COMM.h"

void COMM::GetInfo() const {
    Frame::GetInfo();
    std::cout << "Short content description: " << descriptor_ << '\n';
    std::cout << "Text: " << text_ << "\n";
}

COMM* ReadCOMM(std::istream& file, const FrameHeader& frame_header) {
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
    std::string descriptor = info.substr(0, info.find('\0'));
    std::string text = info.substr(info.find('\0'));

    COMM* frame = new COMM(frame_header, encoding, language, descriptor, text);
    return frame;
}
