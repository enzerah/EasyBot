//
// Created by Wojciech on 03.10.2025.
//

#include "Container.h"

Container* Container::instance{nullptr};
std::mutex Container::mutex;

Container::Container()
{
}

Container* Container::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new Container();
    }

    return instance;
}

uintptr_t Container::getItem(uintptr_t container, uint8_t slot) {
    if (!container) return 0;
    typedef uintptr_t*(gameCall* GetItem)(
        uintptr_t a1,
        void *a2,
        uint8_t slot
        );
    auto function = reinterpret_cast<GetItem>(ClassMemberFunctions["Container.getItem"]);
    return g_dispatcher->scheduleEventEx([function, container, slot]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(container, &pMysteryPtr, slot);
        return *ret;
    });
}


std::deque<uintptr_t> Container::getItems(uintptr_t container) {
    if (!container) return {};
    typedef std::deque<uintptr_t>*(gameCall* GetItems)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetItems>(ClassMemberFunctions["Container.getItems"]);
    return g_dispatcher->scheduleEventEx([function, container]() {
        std::deque<uintptr_t> test;
        void* pMysteryPtr = nullptr;
        auto ret = function(container, &pMysteryPtr);
        return *ret;
    });
}

int Container::getItemsCount(uintptr_t container) {
    if (!container) return 0;
    typedef int(gameCall* GetItemsCount)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetItemsCount>(ClassMemberFunctions["Container.getItemsCount"]);
    return g_dispatcher->scheduleEventEx([function, container]() {
        void* pMysteryPtr = nullptr;
        return function(container, &pMysteryPtr);
    });
}

Position Container::getSlotPosition(uintptr_t container, int slot) {
    if (!container) return {};
    typedef Position*(gameCall* GetSlotPosition)(
        uintptr_t RCX,
        void *RDX,
        int slot
        );
    auto function = reinterpret_cast<GetSlotPosition>(ClassMemberFunctions["Container.getSlotPosition"]);
    return g_dispatcher->scheduleEventEx([function, container, slot]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(container, &pMysteryPtr, slot);
        return *ret;
    });
}

std::string Container::getName(uintptr_t container) {
    if (!container) return "";
    typedef std::string*(gameCall* GetName)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetName>(ClassMemberFunctions["Container.getName"]);
    return g_dispatcher->scheduleEventEx([function, container]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(container, &pMysteryPtr);
        const char* name_data = ret->c_str();
        char temp_buffer[256];
        strncpy_s(temp_buffer, name_data, 255);
        temp_buffer[255] = '\0';
        std::string name(temp_buffer);
        return name;
    });
}

int Container::getId(uintptr_t container) {
    if (!container) return 0;
    typedef int(gameCall* GetId)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetId>(ClassMemberFunctions["Container.getId"]);
    return g_dispatcher->scheduleEventEx([function, container]() {
        void* pMysteryPtr = nullptr;
        return function(container, &pMysteryPtr);
    });
}

uintptr_t Container::getContainerItem(uintptr_t container) {
    if (!container) return 0;
    typedef uintptr_t*(gameCall* GetContainerItem)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetContainerItem>(ClassMemberFunctions["Container.getContainerItem"]);
    return g_dispatcher->scheduleEventEx([function, container]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(container, &pMysteryPtr);
        return *ret;
    });
}

bool Container::hasParent(uintptr_t container) {
    if (!container) return 0;
    typedef bool(gameCall* HasParent)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<HasParent>(ClassMemberFunctions["Container.hasParent"]);
    return g_dispatcher->scheduleEventEx([function, container]() {
        void* pMysteryPtr = nullptr;
        return function(container, &pMysteryPtr);
    });
}

int Container::getSize(uintptr_t container) {
    if (!container) return 0;
    typedef int(gameCall* GetSize)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetSize>(ClassMemberFunctions["Container.getSize"]);
    return g_dispatcher->scheduleEventEx([function, container]() {
            void* pMysteryPtr = nullptr;
            return function(container, &pMysteryPtr);
    });
}

int Container::getFirstIndex(uintptr_t container) {
    if (!container) return 0;
    typedef int(gameCall* GetFirstIndex)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetFirstIndex>(ClassMemberFunctions["Container.getFirstIndex"]);
    return g_dispatcher->scheduleEventEx([function, container]() {
            void* pMysteryPtr = nullptr;
            return function(container, &pMysteryPtr);
    });
}

