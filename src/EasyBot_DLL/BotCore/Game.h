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

    void walk(Otc::Direction direction);
    void autoWalk(const std::vector<Otc::Direction> &dirs, const Position &startPos);
    void turn(Otc::Direction direction);
    void stop();
    void look(const uintptr_t& thing, const bool isBattleList);
    void move(const uintptr_t &thing, const Position& toPos, int count);
    void moveToParentContainer(const uintptr_t& thing, const int count);
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
    void cancelAttack();
    void follow(const uintptr_t &creature);
    void cancelAttackAndFollow();
    void talk(const std::string& message);
    void talkChannel(const Otc::MessageMode mode, const uint16_t channelId, const std::string& message);
    void talkPrivate(const Otc::MessageMode msgMode, const std::string& receiver, const std::string& message);
    void openPrivateChannel(const std::string& receiver);
    void setChaseMode(Otc::ChaseModes mode);
    void setFightMode(Otc::FightModes mode);
    void buyItem(const uintptr_t& item, const uint16_t amount, const bool ignoreCapacity, const bool buyWithBackpack);
    void sellItem(const uintptr_t& item, const uint16_t amount, const bool ignoreEquipped);
    void equipItem(const uintptr_t &item);
    void equipItemId(uint16_t itemId, uint8_t tier);
    void mount(bool mountStatus);
    void changeMapAwareRange(const uint8_t xrange, const uint8_t yrange);
    bool canPerformGameAction();
    bool isOnline();
    bool isAttacking();
    bool isFollowing();
    uintptr_t getContainer(int index);
    std::vector<uintptr_t> getContainers();
    uintptr_t getAttackingCreature();
    uintptr_t getFollowingCreature();
    uintptr_t getLocalPlayer();
    int getClientVersion();
    std::string getCharacterName();

};



#endif //GAME_H
