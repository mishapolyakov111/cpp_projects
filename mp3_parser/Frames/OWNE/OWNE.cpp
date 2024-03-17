#include "OWNE.h"

void OWNE::GetInfo() const {
    Frame::GetInfo();
    std::cout << "Price paid: " << price_ << '\n';
    std::cout << "Date of purch: " << date_.substr(0, 4) + '.' + date_[4] + date_[5] + '.' + date_[6] + date_[7] << '\n';
    std::cout << "Seller: " << seller_ << '\n';
}

OWNE* ReadOWNE(std::istream& file, const FrameHeader& frame_header) {
    char byte;
    file.read(&byte, 1);
    uint8_t encoding = byte;

    std::string price;
    std::string date;
    std::string seller;

    int i = 1;
    byte = 1;
    while (byte != 0) {
        file.read(&byte, 1);
        price += byte;
        i++;
    }

    for (int j = 0; j < 8; ++j) {
        file.read(&byte, 1);
        date += byte;
        i++;
    }

    while (i < frame_header.size_){
        file.read(&byte, 1);
        seller += byte;
        i++;
    }

    OWNE* frame = new OWNE(frame_header, encoding, price, date, seller);
    return frame;
}

