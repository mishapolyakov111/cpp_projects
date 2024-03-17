#pragma once

#include "Frames/AbstractFrame/Frame.h"

class USER : public Frame {
private:
    uint8_t encoding_{};
    std::string language_;
    std::string information_;
public:
    USER() = default;
    ~USER() override = default;

    USER(const FrameHeader& frame_header,
              uint8_t encoding, const std::string& language, const std::string& info)
            : Frame(frame_header), encoding_(encoding), language_(language), information_(info) {}

    void GetInfo() const override;
};

USER* ReadUSER(std::istream& file, const FrameHeader& frame_header);

