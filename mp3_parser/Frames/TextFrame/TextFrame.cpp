#include "TextFrame.h"

void TextFrame::GetInfo() const {
    Frame::GetInfo();
    std::cout << "information: "<< information_ + "\n";
}

TextFrame* ReadTextFrame(std::istream& file, const FrameHeader& frame_header) {
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

    TextFrame* frame = new TextFrame(frame_header, encoding, buffer);
    return frame;
}