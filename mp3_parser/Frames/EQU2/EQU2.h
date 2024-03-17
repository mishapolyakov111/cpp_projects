#pragma once

#include "Frames/AbstractFrame/Frame.h"

class EQU2 : public Frame {
private:
    char interpolation_method_;
    std::string identification_;
public:
    EQU2() = default;
    ~EQU2() override = default;
    EQU2(const FrameHeader& frame_header,
         char interpolation_method, const std::string& identification)
            : Frame(frame_header), interpolation_method_(interpolation_method), identification_(identification) {}

    void GetInfo() const override;
};

EQU2* ReadEQU2(std::istream& file, const FrameHeader& frame_header);
