//
// Created by Wojciech on 04.10.2025.
//

#include "Item.h"
Item* Item::instance{nullptr};
std::mutex Item::mutex;
Item::Item()
{
}

Item* Item::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new Item();
    }
    return instance;
}

std::string Item::getName(uintptr_t item) {
    if (!item) return 0;
    typedef std::string*(gameCall* GetName)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetName>(ClassMemberFunctions["Item.getName"]);
    return g_dispatcher->scheduleEventEx([function, item]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(item, &pMysteryPtr);
        const char* name_data = ret->c_str();
        char temp_buffer[256];
        strncpy_s(temp_buffer, name_data, 255);
        temp_buffer[255] = '\0';
        std::string name(temp_buffer);
        return name;
    });
}

std::string Item::getDescription(uintptr_t item) {
    if (!item) return 0;
    typedef std::string*(gameCall* GetDescription)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetDescription>(ClassMemberFunctions["Item.getDescription"]);
    return g_dispatcher->scheduleEventEx([function, item]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(item, &pMysteryPtr);
        const char* name_data = ret->c_str();
        char temp_buffer[256];
        strncpy_s(temp_buffer, name_data, 255);
        temp_buffer[255] = '\0';
        std::string name(temp_buffer);
        return name;
    });
}

int Item::getCount(uintptr_t item) {
    if (!item) return 0;
    typedef int(gameCall* GetCount)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetCount>(ClassMemberFunctions["Item.getCount"]);
    return g_dispatcher->scheduleEventEx([function, item]() {
        void* pMysteryPtr = nullptr;
        return function(item, &pMysteryPtr);
    });
}

int Item::getSubType(uintptr_t item) {
    if (!item) return 0;
    typedef int(gameCall* GetSubType)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetSubType>(ClassMemberFunctions["Item.getSubType"]);
    return g_dispatcher->scheduleEventEx([function, item]() {
        void* pMysteryPtr = nullptr;
        std::cout << pMysteryPtr << std::endl;
        return function(item, &pMysteryPtr);
    });
}

uint32_t Item::getId(uintptr_t item) {
    if (!item) return 0;
    typedef uint32_t(gameCall* GetId)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetId>(ClassMemberFunctions["Item.getId"]);
    return g_dispatcher->scheduleEventEx([function, item]() {
        void* pMysteryPtr = nullptr;
        return function(item, &pMysteryPtr);
    });
}

uint8_t Item::getTier(uintptr_t item) {
    if (!item) return 0;
    typedef uintptr_t*(gameCall* GetTier)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetTier>(ClassMemberFunctions["Item.getTier"]);
    return g_dispatcher->scheduleEventEx([function, item]() {
        void* pMysteryPtr = nullptr;
        return *function(item, &pMysteryPtr);
    });
}

std::string Item::getText(uintptr_t item) {
    if (!item) return 0;
    typedef std::string*(gameCall* GetText)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetText>(ClassMemberFunctions["Item.getText"]);
    return g_dispatcher->scheduleEventEx([function, item]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(item, &pMysteryPtr);
        const char* name_data = ret->c_str();
        char temp_buffer[256];
        strncpy_s(temp_buffer, name_data, 255);
        temp_buffer[255] = '\0';
        std::string name(temp_buffer);
        return name;
    });
}
