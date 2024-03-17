#pragma once

#include "Frames/AbstractFrame/Frame.h"

class SEEK : public Frame {
private:
    uint32_t offset_{};
public:
    SEEK() = default;
    ~SEEK() override = default;

    SEEK(const FrameHeader& frame_header, uint32_t offset)
            : Frame(frame_header), offset_(offset) {}

    void GetInfo() const override;
};

SEEK* ReadSEEK(std::istream& file, const FrameHeader& frame_header);
