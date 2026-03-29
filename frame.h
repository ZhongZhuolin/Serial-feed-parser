#pragma once

#include <cstdint>

struct Frame
{
    uint8_t id;
    uint8_t length;
    uint8_t payload[256];
    uint8_t crc;
};

enum class State
{
    IDLE,
    GOT_START,
    GOT_ID,
    GOT_LEN,
    READING,
    VALIDATE
};