//
// Created by Wojciech on 28.09.2025.
//


#include "Game.h"

#include <codecvt>

#include "EventDispatcher.h"
#include <unordered_map>
Game* Game::instance{nullptr};
std::mutex Game::mutex;
Game::Game()
{
}

Game* Game::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new Game();
    }
    return instance;
}

void Game::walk(Otc::Direction direction, bool withPreWalk)
{
    typedef void(gameCall* Walk)(
        uintptr_t RCX,
        Otc::Direction RDX,
        bool R8
        );
    auto function = reinterpret_cast<Walk>(SingletonFunctions["g_game.walk"].first);
    return g_dispatcher->scheduleEventEx([function, &direction, withPreWalk]() {
        function(SingletonFunctions["g_game.walk"].second, direction, withPreWalk);
    });
}

void Game::autoWalk(const std::vector<Otc::Direction>& dirs, const Position &startPos)
{
    typedef void(gameCall* AutoWalk)(
        uintptr_t RCX,
        const std::vector<Otc::Direction> *RDX,
        const Position R8
        );
    auto function = reinterpret_cast<AutoWalk>(SingletonFunctions["g_game.autoWalk"].first);
    return g_dispatcher->scheduleEventEx([function, &dirs, startPos]() {
        function(SingletonFunctions["g_game.autoWalk"].second, &dirs, startPos);
    });
}

void Game::turn(Otc::Direction direction)
{
    typedef void(gameCall* Turn)(
        uintptr_t RCX,
        Otc::Direction RDX
        );
    auto function = reinterpret_cast<Turn>(SingletonFunctions["g_game.turn"].first);
    return g_dispatcher->scheduleEventEx([function, direction]() {
        function(SingletonFunctions["g_game.turn"].second, direction);
    });
}

void Game::look(const uintptr_t &thing, const bool isBattleList) {
    typedef void(gameCall* Look)(
        uintptr_t RCX,
        const uintptr_t *RDX,
        const bool isBattleList
    );
    auto function = reinterpret_cast<Look>(SingletonFunctions["g_game.look"].first);
    return g_dispatcher->scheduleEventEx([function, &thing, isBattleList]() {
        function(SingletonFunctions["g_game.look"].second, &thing, isBattleList);
    });
}

void Game::move(const uintptr_t &thing, const Position& toPos, int count) {
    if (!thing) return;
    typedef void(gameCall* Move)(
        uintptr_t RCX,
        const uintptr_t *RDX,
        const Position *R8,
        int count
        );
    auto function = reinterpret_cast<Move>(SingletonFunctions["g_game.move"].first);
    return g_dispatcher->scheduleEventEx([function, &thing, &toPos, count]() {
        function(SingletonFunctions["g_game.move"].second, &thing, &toPos, count);
    });
}

void Game::use(const uintptr_t &thing) {
    if (!thing) return;
    typedef void(gameCall* Use)(
        uintptr_t RCX,
        const uintptr_t *RDX
        );
    auto function = reinterpret_cast<Use>(SingletonFunctions["g_game.use"].first);
    return g_dispatcher->scheduleEventEx([function, &thing]() {
        function(SingletonFunctions["g_game.use"].second, &thing);
    });
}

void Game::useWith(const uintptr_t &item, const uintptr_t &toThing) {
    if (!item || !toThing) return;
    typedef void(gameCall* UseWith)(
        uintptr_t RCX,
        const uintptr_t *RDX,
        const uintptr_t *R8
        );
    auto function = reinterpret_cast<UseWith>(SingletonFunctions["g_game.useWith"].first);
    return g_dispatcher->scheduleEventEx([function, &item, &toThing]() {
        function(SingletonFunctions["g_game.useWith"].second, &item, &toThing);
    });
}

void Game::useInventoryItem(const uint16_t itemId) {
    if (!itemId) return;
    typedef void(gameCall* UseInventoryItem)(
        uintptr_t RCX,
        const uint16_t itemId
    );
    auto function = reinterpret_cast<UseInventoryItem>(SingletonFunctions["g_game.useInventoryItem"].first);
    return g_dispatcher->scheduleEventEx([function, itemId]() {
        function(SingletonFunctions["g_game.useInventoryItem"].second, itemId);
    });
}

void Game::useInventoryItemWith(const uint16_t itemId, const uintptr_t &toThing) {
    if (!toThing) return;
    typedef void(gameCall* UseInventoryItemWith)(
        uintptr_t second_param,
        const uint16_t itemId,
        const uintptr_t *toThing
    );
    auto function = reinterpret_cast<UseInventoryItemWith>(SingletonFunctions["g_game.useInventoryItemWith"].first);
    return g_dispatcher->scheduleEventEx([function, itemId, &toThing]() {
        function(SingletonFunctions["g_game.useInventoryItemWith"].second, itemId, &toThing);
    });
}

