#pragma once

#include <bitset>
#include <fstream>
#include <string>

const uint8_t LENGTH_OF_SIZE = 4;

struct TagFlags{
    bool unsynchronisation_;
    bool extended_header_;
    bool experimental_indicator_;
    bool footer_present_;
};

struct ExtendedHeader {
    uint32_t size_;
    bool tag_is_an_update_;
    bool CRC_data_present_;
    bool tag_restrictions_;
    std::string flags_data_;
};

class TagHeader {
private:
    std::string identifier_;
    uint8_t version_{};
    TagFlags flags_{};
    uint32_t size_{};
    ExtendedHeader extended_header_{};
public:
    void ReadTagHeader(std::fstream& file);
    void ReadExtendedHeader(std::fstream& file);

    uint32_t TagSize() const;
    bool extendedHeader() const;
};

uint32_t GetSize(char* size);

