#pragma once

#include "Frames/AbstractFrame/Frame.h"

class LINK : public Frame {
private:
    std::string frame_identifier_;
    std::string URL_;
    std::string additional_data_;
public:
    LINK() = default;
    ~LINK() override = default;
    LINK(const FrameHeader& frame_header,
         const std::string& frame_identifier, const std::string& URL, const std::string& additional_data)
            : Frame(frame_header), frame_identifier_(frame_identifier), URL_(URL), additional_data_(additional_data) {}

    void GetInfo() const override;
};

LINK* ReadLINK(std::istream& file, const FrameHeader& frame_header);

