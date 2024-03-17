#pragma once

#include "Frames/AbstractFrame/Frame.h"

class ETCO : public Frame {
private:
    char time_stamp_format_;
    std::string data_;
public:
    ETCO() = default;
    ~ETCO() override = default;
    ETCO(const FrameHeader& frame_header,
         char time_stamp_format, const std::string& data)
            : Frame(frame_header), time_stamp_format_(time_stamp_format),
              data_(data) {}

    void GetInfo() const override;
};

ETCO* ReadETCO(std::istream& file, const FrameHeader& frame_header);
