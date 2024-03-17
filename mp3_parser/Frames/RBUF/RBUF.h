#pragma once

#include "Frames/AbstractFrame/Frame.h"

class RBUF : public Frame {
    uint32_t buffer_size_;
    bool embedded_info_flag_;
    uint32_t offset_;
public:
    RBUF() = default;
    ~RBUF() override = default;

    RBUF(const FrameHeader& frame_header,
         uint32_t buffer_size, bool embedded_info_flag, uint32_t offset)
            : Frame(frame_header), buffer_size_(buffer_size), embedded_info_flag_(embedded_info_flag), offset_(offset) {}

    void GetInfo() const override;
};

RBUF* ReadRBUF(std::istream& file, const FrameHeader& frame_header);


