#pragma once

#include "Frames/AbstractFrame/Frame.h"

class GRID : public Frame {
private:
    std::string identifier_;
    uint8_t group_symbol_{};
    std::string data_;
public:
    GRID() = default;
    ~GRID() override = default;
    GRID(const FrameHeader& frame_header,
         const std::string& identifier, uint8_t group_symbol, const std::string& data)
            : Frame(frame_header), identifier_(identifier), group_symbol_(group_symbol),
              data_(data) {}

    void GetInfo() const override;
};

GRID* ReadGRID(std::istream& file, const FrameHeader& frame_header);
