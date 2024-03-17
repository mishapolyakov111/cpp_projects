#pragma once

#include "Frames/AbstractFrame/Frame.h"

class POPM : public Frame {
private:
    std::string email_;
    uint8_t rating_;
    uint64_t counter_;
public:
    POPM() = default;
    ~POPM() override = default;
    POPM(const FrameHeader& frame_header,
         const std::string& email, uint8_t rating, uint64_t counter)
            : Frame(frame_header), email_(email), rating_(rating),
              counter_(counter) {}

    void GetInfo() const override;
};

POPM* ReadPOPM(std::istream& file, const FrameHeader& frame_header);

