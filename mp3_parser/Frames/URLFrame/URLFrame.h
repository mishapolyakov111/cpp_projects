#pragma once

#include "Frames/AbstractFrame/Frame.h"

class URLFrame : public Frame {
private:
    std::string URL_;
public:
    URLFrame() = default;
    ~URLFrame() override = default;

    URLFrame(const FrameHeader& frame_header,
             const std::string& URL)
            : Frame(frame_header),  URL_(URL) {}

    void GetInfo() const override;
};

URLFrame* ReadURLFrame(std::istream& file, const FrameHeader& frame_header);

