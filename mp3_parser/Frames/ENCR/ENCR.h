#pragma once

#include "Frames/AbstractFrame/Frame.h"

class ENCR : public Frame {
private:
    std::string owner_identifier_;
    char method_symbol_;
    std::string encryption_data_;
public:
    ENCR() = default;
    ~ENCR() override = default;
    ENCR(const FrameHeader& frame_header,
         const std::string& owner_identifier, char method_symbol, const std::string& encryption_data)
            : Frame(frame_header), owner_identifier_(owner_identifier), method_symbol_(method_symbol),
              encryption_data_(encryption_data) {}

    void GetInfo() const override;
};

ENCR* ReadENCR(std::istream& file, const FrameHeader& frame_header);
