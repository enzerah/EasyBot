//
// Created by Wojciech on 03.10.2025.
//

#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H
#define g_localPlayer LocalPlayer::getInstance()
#include <mutex>
#include "Map.h"


class LocalPlayer : public Map {
private:
    static LocalPlayer* instance;
    static std::mutex mutex;
protected:
    LocalPlayer();
    ~LocalPlayer(){}
public:
    LocalPlayer(LocalPlayer const&) = delete;
    void operator=(const LocalPlayer&) = delete;
    static LocalPlayer* getInstance();

    bool isWalkLocked(uintptr_t localPlayer);
    uint32_t getStates(uintptr_t localPlayer);
    double getHealth(uintptr_t localPlayer);
    double getMaxHealth(uintptr_t localPlayer);
    double getFreeCapacity(uintptr_t localPlayer);
    uint16_t getLevel(uintptr_t localPlayer);
    double getMana(uintptr_t localPlayer);
    double getMaxMana(uintptr_t localPlayer);
    uint32_t getManaShield(uintptr_t localPlayer);
    uint8_t getSoul(uintptr_t localPlayer);
    uint16_t getStamina(uintptr_t localPlayer);
    uintptr_t getInventoryItem(uintptr_t localPlayer, Otc::InventorySlot inventorySlot);
    bool hasEquippedItemId(uintptr_t localPlayer, uint16_t itemId, uint8_t tier);
    uint16_t getInventoryCount(uintptr_t localPlayer, uint16_t itemId, uint8_t tier);
    bool hasSight(uintptr_t localPlayer, const Position &pos);
    bool isAutoWalking(uintptr_t localPlayer);
    void stopAutoWalk(uintptr_t localPlayer);
    bool autoWalk(uintptr_t localPlayer, const Position& destination, bool retry = false);

};




#endif //LOCALPLAYER_H
