#pragma once

#include "Frames/AbstractFrame/Frame.h"

class COMM : public Frame {
private:
    uint8_t encoding_{};
    std::string language_;
    std::string descriptor_;
    std::string text_;
public:
    COMM() = default;
    ~COMM() override = default;
    COMM(const FrameHeader& frame_header, uint8_t encoding, const std::string& language,
         const std::string& content_descriptor, const std::string& lyrics)
        : Frame(frame_header),
          encoding_(encoding),
          language_(language),
          descriptor_(content_descriptor),
          text_(lyrics) {}

    void GetInfo() const override;
};

COMM* ReadCOMM(std::istream& file, const FrameHeader& frame_header);
