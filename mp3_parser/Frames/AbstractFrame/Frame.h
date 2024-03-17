#pragma once

#include <bitset>
#include <iostream>
#include <string>
#include <vector>

struct FrameFlags {
    bool tag_alter_preservation_;
    bool file_alter_preservation_;
    bool read_only_;
    bool grouping_identity_;
    bool compression_;
    bool encryption_;
    bool unsynchronisation_;
    bool data_length_indicator_;
};

struct FrameHeader {
    std::string id_;
    uint32_t size_;
    FrameFlags frame_flags_;
};


class Frame {
private:
    std::string ID_;
    uint32_t size_{};
    FrameFlags flags_{};
public:
    Frame() = default;
    Frame(const FrameHeader& frame_header)
        : ID_(frame_header.id_), size_(frame_header.size_), flags_(frame_header.frame_flags_){};
    virtual ~Frame() = default;
    virtual void GetInfo() const;

};




