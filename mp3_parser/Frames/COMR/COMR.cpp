#include "COMR.h"

void COMR::GetInfo() const {
    Frame::GetInfo();

    std::cout << "Price " << price_ << '\n';
    std::cout << "Valid until: " << valid_time_.substr(0, 4) + '.' + valid_time_[4] + valid_time_[5] + '.' + valid_time_[6] + valid_time_[7] << '\n';
    std::cout << "Contact URL: " << URL_ << '\n';
    std::cout << "Received as: ";

    if (received_ == 0) {
        std::cout << "Other\n";
    } else if (received_ == 1) {
        std::cout << "Standard CD album with other songs\n";
    } else if (received_ == 2) {
        std::cout << "Compressed audio on CD\n";
    } else if (received_ == 3) {
        std::cout << "File over the Internet\n";
    } else if (received_ == 4) {
        std::cout << "Stream over the Internet\n";
    } else if (received_ == 5) {
        std::cout << "As note sheets\n";
    } else if (received_ == 6) {
        std::cout << "As note sheets in a book with other sheets\n";
    } else if (received_ == 7) {
        std::cout << "Music on other media\n";
    } else if (received_ == 8) {
        std::cout << "Non-musical merchandise\n";
    }

    std::cout << "Name of seller: " << seller_name_ << '\n';
    std::cout << "Description: " << description_ << '\n';
}

COMR* ReadCOMR(std::istream& file, const FrameHeader& frame_header) {
    uint32_t i = 1;
    std::string price;
    std::string valid_time;
    std::string URL;
    uint8_t received;
    std::string seller_name;
    std::string description;
    std::string picture_type;

    char byte;
    file.read(&byte, 1);
    uint8_t encoding = byte;

    do {
        file.read(&byte, 1);
        price += byte;
        i++;
    } while (byte != 0);

    for (int j = 0; j < 8; ++j) {
        file.read(&byte, 1);
        valid_time += byte;
        i++;
    }

    do {
        file.read(&byte, 1);
        URL += byte;
        i++;
    } while (byte != 0);

    file.read(&byte, 1);
    received = byte;

    do {
        file.read(&byte, 1);
        seller_name += byte;
        i++;
    } while (byte != 0);

    do {
        file.read(&byte, 1);
        description += byte;
        i++;
    } while (byte != 0);

    do {
        file.read(&byte, 1);
        picture_type += byte;
        i++;
    } while (byte != 0);

    int skip = frame_header.size_ - i;
    file.seekg(skip, std::ios::cur);

    COMR* frame = new COMR(frame_header, encoding, price, valid_time, URL, received, seller_name, description, picture_type);
    return frame;
}
