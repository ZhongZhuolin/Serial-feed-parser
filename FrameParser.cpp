#include "FrameParser.h"

FrameParser::FrameParser()
{

    reset();
}

void FrameParser::feed(uint8_t byte)
{
    switch (state_)
    {
        case State::IDLE:
            if(byte == 0xAA)
            {
                state_ = State::GOT_START;
            }
            break;
        case State::GOT_START:
            frame_.id = byte;
            state_ = State::GOT_ID;
            break;
            
        case State::GOT_ID:
            frame_.length = byte;
            bytes_read_ = 0;
            state_ = State::GOT_LEN;
            break;
      
        case State::GOT_LEN:
            payload_[bytes_read_++] = byte;
            if (bytes_read_ == frame_.length)
                state_ = State::VALIDATE;
            break;
            
        case State::VALIDATE:
            if(byte == computeCRC())
            {
                for(int i = 0; i < frame_.length; i++)
                {
                    frame_.payload[i] = payload_[i];
                }
                ready_ = true;
            }
            reset();
            break;

    }
}

bool FrameParser::hasFrame() const {
    return ready_;
}

Frame FrameParser::getFrame() const {
    return frame_;
}

void FrameParser::reset() {
    state_ = State::IDLE;
    bytes_read_ = 0;
    ready_ = false;
}

uint8_t FrameParser::computeCRC() const {
    uint8_t crc = 0;
    for (int i = 0; i < frame_.length; i++)
        crc ^= payload_[i];
    return crc;
}