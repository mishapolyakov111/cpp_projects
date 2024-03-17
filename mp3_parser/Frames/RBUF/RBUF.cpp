#include "RBUF.h"

void RBUF::GetInfo() const {
    Frame::GetInfo();
    std::cout << "Buffer size: " << buffer_size_ << '\n';
    std::cout << "Embedded info flag: " << embedded_info_flag_ << '\n';
    std::cout << "Offset to next tag: " << offset_ << '\n';
}

RBUF* ReadRBUF(std::istream& file, const FrameHeader& frame_header) {
    std::string tmp;
    std::bitset<8> bits;

    char byte;
    for (int i = 0; i < 3; ++i) {
        file.read(&byte, 1);
        bits = byte;
        tmp += bits.to_string();
    }

    std::bitset<32> buff_size_in_bits { tmp };
    uint32_t buff_size = buff_size_in_bits.to_ulong();

    file.read(&byte, 1);
    bits = byte;
    bool flag = bits.test(0);

    uint32_t offset = 0;
    file.read(reinterpret_cast<char *>(offset), 4);

    RBUF* frame = new RBUF(frame_header, buff_size, flag, offset);
    return frame;
}
