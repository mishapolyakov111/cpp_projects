#pragma once

#include "Frames/AbstractFrame/Frame.h"

class TextFrame : public Frame {
private:
    uint8_t encoding_{};
    std::string information_;
public:
    TextFrame() = default;
    ~TextFrame() override = default;

    TextFrame(const FrameHeader& frame_header,
              uint8_t encoding, const std::string& info)
            : Frame(frame_header), encoding_(encoding), information_(info) {}

    void GetInfo() const override;
};

TextFrame* ReadTextFrame(std::istream& file, const FrameHeader& frame_header);
