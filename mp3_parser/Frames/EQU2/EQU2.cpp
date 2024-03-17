#include "EQU2.h"

void EQU2::GetInfo() const {
    Frame::GetInfo();
    for (int i = 0; i < identification_.size(); i += 4) {
        std::cout << "Frequency: " << identification_[i] << identification_[i + 1] << '\n'
                  << "Identification: " << identification_[i + 2] << identification_[i + 3] << '\n';
    }
}

EQU2* ReadEQU2(std::istream& file, const FrameHeader& frame_header) {
    char byte;
    file.read(&byte, 1);
    char method = byte;
    std::string buff;

    byte = 1;
    while (byte != 0) {
        file.read(&byte, 1);
        buff += byte;
    }

    EQU2* frame = new EQU2(frame_header, method, buff);
    return frame;
}
