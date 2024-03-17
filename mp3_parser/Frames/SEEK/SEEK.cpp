#include "SEEK.h"

void SEEK::GetInfo() const {
    Frame::GetInfo();
    std::cout << "Minimum offset to next tag: " << offset_ << '\n';
}

SEEK* ReadSEEK(std::istream& file, const FrameHeader& frame_header) {
    uint32_t offset;
    file.read(reinterpret_cast<char*>(&offset), 4);
    SEEK* frame = new SEEK(frame_header, offset);

    return frame;
}
