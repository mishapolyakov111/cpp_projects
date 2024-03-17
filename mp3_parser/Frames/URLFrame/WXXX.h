#pragma once

#include "URLFrame.h"

class WXXX : public URLFrame {
private:
    uint8_t encoding_;
    std::string description_;
public:
    WXXX() = default;
    ~WXXX() override = default;

    WXXX(const FrameHeader& frame_header,
         uint8_t encoding, const std::string& URL, const std::string& description)
            : URLFrame(frame_header, URL), description_(description) {}

    void GetInfo() const override;
};

WXXX* ReadWXXX(std::istream& file, const FrameHeader& frame_header);
