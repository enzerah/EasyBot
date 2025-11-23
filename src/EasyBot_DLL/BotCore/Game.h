//
// Created by Wojciech on 28.09.2025.
//

#ifndef GAME_H
#define GAME_H
#include <cstdint>
#include <iostream>
#include <mutex>
#include <queue>
#include <vector>
#include "hooks.h"
#include "../../const.h"
#define g_game Game::getInstance()
#ifdef _WIN64
    #define gameCall __fastcall
#else
    #define gameCall __thiscall
#endif

class Game {
private:
    static Game* instance;
    static std::mutex mutex;
protected:
    Game();
    ~Game(){}
public:
    Game(Game const&) = delete;
    void operator=(const Game&) = delete;
    static Game* getInstance();

    void walk(Otc::Direction direction, bool withPreWalk);
    void autoWalk(const std::vector<Otc::Direction> &dirs, const Position &startPos);
    void turn(Otc::Direction direction);
    void look(const uintptr_t& thing, const bool isBattleList);
    void move(const uintptr_t &thing, const Position& toPos, int count);
    void use(const uintptr_t &thing);
    void useWith(const uintptr_t &item, const uintptr_t &toThing);
    void useInventoryItem(const uint16_t itemId);
    void useInventoryItemWith(const uint16_t itemId, const uintptr_t& toThing);
    uintptr_t findItemInContainers(uint32_t itemId, int subType, uint8_t tier);
    int open(const uintptr_t &item, const uintptr_t &previousContainer);
    void openParent(const uintptr_t &container);
    void close(const uintptr_t &container);
    void refreshContainer(const uintptr_t &container);
    void attack(const uintptr_t &creature, bool cancel);

    uintptr_t getLocalPlayer();
    void equipItem(const uintptr_t &item);
    void cancelAttack();
    void talk(const std::string& message);
    void talkChannel(const Otc::MessageMode mode, const uint16_t channelId, const std::string& message);
    void talkPrivate(const Otc::MessageMode msgMode, const std::string& receiver, const std::string& message);
    bool canPerformGameAction();
    bool isAttacking();

    uintptr_t getContainer(int index);
    std::vector<uintptr_t> getContainers();
    uintptr_t getAttackingCreature();
    uintptr_t getThingType(uint16_t id, ThingCategory category);


};



#endif //GAME_H
