//
// Created by Wojciech on 03.10.2025.
//

#ifndef THING_H
#define THING_H
#define g_thing Thing::getInstance()
#include <mutex>
#include "Map.h"


class Thing : public Map {
private:
    static Thing* instance;
    static std::mutex mutex;
protected:
    Thing();
    ~Thing(){}
public:
    Thing(Thing const&) = delete;
    void operator=(const Thing&) = delete;
    static Thing* getInstance();

    uint32_t getId(uintptr_t thing);
    Position getPosition(uintptr_t thing);

    uintptr_t getParentContainer(uintptr_t thing);
    bool isMonster(uintptr_t thing);
    bool isNpc(uintptr_t thing);
    bool isPlayer(uintptr_t thing);
    bool isLocalPlayer(uintptr_t thing);
    bool isContainer(uintptr_t thing);
    bool isUsable(uintptr_t thing);
    bool isLyingCorpse(uintptr_t thing);
};



#endif //THING_H
