#include "URLFrame.h"

void URLFrame::GetInfo() const {
    Frame::GetInfo();
    std::cout << "URL: " << URL_ << "\n";
}

URLFrame* ReadURLFrame(std::istream& file, const FrameHeader& frame_header) {
    char byte;
    std::string url;
    for (int j = 0; j < frame_header.size_; ++j) {
        file.read(&byte, 1);
        url += byte;
    }
    URLFrame* frame = new URLFrame(frame_header, url);
    return frame;
}
