#include "WXXX.h"

void WXXX::GetInfo() const {
    URLFrame::GetInfo();
    std::cout << "description: " << description_ << '\n';
}

WXXX* ReadWXXX(std::istream& file, const FrameHeader& frame_header) {
    char byte;
    file.read(&byte, 1);
    uint8_t encoding = byte;

    std::string url;
    std::string info;

    for (int j = 1; j < frame_header.size_; ++j) {
        file.read(&byte, 1);
        info += byte;
    }
    url = info.substr(info.find('\0'));
    info = info.substr(0, info.find('\0'));
    WXXX* frame = new WXXX(frame_header, encoding, url, info);
    return frame;
}
