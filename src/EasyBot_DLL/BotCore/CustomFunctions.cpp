#include "CustomFunctions.h"
#include <iostream>


CustomFunctions* CustomFunctions::instance{nullptr};
std::mutex CustomFunctions::mutex;

CustomFunctions::CustomFunctions()
{
}

CustomFunctions* CustomFunctions::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new CustomFunctions();
    }

    return instance;
}

void CustomFunctions::onTalk(std::string name, uint16_t level, Otc::MessageMode mode, std::string text,
    uint16_t channelId, const Position &pos) {
    if (messages.size() >= MAX_MESSAGES) {
        messages.erase(messages.begin());
    }
    Message record = {name, level, mode, text, channelId, pos};
    messages.push_back(std::move(record));
}

void CustomFunctions::onOpenChannel(const uint16_t channelId, const std::string name) {
    if (channels.size() >= MAX_CHANNELS) {
        return;
    }
    auto exists = std::find_if(channels.begin(), channels.end(),
        [&](const Channel& ch) {
            return ch.channelId == channelId || ch.channelName == name;
        });

    if (exists != channels.end()) {
        return;
    }
    channels.push_back({ channelId, name });
}

void CustomFunctions::onCloseChannel(uint16_t channelId) {
    channels.erase(
        std::remove_if(
            channels.begin(),
            channels.end(),
            [&](const Channel& ch) {
                return ch.channelId == channelId;
            }
        ),
        channels.end()
    );
}


std::vector<Message> CustomFunctions::getMessages(int messageNumber) {
    size_t count = static_cast<size_t>(messageNumber);
    size_t actual_size = messages.size();
    size_t start_index;
    if (count >= actual_size) {
        start_index = 0;
    } else {
        start_index = actual_size - count;
    }
    return std::vector<Message>(
        messages.begin() + start_index,
        messages.end()
    );
}

std::vector<Channel> CustomFunctions::getChannels() {
    return channels;
}



