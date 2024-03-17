#include "POSS.h"

void POSS::GetInfo() const {
    Frame::GetInfo();
    if (time_stamp_ == 1) {
        std::cout << "Absolute time, 32 bit sized, using MPEG frames as unit" << '\n';
    } else {
        std::cout << "Absolute time, 32 bit sized, using milliseconds as unit" << '\n';
    }

    std::cout << "Time offset from the first frame in the stream: " << position_ << '\n';
}

POSS* ReadPOSS(std::istream& file, const FrameHeader& frame_header) {
    uint8_t stamp = 0;
    uint32_t pos = 0;
    file.read(reinterpret_cast<char*>(stamp), 1);
    file.read(reinterpret_cast<char*>(pos), 4);

    POSS* frame = new POSS(frame_header, stamp, pos);
    return frame;
}
