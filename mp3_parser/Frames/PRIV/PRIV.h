#pragma once

#include "Frames/AbstractFrame/Frame.h"

class PRIV : public Frame {
private:
    std::string identifier_;
    std::string private_data_;
public:
    PRIV() = default;
    ~PRIV() override = default;
    PRIV(const FrameHeader& frame_header,
         const std::string& identifier, const std::string& private_data)
            : Frame(frame_header), identifier_(identifier), private_data_(private_data){}

    void GetInfo() const override;

};

PRIV* ReadPRIV(std::istream& file, const FrameHeader& frame_header);

