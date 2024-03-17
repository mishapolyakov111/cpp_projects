#pragma once

#include "Frames/AbstractFrame/Frame.h"

class COMR : public Frame {
private:
    uint8_t encoding_;
    std::string price_;
    std::string valid_time_;
    std::string URL_;
    uint8_t received_;
    std::string seller_name_;
    std::string description_;
    std::string picture_type_;
public:
    COMR() = default;
    ~COMR() override = default;
    COMR(const FrameHeader& frame_header,
         uint8_t encoding, const std::string& price, const std::string& date, const std::string& URL,
         uint8_t received, const std::string& seller_name, const std::string& description, const std::string& picture_type)
            : Frame(frame_header), encoding_(encoding), price_(price), valid_time_(date)
            , URL_(URL), received_(received), seller_name_(seller_name), description_(description), picture_type_(picture_type){}

    void GetInfo() const override;
};

COMR* ReadCOMR(std::istream& file, const FrameHeader& frame_header);
