#pragma once

#include "Frames/COMM/COMM.h"
#include "Frames/COMR/COMR.h"
#include "Frames/ENCR/ENCR.h"
#include "Frames/ETCO/ETCO.h"
#include "Frames/EQU2/EQU2.h"
#include "Frames/GRID/GRID.h"
#include "Frames/LINK/LINK.h"
#include "Frames/OWNE/OWNE.h"
#include "Frames/PCNT/PCNT.h"
#include "Frames/POPM/POPM.h"
#include "Frames/POSS/POSS.h"
#include "Frames/PRIV/PRIV.h"
#include "Frames/RBUF/RBUF.h"
#include "Frames/SEEK/SEEK.h"
#include "Frames/TextFrame/TextFrame.h"
#include "Frames/TextFrame/TXXX.h"
#include "Frames/URLFrame/URLFrame.h"
#include "Frames/URLFrame/WXXX.h"
#include "Frames/UFID/UFID.h"
#include "Frames/USER/USER.h"
#include "Frames/USLT/USLT.h"
#include "TagHeader.h"

#include <fstream>
#include <vector>

const uint8_t ID_SIZE = 4;
const uint32_t HEADER_SIZE = 10;

class Tag {
private:
    TagHeader header_;
public:
    ~Tag() = default;
    std::vector<Frame*> frames_;
    void Parse(int argc, char** argv);
    void ReadFrames(std::fstream& file);
};

Frame* ReadCurrentFrame(std::istream &file, const FrameHeader& frame_header);