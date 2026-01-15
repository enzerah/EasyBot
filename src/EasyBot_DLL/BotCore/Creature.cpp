#include "Creature.h"


Creature* Creature::instance{nullptr};
std::mutex Creature::mutex;

Creature* Creature::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new Creature();
    }
    return instance;
}

std::string Creature::getName(CreaturePtr creature) {
    if (!creature) return "";
    typedef void*(gameCall* GetName)(
        uintptr_t RCX,
        std::string* result
        );
    auto function = reinterpret_cast<GetName>(ClassMemberFunctions["Creature.getName"]);
    return g_dispatcher->scheduleEventEx([function, creature]() {
        std::string result;
        function(reinterpret_cast<uintptr_t>(creature.address), &result);
        return result;
    });
}

uint8_t Creature::getHealthPercent(CreaturePtr creature) {
    if (!creature) return 0;
    typedef uint8_t(gameCall* GetHealthPercent)(uintptr_t RCX);
    auto function = reinterpret_cast<GetHealthPercent>(ClassMemberFunctions["Creature.getHealthPercent"]);
    return g_dispatcher->scheduleEventEx([function, creature]() { return function(reinterpret_cast<uintptr_t>(creature.address)); });
}

Otc::Direction Creature::getDirection(CreaturePtr creature) {
    if (!creature) return {};
    typedef Otc::Direction(gameCall* GetDirection)(uintptr_t RCX);
    auto function = reinterpret_cast<GetDirection>(ClassMemberFunctions["Creature.getDirection"]);
    return g_dispatcher->scheduleEventEx([function, creature]() { return function(reinterpret_cast<uintptr_t>(creature.address)); });
}

bool Creature::isDead(CreaturePtr creature) {
    if (!creature) return 0;
    typedef bool(gameCall* IsDead)(uintptr_t RCX);
    auto function = reinterpret_cast<IsDead>(ClassMemberFunctions["Creature.isDead"]);
    return g_dispatcher->scheduleEventEx([function, creature]() { return function(reinterpret_cast<uintptr_t>(creature.address)); });
}

bool Creature::canBeSeen(CreaturePtr creature) {
    if (!creature) return 0;
    typedef bool(gameCall* CanBeSeen)(uintptr_t RCX);
    auto function = reinterpret_cast<CanBeSeen>(ClassMemberFunctions["Creature.canBeSeen"]);
    return g_dispatcher->scheduleEventEx([function, creature]() { return function(reinterpret_cast<uintptr_t>(creature.address)); });
}

bool Creature::isCovered(CreaturePtr creature) {
    if (!creature) return 0;
    typedef bool(gameCall* IsCovered)(uintptr_t RCX);
    auto function = reinterpret_cast<IsCovered>(ClassMemberFunctions["Creature.isCovered"]);
    return g_dispatcher->scheduleEventEx([function, creature]() { return function(reinterpret_cast<uintptr_t>(creature.address)); });
}

bool Creature::canShoot(CreaturePtr creature, int distance) {
    if (!creature) return 0;
    typedef bool(gameCall* CanShoot)(uintptr_t RCX, int distance);
    auto function = reinterpret_cast<CanShoot>(ClassMemberFunctions["Creature.canShoot"]);
    return g_dispatcher->scheduleEventEx([function, creature, distance]() { return function(reinterpret_cast<uintptr_t>(creature.address), distance); });
}


