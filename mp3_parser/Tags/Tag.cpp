#pragma once

#include "Tag.h"

FrameFlags ReadFrameFlags(char* buf) {
    std::bitset<8> first = buf[0];
    std::bitset<8> second = buf[1];

    FrameFlags frame_flags{};
    frame_flags.tag_alter_preservation_ = first.test(6);
    frame_flags.file_alter_preservation_ = first.test(5);
    frame_flags.read_only_ = first.test(4);
    frame_flags.grouping_identity_ = second.test(6);
    frame_flags.compression_ = second.test(3);
    frame_flags.encryption_ = second.test(2);
    frame_flags.unsynchronisation_ = second.test(1);
    frame_flags.data_length_indicator_ = second.test(0);

    return frame_flags;
}

bool IsSupported(const std::string& id) {
    return id != "AENC" and id != "APIC" and id != "ASPI" and id != "GEOB"
           and id != "MCDI" and id != "MLLT" and id != "RVRB"
           and id != "SIGN" and id != "SYTC" and id != "TFLT"
           and id != "TMED" and id != "SYLT" and id != "RVA2";
}

bool IsPadding(const std::string& id) {
    return id[0] == 0 and id[1] == 0 and id[2] == 0 and id[3] == 0;
}

void Tag::ReadFrames(std::fstream& mp3_file) {
    uint32_t i = 0;
    char byte;
    while (i < header_.TagSize()) {
        FrameHeader frame_header{};

        for (int j = 0; j < ID_SIZE; ++j) {
            mp3_file.read(&byte, 1);
            frame_header.id_ += byte;
        }

        if (IsPadding(frame_header.id_)) {
            break;
        }

        char size_in_bytes[4];
        mp3_file.read(size_in_bytes, 4);
        frame_header.size_ = GetSize(size_in_bytes);

        char flags[2];
        mp3_file.read(flags, 2);
        frame_header.frame_flags_ = ReadFrameFlags(flags);

        if (IsSupported(frame_header.id_)) {
            Frame* new_frame = ReadCurrentFrame(mp3_file, frame_header);
            frames_.push_back(new_frame);
        } else {
            mp3_file.seekg(frame_header.size_, std::ios::cur);
        }

        i += 10 + frame_header.size_;
    }

}

Frame* ReadCurrentFrame(std::istream& file, const FrameHeader& frame_header) {
    if (frame_header.id_ == "TXXX") {
        return ReadTXXX(file, frame_header);
    } else if (frame_header.id_[0] == 'T') {
        return ReadTextFrame(file, frame_header);
    } else if (frame_header.id_ == "WXXX") {
        return ReadWXXX(file, frame_header);
    } else if (frame_header.id_[0] == 'W') {
        return ReadURLFrame(file, frame_header);
    } else if (frame_header.id_ == "UFID") {
        return ReadUFID(file, frame_header);
    } else if (frame_header.id_ == "USER") {
        return ReadUSER(file, frame_header);
    } else if (frame_header.id_ == "USLT") {
        return ReadUSLT(file, frame_header);
    } else if (frame_header.id_ == "COMM") {
        return ReadCOMM(file, frame_header);
    } else if (frame_header.id_ == "SEEK") {
        return ReadSEEK(file, frame_header);
    } else if (frame_header.id_ == "OWNE") {
        return ReadOWNE(file, frame_header);
    } else if (frame_header.id_ == "PRIV") {
        return ReadPRIV(file, frame_header);
    } else if (frame_header.id_ == "LINK") {
        return ReadLINK(file, frame_header);
    } else if (frame_header.id_ == "ENCR") {
        return ReadENCR(file, frame_header);
    } else if (frame_header.id_ == "COMR") {
        return ReadCOMR(file, frame_header);
    } else if (frame_header.id_ == "GRID") {
        return ReadGRID(file, frame_header);
    } else if (frame_header.id_ == "POPM") {
        return ReadPOPM(file, frame_header);
    } else if (frame_header.id_ == "RBUF") {
        return ReadRBUF(file, frame_header);
    } else if (frame_header.id_ == "POSS") {
        return ReadPOSS(file, frame_header);
    } else if (frame_header.id_ == "EQU2") {
        return ReadEQU2(file, frame_header);
    } else if (frame_header.id_ == "EQU2") {
        return ReadPCNT(file, frame_header);
    } else {
        return ReadETCO(file, frame_header);
    }
}

void Tag::Parse(int argc, char** argv) {
    if (argc > 1) {
        std::string file_path = argv[1];
        std::fstream file(file_path, std::fstream::in | std::ios::binary);
        header_.ReadTagHeader(file);
        if (header_.extendedHeader()) {
            header_.ReadExtendedHeader(file);
        }

        ReadFrames(file);
    }
}