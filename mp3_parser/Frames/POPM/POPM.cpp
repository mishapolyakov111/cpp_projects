#include "POPM.h"

void POPM::GetInfo() const {
    Frame::GetInfo();
    std::cout << "Email to user: " << email_ << '\n';
    std::cout << "Rating: " << static_cast<int>(rating_) << '\n';
    std::cout << "Counter: " << counter_ << '\n';
}

POPM* ReadPOPM(std::istream& file, const FrameHeader& frame_header) {
    char byte = 1;
    int i = 0;
    uint8_t rating;
    std::string email;

    while (byte != 0) {
        file.read(&byte, 1);
        email += byte;
        i++;
    }

    file.read(&byte, 1);
    rating = byte;
    i++;

    std::string counter_in_bits;
    std::bitset <8> tmp;
    while (i < frame_header.size_) {
        i++;
        file.read(&byte, 1);
        tmp = byte;
        counter_in_bits += tmp.to_string();
    }

    const uint32_t len = counter_in_bits.length();
    std::bitset<64> count {counter_in_bits};
    uint64_t counter = count.to_ullong();

    POPM* frame = new POPM(frame_header, email, rating, counter);
    return frame;
}
