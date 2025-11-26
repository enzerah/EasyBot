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

struct Channel
{
    uint16_t channelId;
    std::string channelName;
};

class CustomFunctions{
private:
    static CustomFunctions* instance;
    static std::mutex mutex;
    std::vector<Message> messages;
    std::vector<Channel> channels;

    const size_t MAX_MESSAGES = 100;
    const size_t MAX_CHANNELS = 15;
protected:
        CustomFunctions();
    ~CustomFunctions(){}
public:
    CustomFunctions(CustomFunctions const&) = delete;
    void operator=(const CustomFunctions&) = delete;
    static CustomFunctions* getInstance();


    void onTalk(std::string name, uint16_t level, Otc::MessageMode mode, std::string text, uint16_t channelId, const Position& pos);
    void onOpenChannel(uint16_t channelId, std::string name);
    void onCloseChannel(uint16_t channelId);

    std::vector<Message> getMessages(int messageNumber);
    std::vector<Channel> getChannels();
};






#endif //CUSTOM_FUNCTIONS_H
