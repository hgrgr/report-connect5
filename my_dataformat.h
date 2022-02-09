#ifndef MY_DATAFORMAT_H
#define MY_DATAFORMAT_H
#include "pch.h"

#pragma pack(push, 1)
struct MyFormat{
    uint8_t cmd;
    uint8_t turn;
    uint8_t data;
};
#pragma pack(pop)

#endif // MY_DATAFORMAT_H
