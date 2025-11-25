#include "custom_functions.h"
#include <iostream>


void processTalk(std::string name, uint16_t level, Otc::MessageMode mode, std::string text,
    uint16_t channelId, const Position &pos) {
    std::cout << name << std::endl;
    std::cout << mode << std::endl;
    std::cout << text<< std::endl;
}