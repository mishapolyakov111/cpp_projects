#pragma once

#include "Frames/TextFrame/TextFrame.h"

class TXXX : public TextFrame {
private:
    std::string value_;
public:
    TXXX() = default;
    ~TXXX() override = default;

    TXXX(const FrameHeader& frame_header,
         uint8_t encoding, const std::string& info, const std::string& value)
            : TextFrame(frame_header, encoding, info), value_(value) {}

    void GetInfo() const override;
};

TXXX* ReadTXXX(std::istream& file, const FrameHeader& frame_header);

