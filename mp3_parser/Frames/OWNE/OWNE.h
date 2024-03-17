#pragma once

#include "Frames/AbstractFrame/Frame.h"

class OWNE : public Frame {
private:
    uint8_t encoding_{};
    std::string price_;
    std::string date_;
    std::string seller_;
public:
    OWNE() = default;
    ~OWNE() override = default;
    OWNE(const FrameHeader& frame_header,
         uint8_t encoding, const std::string& price, const std::string& date, const std::string& seller)
            : Frame(frame_header), encoding_(encoding), price_(price), date_(date), seller_(seller){}

    void GetInfo() const override;
};

OWNE* ReadOWNE(std::istream& file, const FrameHeader& frame_header);
