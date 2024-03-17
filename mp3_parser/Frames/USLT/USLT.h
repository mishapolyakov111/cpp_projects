#pragma once

#include "Frames/AbstractFrame/Frame.h"

class USLT : public Frame {
private:
    uint8_t encoding_{};
    std::string language_;
    std::string content_descriptor_;
    std::string lyrics_;
public:
    USLT() = default;

    ~USLT() override = default;

    USLT(const FrameHeader& frame_header,
         uint8_t encoding, const std::string& language, const std::string& content_descriptor,
         const std::string& lyrics)
            : Frame(frame_header), encoding_(encoding), language_(language), content_descriptor_(content_descriptor),
              lyrics_(lyrics) {}

    void GetInfo() const override;
};

USLT* ReadUSLT(std::istream& file, const FrameHeader& frame_header);
