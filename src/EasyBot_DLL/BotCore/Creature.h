//
// Created by Wojciech on 03.10.2025.
//

#ifndef CREATURE_H
#define CREATURE_H
#define g_creature Creature::getInstance()
#include <mutex>
#include "Map.h"


class Creature : public Map {
private:
    static Creature* instance;
    static std::mutex mutex;
protected:
    Creature();
    ~Creature(){}
public:
    Creature(Creature const&) = delete;
    void operator=(const Creature&) = delete;
    static Creature* getInstance();

    std::string getName(uintptr_t creature);
    uint8_t getHealthPercent(uintptr_t creature);
    Otc::Direction getDirection(uintptr_t creature);
    bool isDead(uintptr_t creature);
    bool canBeSeen(uintptr_t creature);
    bool isCovered(uintptr_t creature);
    bool canShoot(uintptr_t creature, int distance);

};



#endif //CREATURE_H
