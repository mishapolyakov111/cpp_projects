#pragma once

#include "Frames/AbstractFrame/Frame.h"

class UFID : public Frame {
private:
    std::string owner_identifier_;
    std::string identifier_;
public:
    UFID() = default;
    ~UFID() override = default;

    UFID(const FrameHeader& frame_header,
         const std::string& owner_identifier, const std::string& identifier)
            : Frame(frame_header), owner_identifier_(owner_identifier), identifier_(identifier) {}

    void GetInfo() const override;
};

UFID* ReadUFID(std::istream& file, const FrameHeader& frame_header);

