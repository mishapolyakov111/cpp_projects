#include "TXXX.h"

void TXXX::GetInfo() const {
    TextFrame::GetInfo();
    std::cout << "value: " << value_ << "\n";
}

TXXX* ReadTXXX(std::istream& file, const FrameHeader& frame_header) {
    char byte;
    file.read(&byte, 1);
    uint8_t encoding = byte;

    std::string buffer;
    std::string information;
    std::string value;

    for (int j = 0; j < frame_header.size_ - 1; ++j) {
        file.read(&byte, 1);
        buffer += byte;
    }

    information = buffer.substr(0, information.find('\0'));
    value = buffer.substr(information.find('\0') + 1);
    TXXX* frame = new TXXX(frame_header, encoding, information, value);
    return frame;
}
