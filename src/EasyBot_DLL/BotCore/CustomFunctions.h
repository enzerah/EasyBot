#ifndef CUSTOM_FUNCTIONS_H
#define CUSTOM_FUNCTIONS_H
#include <mutex>
#include <stdint.h>
#include <string>
#include <vector>
#include "../../../const.h"
#define g_custom CustomFunctions::getInstance()

struct StackArgs {
    std::string* name;
    uintptr_t* level;
    Otc::MessageMode* mode;
    std::string* text;
    uint16_t* channelId;
    Position* pos;
};

struct Message {
    std::string name;
    uint16_t level;
    Otc::MessageMode mode;
    std::string text;
    uint16_t channelId;
    Position pos;
};

class CustomFunctions{
private:
    static CustomFunctions* instance;
    static std::mutex mutex;
    std::vector<Message> messages;
protected:
        CustomFunctions();
    ~CustomFunctions(){}
public:
    CustomFunctions(CustomFunctions const&) = delete;
    void operator=(const CustomFunctions&) = delete;
    static CustomFunctions* getInstance();


    void onTalk(std::string name, uint16_t level, Otc::MessageMode mode, std::string text, uint16_t channelId, const Position& pos);

    std::vector<Message> getMessages(int messageNumber);
};






#endif //CUSTOM_FUNCTIONS_H
