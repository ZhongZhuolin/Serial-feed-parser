#pragma once

#include <cstdint>
#include "frame.h"

class FrameParser
{
    public:
        FrameParser();
        void feed(uint8_t byte);
        bool hasFrame() const;
        Frame getFrame() const;
    private:
        State state_;
        Frame frame_;
        uint8_t payload_[256];
        uint8_t bytes_read_;
        bool ready_;

        void reset();
        uint8_t computeCRC() const;
};



