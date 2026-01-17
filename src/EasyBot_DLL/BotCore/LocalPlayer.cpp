#include "LocalPlayer.h"
LocalPlayer* LocalPlayer::instance{nullptr};
std::mutex LocalPlayer::mutex;


LocalPlayer* LocalPlayer::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new LocalPlayer();
    }
    return instance;
}

bool LocalPlayer::isWalkLocked(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef bool(gameCall* IsWalkLocked)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<IsWalkLocked>(ClassMemberFunctions["LocalPlayer.isWalkLocked"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

uint32_t LocalPlayer::getStates(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef uint32_t(gameCall* GetStates)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetStates>(ClassMemberFunctions["LocalPlayer.getStates"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

double LocalPlayer::getHealth(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef double(gameCall* GetHealth)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetHealth>(ClassMemberFunctions["LocalPlayer.getHealth"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

double LocalPlayer::getMaxHealth(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef double(gameCall* GetMaxHealth)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetMaxHealth>(ClassMemberFunctions["LocalPlayer.getMaxHealth"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

double LocalPlayer::getFreeCapacity(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef double(gameCall* GetFreeCapacity)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetFreeCapacity>(ClassMemberFunctions["LocalPlayer.getFreeCapacity"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

uint16_t LocalPlayer::getLevel(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef uint16_t(gameCall* GetLevel)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetLevel>(ClassMemberFunctions["LocalPlayer.getLevel"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

double LocalPlayer::getMana(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef double(gameCall* GetMana)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetMana>(ClassMemberFunctions["LocalPlayer.getMana"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

double LocalPlayer::getMaxMana(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef double(gameCall* GetMaxMana)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetMaxMana>(ClassMemberFunctions["LocalPlayer.getMaxMana"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

uint32_t LocalPlayer::getManaShield(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef uint32_t(gameCall* GetManaShield)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetManaShield>(ClassMemberFunctions["LocalPlayer.getManaShield"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

uint8_t LocalPlayer::getSoul(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef uint8_t(gameCall* GetSoul)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetSoul>(ClassMemberFunctions["LocalPlayer.getSoul"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

uint16_t LocalPlayer::getStamina(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef uint16_t(gameCall* GetStamina)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetStamina>(ClassMemberFunctions["LocalPlayer.getStamina"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

ItemPtr LocalPlayer::getInventoryItem(LocalPlayerPtr localPlayer, Otc::InventorySlot inventorySlot) {
    if (!localPlayer) return 0;
    typedef void(gameCall* GetInventoryItem)(
        uintptr_t RCX,
        ItemPtr *RDX,
        Otc::InventorySlot inventorySlot
        );
    auto function = reinterpret_cast<GetInventoryItem>(ClassMemberFunctions["LocalPlayer.getInventoryItem"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer, inventorySlot]() {
        ItemPtr result;
        function(localPlayer.address, &result, inventorySlot);
        return result;
    });
}

bool LocalPlayer::hasEquippedItemId(LocalPlayerPtr localPlayer, uint16_t itemId, uint8_t tier) {
    if (!localPlayer) return 0;
    typedef bool(gameCall* HasEquippedItemId)(
        uintptr_t RCX,
        void *RDX,
        uint16_t itemId,
        uint8_t tier
        );
    auto function = reinterpret_cast<HasEquippedItemId>(ClassMemberFunctions["LocalPlayer.hasEquippedItemId"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer, itemId, tier]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr, itemId, tier);
    });
}

int LocalPlayer::getInventoryCount(LocalPlayerPtr localPlayer, uint16_t itemId, uint8_t tier) {
    if (!localPlayer) return 0;
    typedef int(gameCall* GetInventoryCount)(
        uintptr_t RCX,
        void *RDX,
        uint16_t itemId,
        uint8_t tier
        );
    auto function = reinterpret_cast<GetInventoryCount>(ClassMemberFunctions["LocalPlayer.getInventoryCount"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer, itemId, tier]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr, itemId, tier);
    });
}

bool LocalPlayer::hasSight(LocalPlayerPtr localPlayer, const Position &pos) {
    if (!localPlayer) return 0;
    typedef bool(gameCall* HasSight)(
        uintptr_t RCX,
        void *RDX,
        const Position *pos
        );
    auto function = reinterpret_cast<HasSight>(ClassMemberFunctions["LocalPlayer.hasSight"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer, pos]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr, &pos);
    });
}

bool LocalPlayer::isAutoWalking(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return 0;
    typedef bool(gameCall* IsAutoWalking)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<IsAutoWalking>(ClassMemberFunctions["LocalPlayer.isAutoWalking"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        void* pMysteryPtr = nullptr;
        return function(localPlayer.address, &pMysteryPtr);
    });
}

void LocalPlayer::stopAutoWalk(LocalPlayerPtr localPlayer) {
    if (!localPlayer) return;
    typedef void(gameCall* StopAutoWalk)(
        uintptr_t RCX
        );
    auto function = reinterpret_cast<StopAutoWalk>(ClassMemberFunctions["LocalPlayer.stopAutoWalk"]);
    return g_dispatcher->scheduleEventEx([function, localPlayer]() {
        return function(localPlayer.address);
    });
}

bool LocalPlayer::autoWalk(LocalPlayerPtr localPlayer, const Position &destination, bool retry) {
    if (!localPlayer) return 0;
    if (BuildOption == Exordion || BuildOption == Treasura) {
        typedef bool(gameCall* AutoWalk)(
            uintptr_t RCX,
            Position RDX,
            bool R8
            );
        auto function = reinterpret_cast<AutoWalk>(ClassMemberFunctions["LocalPlayer.autoWalk"]);
        return g_dispatcher->scheduleEventEx([function, localPlayer, destination, retry]() {
            return function(localPlayer.address, destination, retry);
        });
    }
    if (BuildOption == Dbl) {
        typedef bool(gameCall* AutoWalk)(
            uintptr_t RCX,
            const Position *RDX,
            bool R8
        );
        auto function = reinterpret_cast<AutoWalk>(ClassMemberFunctions["LocalPlayer.autoWalk"]);
        return g_dispatcher->scheduleEventEx([function, localPlayer, destination, retry]() {
            return function(localPlayer.address, &destination, retry);
        });
    }
}

void LocalPlayer::setLightHack(LocalPlayerPtr localPlayer, uint16_t lightLevel) {
    if (!localPlayer) return;
    g_dispatcher->scheduleEventEx([localPlayer, lightLevel]() {
        auto lightPtr = reinterpret_cast<uint16_t*>(localPlayer.address + lightHackOffset);
        if (*lightPtr != lightLevel) *lightPtr = lightLevel;
    });
}


