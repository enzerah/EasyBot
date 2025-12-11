//
// Created by Wojciech on 03.10.2025.
//

#include "Creature.h"
Creature* Creature::instance{nullptr};
std::mutex Creature::mutex;
Creature::Creature()
{
}

Creature* Creature::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new Creature();
    }
    return instance;
}

std::string Creature::getName(uintptr_t creature) {
    if (!creature) return 0;
    typedef std::string*(gameCall* GetName)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetName>(ClassMemberFunctions["Creature.getName"]);
    return g_dispatcher->scheduleEventEx([function, creature]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(creature, &pMysteryPtr);
        const char* name_data = ret->c_str();
        char temp_buffer[256];
        strncpy_s(temp_buffer, name_data, 255);
        temp_buffer[255] = '\0';
        std::string name(temp_buffer);
        return name;
    });
}

uint8_t Creature::getHealthPercent(uintptr_t creature) {
    if (!creature) return 0;
    typedef uint8_t(gameCall* GetHealthPercent)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetHealthPercent>(ClassMemberFunctions["Creature.getHealthPercent"]);
    return g_dispatcher->scheduleEventEx([function, creature]() {
        void* pMysteryPtr = nullptr;
        return function(creature, &pMysteryPtr);
    });
}

Otc::Direction Creature::getDirection(uintptr_t creature) {
    if (!creature) return {};
    typedef Otc::Direction(gameCall* GetDirection)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetDirection>(ClassMemberFunctions["Creature.getDirection"]);
    return g_dispatcher->scheduleEventEx([function, creature]() {
            void* pMysteryPtr = nullptr;
            return function(creature, &pMysteryPtr);
    });
}

bool Creature::isDead(uintptr_t creature) {
    if (!creature) return 0;
    typedef bool(gameCall* IsDead)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<IsDead>(ClassMemberFunctions["Creature.isDead"]);
    return g_dispatcher->scheduleEventEx([function, creature]() {
            void* pMysteryPtr = nullptr;
            return function(creature, &pMysteryPtr);
    });
}

bool Creature::canBeSeen(uintptr_t creature) {
    if (!creature) return 0;
    typedef bool(gameCall* CanBeSeen)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<CanBeSeen>(ClassMemberFunctions["Creature.canBeSeen"]);
    return g_dispatcher->scheduleEventEx([function, creature]() {
            void* pMysteryPtr = nullptr;
            return function(creature, &pMysteryPtr);
    });
}

bool Creature::isCovered(uintptr_t creature) {
    if (!creature) return 0;
    typedef bool(gameCall* IsCovered)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<IsCovered>(ClassMemberFunctions["Creature.isCovered"]);
    return g_dispatcher->scheduleEventEx([function, creature]() {
            void* pMysteryPtr = nullptr;
            return function(creature, &pMysteryPtr);
    });
}

bool Creature::canShoot(uintptr_t creature, int distance) {
    if (!creature) return 0;
    typedef bool(gameCall* CanShoot)(
        uintptr_t RCX,
        void *RDX,
        int distance
        );
    auto function = reinterpret_cast<CanShoot>(ClassMemberFunctions["Creature.canShoot"]);
    return g_dispatcher->scheduleEventEx([function, creature, distance]() {
            void* pMysteryPtr = nullptr;
            return function(creature, &pMysteryPtr, distance);
    });
}


