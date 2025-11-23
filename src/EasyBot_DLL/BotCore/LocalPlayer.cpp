//
// Created by Wojciech on 03.10.2025.
//

#include "LocalPlayer.h"
LocalPlayer* LocalPlayer::instance{nullptr};
std::mutex LocalPlayer::mutex;
LocalPlayer::LocalPlayer()
{
}

LocalPlayer* LocalPlayer::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new LocalPlayer();
    }
    return instance;
}

uint32_t LocalPlayer::getStates(uintptr_t localPlayer) {
    if (!localPlayer) return 0;
    typedef uint32_t(gameCall* GetStates)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetStates>(ClassMemberFunctions["LocalPlayer.getStates"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer, &pMysteryPtr);
    });
}

double LocalPlayer::getHealth(uintptr_t localPlayer) {
    if (!localPlayer) return 0;
    typedef double(gameCall* GetHealth)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetHealth>(ClassMemberFunctions["LocalPlayer.getHealth"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer, &pMysteryPtr);
    });
}

double LocalPlayer::getMaxHealth(uintptr_t localPlayer) {
    if (!localPlayer) return 0;
    typedef double(gameCall* GetMaxHealth)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetMaxHealth>(ClassMemberFunctions["LocalPlayer.getMaxHealth"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer, &pMysteryPtr);
    });
}

double LocalPlayer::getFreeCapacity(uintptr_t localPlayer) {
    if (!localPlayer) return 0;
    typedef double(gameCall* GetFreeCapacity)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetFreeCapacity>(ClassMemberFunctions["LocalPlayer.getFreeCapacity"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer, &pMysteryPtr);
    });
}

uint16_t LocalPlayer::getLevel(uintptr_t localPlayer) {
    if (!localPlayer) return 0;
    typedef uint16_t(gameCall* GetLevel)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetLevel>(ClassMemberFunctions["LocalPlayer.getLevel"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer, &pMysteryPtr);
    });
}

double LocalPlayer::getMana(uintptr_t localPlayer) {
    if (!localPlayer) return 0;
    typedef double(gameCall* GetMana)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetMana>(ClassMemberFunctions["LocalPlayer.getMana"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer, &pMysteryPtr);
    });
}

double LocalPlayer::getMaxMana(uintptr_t localPlayer) {
    if (!localPlayer) return 0;
    typedef double(gameCall* GetMaxMana)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetMaxMana>(ClassMemberFunctions["LocalPlayer.getMaxMana"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer, &pMysteryPtr);
    });
}

uint8_t LocalPlayer::getSoul(uintptr_t localPlayer) {
    if (!localPlayer) return 0;
    typedef uint8_t(gameCall* GetSoul)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetSoul>(ClassMemberFunctions["LocalPlayer.getSoul"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer, &pMysteryPtr);
    });
}

uint16_t LocalPlayer::getStamina(uintptr_t localPlayer) {
    if (!localPlayer) return 0;
    typedef uint16_t(gameCall* GetStamina)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetStamina>(ClassMemberFunctions["LocalPlayer.getStamina"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer, &pMysteryPtr);
    });
}

bool LocalPlayer::hasSight(uintptr_t localPlayer, const Position &pos) {
    if (!localPlayer) return 0;
    typedef bool(gameCall* HasSight)(
        uintptr_t RCX,
        void *RDX,
        const Position pos
        );
    auto function = reinterpret_cast<HasSight>(ClassMemberFunctions["LocalPlayer.hasSight"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer, pos]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer, &pMysteryPtr, pos);
    });
}

bool LocalPlayer::isAutoWalking(uintptr_t localPlayer) {
    if (!localPlayer) return 0;
    typedef bool(gameCall* IsAutoWalking)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<IsAutoWalking>(ClassMemberFunctions["LocalPlayer.isAutoWalking"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer, &pMysteryPtr);
    });
}

void LocalPlayer::stopAutoWalk(uintptr_t localPlayer) {
    if (!localPlayer) return;
    typedef void(gameCall* StopAutoWalk)(
        uintptr_t RCX
        );
    auto function = reinterpret_cast<StopAutoWalk>(ClassMemberFunctions["LocalPlayer.stopAutoWalk"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        return function(localPlayer);
    });
}

bool LocalPlayer::autoWalk(uintptr_t localPlayer, const Position &destination, bool retry) {
    if (!localPlayer) return 0;
    typedef bool(gameCall* AutoWalk)(
        uintptr_t RCX,
        const Position pos,
        bool retry
        );
    auto function = reinterpret_cast<AutoWalk>(ClassMemberFunctions["LocalPlayer.autoWalk"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer, destination, retry]() {
        return function(localPlayer, destination, retry);
    });
}