uintptr_t Game::findItemInContainers(uint32_t itemId, int subType, uint8_t tier) {
    typedef uintptr_t*(gameCall* FindItemInContainers)(
        uintptr_t RCX,
        void* result,
        uint32_t RDX,
        int R8,
        uint8_t tier
        );
    auto function = reinterpret_cast<FindItemInContainers>(SingletonFunctions["g_game.findItemInContainers"].first);
    return g_dispatcher->scheduleEventEx([function, itemId, subType, tier]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(SingletonFunctions["g_game.findItemInContainers"].second, &pMysteryPtr, itemId, subType, tier);
        return *ret;
    });
}

int Game::open(const uintptr_t &item, const uintptr_t &previousContainer) {
    if (!item) return 0;
    typedef int(gameCall* Open)(
        uintptr_t RCX,
        const uintptr_t *RDX,
        const uintptr_t *R8
        );
    auto function = reinterpret_cast<Open>(SingletonFunctions["g_game.open"].first);
    return g_dispatcher->scheduleEventEx([function, &item, &previousContainer]() {
            auto ret = function(SingletonFunctions["g_game.open"].second, &item, &previousContainer);
            return ret;
    });
}

void Game::openParent(const uintptr_t &container) {
    if (!container) return;
    typedef void(gameCall* OpenParent)(
        uintptr_t RCX,
        const uintptr_t *RDX
        );
    auto function = reinterpret_cast<OpenParent>(SingletonFunctions["g_game.openParent"].first);
    return g_dispatcher->scheduleEventEx([function, &container]() {
        function(SingletonFunctions["g_game.openParent"].second, &container);
    });
}

void Game::close(const uintptr_t &container) {
    if (!container) return;
    typedef void(gameCall* Close)(
        uintptr_t RCX,
        const uintptr_t *RDX
        );
    auto function = reinterpret_cast<Close>(SingletonFunctions["g_game.close"].first);
    return g_dispatcher->scheduleEventEx([function, &container]() {
        function(SingletonFunctions["g_game.close"].second, &container);
    });
}

void Game::refreshContainer(const uintptr_t &container) {
    if (!container) return;
    typedef void(gameCall* RefreshContainer)(
        uintptr_t RCX,
        const uintptr_t *RDX
        );
    auto function = reinterpret_cast<RefreshContainer>(SingletonFunctions["g_game.refreshContainer"].first);
    return g_dispatcher->scheduleEventEx([function, &container]() {
        function(SingletonFunctions["g_game.refreshContainer"].second, &container);
    });
}

void Game::attack(const uintptr_t &creature, bool cancel = false) {
    if (!creature) return;
    typedef void(gameCall* Attack)(
        uintptr_t RCX,
        const uintptr_t RDX,
        bool R8
        );
    auto function = reinterpret_cast<Attack>(SingletonFunctions["g_game.attack"].first);
    return g_dispatcher->scheduleEventEx([function, creature, cancel]() {
        function(SingletonFunctions["g_game.attack"].second, creature, cancel);
    });
}

uintptr_t Game::getLocalPlayer() {
    typedef uintptr_t*(gameCall* GetLocalPlayer)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetLocalPlayer>(SingletonFunctions["g_game.getLocalPlayer"].first);
    return g_dispatcher->scheduleEventEx([function]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(SingletonFunctions["g_game.getLocalPlayer"].second, &pMysteryPtr);
        return *ret;
    });
}

void Game::equipItem(const uintptr_t &item) {
    if (!item) return;
    typedef void(gameCall* EquipItem)(
        uintptr_t RCX,
        const uintptr_t *item
        );
    auto function = reinterpret_cast<EquipItem>(SingletonFunctions["g_game.equipItem"].first);
    return g_dispatcher->scheduleEventEx([function, &item]() {
        function(SingletonFunctions["g_game.equipItem"].second, &item);
    });
}

void Game::cancelAttack() {
    typedef void(gameCall* CancelAttack)(
        uintptr_t RCX
        );
    auto function = reinterpret_cast<CancelAttack>(SingletonFunctions["g_game.cancelAttack"].first);
    return g_dispatcher->scheduleEventEx([function]() {
        function(SingletonFunctions["g_game.cancelAttack"].second);
    });
}

void Game::talk(const std::string& message) {
    typedef void(gameCall *Talk)(
        uintptr_t RCX,
        const std::string& message
    );
    auto function = reinterpret_cast<Talk>(SingletonFunctions["g_game.talk"].first);
    return g_dispatcher->scheduleEventEx([function, message]() {

        function(SingletonFunctions["g_game.talk"].second, message);
    });
}


