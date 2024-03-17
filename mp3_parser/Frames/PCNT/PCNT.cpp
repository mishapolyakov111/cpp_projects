#include "PCNT.h"

void PCNT::GetInfo() const {
    Frame::GetInfo();
    std::cout << "Counter = " << counter_ << '\n';
}

PCNT* ReadPCNT(std::istream& file, const FrameHeader& frame_header) {
    uint32_t cnt = 0;
    file.read(reinterpret_cast<char*>(cnt), 4);
    PCNT* frame = new PCNT(frame_header, cnt);
    return frame;
}
