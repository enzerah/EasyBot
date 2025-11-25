#ifndef CUSTOM_FUNCTIONS_H
#define CUSTOM_FUNCTIONS_H
#include <stdint.h>
#include <string>
#include "../../../const.h"
struct StackArgs {
    std::string* name;
    uintptr_t* level;
    Otc::MessageMode* mode;
    std::string* text;
    uint16_t* channelId;
    Position* pos;
};


void processTalk(std::string name, uint16_t level, Otc::MessageMode mode, std::string text, uint16_t channelId, const Position& pos);




#endif //CUSTOM_FUNCTIONS_H
