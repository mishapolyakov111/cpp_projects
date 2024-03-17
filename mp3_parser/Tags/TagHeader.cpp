#include "TagHeader.h"

TagFlags GetFlagsFromByte(char byte) {
    TagFlags flags{};
    std::bitset<8> bits = byte;

    flags.unsynchronisation_ = bits.test(7);
    flags.extended_header_ = bits.test(6);
    flags.experimental_indicator_ = bits.test(5);
    flags.footer_present_ = bits.test(4);

    return flags;
}

uint32_t GetSize(char* size) {
    std::bitset<8> bits;
    std::string size_binary;
    for (int i = 0; i < LENGTH_OF_SIZE; ++i) {
        bits = size[i];
        size_binary += bits.to_string().substr(1);
    }

    std::bitset<32> tmp {size_binary};
    uint32_t result = tmp.to_ulong();
    return result;
}

void TagHeader::ReadTagHeader(std::fstream& mp3_file) {
    char identifier[3];
    mp3_file.read(identifier, 3);
    identifier_ += identifier[0];
    identifier_ += identifier[1];
    identifier_ += identifier[2];

    char version;
    mp3_file.read(&version, 1);
    version_ = version;

    mp3_file.read(&version, 1);
    char flags;
    mp3_file.read(&flags, 1);
    TagFlags tag_flags = GetFlagsFromByte(flags);
    flags_ = tag_flags;

    char tag_size[4];
    mp3_file.read(tag_size, 4);
    size_ = GetSize(tag_size);
}

uint32_t TagHeader::TagSize() const {
    return size_;
}

bool TagHeader::extendedHeader() const {
    return flags_.extended_header_;
}

void TagHeader::ReadExtendedHeader(std::fstream& file) {
    char tag_size[4];
    file.read(tag_size, 4);
    extended_header_.size_ = GetSize(tag_size);

    char flags;
    file.read(&flags, 1);
    std::bitset<8> bits = flags;
    extended_header_.tag_is_an_update_ = bits[6];
    extended_header_.CRC_data_present_ = bits[5];
    extended_header_.tag_restrictions_ = bits[4];

    char byte;
    for (int i = 0; i < extended_header_.size_ - sizeof(uint32_t) - sizeof(char); ++i) {
        file.read(&byte, 1);
        extended_header_.flags_data_ += byte;
    }
}
