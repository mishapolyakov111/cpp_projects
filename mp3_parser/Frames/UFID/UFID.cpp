#include "UFID.h"

void UFID::GetInfo() const {
    Frame::GetInfo();
    std::cout << "owner identifier URL: " << owner_identifier_ << '\n';
    std::cout << "identifier " << identifier_ << '\n';
}

UFID* ReadUFID(std::istream& file, const FrameHeader& frame_header) {
    char byte;
    std::string buff;
    std::string url;
    std::string identifier;

    for (int j = 0; j < frame_header.size_; ++j) {
        file.read(&byte, 1);
        buff += byte;
    }
    url = buff.substr(buff.find('\0'));
    identifier = buff.substr(0, buff.find('\0'));

    UFID* frame = new UFID(frame_header, url, identifier);
    return frame;
}

