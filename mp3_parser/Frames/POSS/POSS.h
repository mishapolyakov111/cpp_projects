#pragma once

#include "Frames/AbstractFrame/Frame.h"

class POSS : public Frame {
    uint8_t time_stamp_;
    uint32_t position_;
public:
    POSS() = default;
    ~POSS() override = default;

    POSS(const FrameHeader& frame_header,
         uint8_t time_stamp, uint32_t position)
            : Frame(frame_header), time_stamp_(time_stamp), position_(position) {}

    void GetInfo() const override;
};

POSS* ReadPOSS(std::istream& file, const FrameHeader& frame_header);
