cmake_minimum_required(VERSION 3.23)
project(labwork_7_mishapolyakov111)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(labwork_7_mishapolyakov111
        Frames/AbstractFrame/Frame.cpp
        Frames/AbstractFrame/Frame.h

        Frames/TextFrame/TextFrame.cpp
        Frames/TextFrame/TextFrame.h

        Frames/TextFrame/TXXX.cpp
        Frames/TextFrame/TXXX.h

        Frames/URLFrame/URLFrame.cpp
        Frames/URLFrame/URLFrame.h

        Frames/URLFrame/WXXX.cpp
        Frames/URLFrame/WXXX.h

        Frames/UFID/UFID.cpp
        Frames/UFID/UFID.h

        Frames/USER/USER.cpp
        Frames/USER/USER.h

        Frames/USLT/USLT.cpp
        Frames/USLT/USLT.h

        Tags/Tag.cpp
        Tags/Tag.h

        Tags/TagHeader.cpp
        Tags/TagHeader.h

        main.cpp

        Frames/SEEK/SEEK.cpp
        Frames/SEEK/SEEK.h

        Frames/COMM/COMM.cpp
        Frames/COMM/COMM.h

        Frames/OWNE/OWNE.cpp
        Frames/OWNE/OWNE.h

        Frames/PRIV/PRIV.cpp
        Frames/PRIV/PRIV.h

        Frames/PCNT/PCNT.cpp
        Frames/PCNT/PCNT.h

        Frames/LINK/LINK.cpp
        Frames/LINK/LINK.h

        Frames/ENCR/ENCR.cpp
        Frames/ENCR/ENCR.h

        Frames/COMR/COMR.cpp
        Frames/COMR/COMR.h

        Frames/GRID/GRID.cpp
        Frames/GRID/GRID.h

        Frames/RBUF/RBUF.cpp
        Frames/RBUF/RBUF.h

        Frames/POPM/POPM.cpp
        Frames/POPM/POPM.h

        Frames/POSS/POSS.cpp
        Frames/POSS/POSS.h Frames/EQU2/EQU2.cpp Frames/EQU2/EQU2.h Frames/ETCO/ETCO.cpp Frames/ETCO/ETCO.h)