void Game::talkChannel(const Otc::MessageMode mode, const uint16_t channelId, const std::string& message) {
    typedef void(gameCall *TalkChannel)(
        uintptr_t RCX,
        const Otc::MessageMode RDX,
        const uint16_t channelId,
        const std::string& message
        );
    auto function = reinterpret_cast<TalkChannel>(SingletonFunctions["g_game.talkChannel"].first);
    return g_dispatcher->scheduleEventEx([function, mode, channelId, message]() {
            function(SingletonFunctions["g_game.talkChannel"].second, mode, channelId, message);
    });
}

void Game::talkPrivate(const Otc::MessageMode msgMode, const std::string& receiver, const std::string& message) {
    typedef void(gameCall *TalkPrivate)(
        uintptr_t RCX,
        Otc::MessageMode RDX,
        uintptr_t *receiver,
        uintptr_t *message
    );
    auto function = reinterpret_cast<TalkPrivate>(SingletonFunctions["g_game.talkPrivate"].first);
    return g_dispatcher->scheduleEventEx([function, msgMode, &receiver, &message]() {
            uintptr_t rcv[2];
            rcv[0] = reinterpret_cast<uintptr_t>(receiver.c_str());
            rcv[1] = strlen(receiver.c_str());

            uintptr_t msg[2];
            msg[0] = reinterpret_cast<uintptr_t>(message.c_str());
            msg[1] = strlen(message.c_str());
            function(SingletonFunctions["g_game.talkPrivate"].second, msgMode, rcv, msg);
    });
}

bool Game::canPerformGameAction() {
    typedef bool(gameCall* CanPerformGameAction)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<CanPerformGameAction>(SingletonFunctions["g_game.canPerformGameAction"].first);
    return g_dispatcher->scheduleEventEx([function]() {
            void* pMysteryPtr = nullptr;
            auto ret = function(SingletonFunctions["g_game.canPerformGameAction"].second, &pMysteryPtr);
            return ret;
    });
}

bool Game::isAttacking() {
    typedef bool(gameCall* IsAttacking)(
       uintptr_t RCX,
       void *RDX
       );
    auto function = reinterpret_cast<IsAttacking>(SingletonFunctions["g_game.isAttacking"].first);
    return g_dispatcher->scheduleEventEx([function]() {
            void* pMysteryPtr = nullptr;
            auto ret = function(SingletonFunctions["g_game.isAttacking"].second, &pMysteryPtr);
            return ret;
    });
}

uintptr_t Game::getContainer(int index) {
    typedef uintptr_t*(gameCall* GetContainer)(
        uintptr_t RCX,
        void *RDX,
        int idx
        );
    auto function = reinterpret_cast<GetContainer>(SingletonFunctions["g_game.getContainer"].first);
    return g_dispatcher->scheduleEventEx([function, index]() {
            void* pMysteryPtr = nullptr;
            auto ret = function(SingletonFunctions["g_game.getContainer"].second, &pMysteryPtr, index);
            return *ret;
    });
}

std::vector<uintptr_t> Game::getContainers() {
    typedef std::map<int, uintptr_t>*(gameCall* GetContainers)(
        uintptr_t RCX,
        void *RDX
    );
    auto function = reinterpret_cast<GetContainers>(SingletonFunctions["g_game.getContainers"].first);
    return g_dispatcher->scheduleEventEx([function]() {
        void *pMysteryPtr = nullptr;
        auto ret = function(SingletonFunctions["g_game.getContainers"].second, &pMysteryPtr);
        std::vector<uintptr_t> containers;
        for (auto items : *ret){
            containers.push_back(items.second);
        }
        return containers;
    });
}

uintptr_t Game::getAttackingCreature() {
    typedef uintptr_t*(gameCall* GetAttackingCreature)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetAttackingCreature>(SingletonFunctions["g_game.getAttackingCreature"].first);
    return g_dispatcher->scheduleEventEx([function]() {
            void* pMysteryPtr = nullptr;
            auto ret = function(SingletonFunctions["g_game.getAttackingCreature"].second, &pMysteryPtr);
            return *ret;
    });
}

uintptr_t Game::getThingType(uint16_t id, ThingCategory category)
{
    typedef uintptr_t*(gameCall* GetThingType)(
        uintptr_t RCX,
        uint16_t id,
        ThingCategory category
        );
    auto function = reinterpret_cast<GetThingType>(SingletonFunctions["g_things.getThingType"].first);
    return g_dispatcher->scheduleEventEx([function, id, category]() {
        auto ret = function(SingletonFunctions["g_things.getThingType"].second, id, category);
        return *ret;
    });
}



















