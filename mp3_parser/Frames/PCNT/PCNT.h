#pragma once

#include "Frames/AbstractFrame/Frame.h"

class PCNT : public Frame {
private:
    uint64_t counter_;
public:
    PCNT() = default;
    ~PCNT() override = default;
    PCNT(const FrameHeader& frame_header, uint64_t cnt)
            : Frame(frame_header), counter_(cnt){}

    void GetInfo() const override;
};

PCNT* ReadPCNT(std::istream& file, const FrameHeader& frame_header);

