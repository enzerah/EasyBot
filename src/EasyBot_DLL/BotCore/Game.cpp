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

void Game::walk(Otc::Direction direction)
{
    typedef void(gameCall* Walk)(
        uintptr_t RCX,
        Otc::Direction RDX
        );
    auto function = reinterpret_cast<Walk>(SingletonFunctions["g_game.walk"].first);
    return g_dispatcher->scheduleEventEx([function, &direction]() {
        function(SingletonFunctions["g_game.walk"].second, direction);
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

void Game::stop() {
    typedef void(gameCall* Stop)(
        uintptr_t RCX
        );
    auto function = reinterpret_cast<Stop>(SingletonFunctions["g_game.stop"].first);
    return g_dispatcher->scheduleEventEx([function]() {
        function(SingletonFunctions["g_game.stop"].second);
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
    return g_dispatcher->scheduleEventEx([function, &thing, toPos, count]() {
        function(SingletonFunctions["g_game.move"].second, &thing, &toPos, count);
    });
}

void Game::moveToParentContainer(const uintptr_t& thing, const int count) {
    if (!thing) return;
    typedef void(gameCall* MoveToParentContainer)(
        uintptr_t RCX,
        const uintptr_t *RDX,
        const int count
        );
    auto function = reinterpret_cast<MoveToParentContainer>(SingletonFunctions["g_game.moveToParentContainer"].first);
    return g_dispatcher->scheduleEventEx([function, &thing, count]() {
        function(SingletonFunctions["g_game.moveToParentContainer"].second, &thing, count);
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

void Game::cancelAttack() {
    typedef void(gameCall* CancelAttack)(
        uintptr_t RCX
        );
    auto function = reinterpret_cast<CancelAttack>(SingletonFunctions["g_game.cancelAttack"].first);
    return g_dispatcher->scheduleEventEx([function]() {
        function(SingletonFunctions["g_game.cancelAttack"].second);
    });
}

void Game::follow(const uintptr_t& creature) {
    if (!creature) return;
    typedef void(gameCall* Follow)(
        uintptr_t RCX,
        const uintptr_t RDX
        );
    auto function = reinterpret_cast<Follow>(SingletonFunctions["g_game.follow"].first);
    return g_dispatcher->scheduleEventEx([function, creature]() {
        function(SingletonFunctions["g_game.follow"].second, creature);
    });

}

void Game::cancelAttackAndFollow() {
    typedef void(gameCall* CancelAttackAndFollow)(
        uintptr_t RCX
    );
    auto function = reinterpret_cast<CancelAttackAndFollow>(SingletonFunctions["g_game.cancelAttackAndFollow"].first);
    return g_dispatcher->scheduleEventEx([function]() {
        function(SingletonFunctions["g_game.cancelAttackAndFollow"].second);
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

void Game::talkPrivate(Otc::MessageMode msgMode,const std::string& receiver,const std::string& message) {
    typedef void(gameCall *TalkPrivate)(
        uintptr_t RCX,
        Otc::MessageMode RDX,
        const std::string& receiver,
        const std::string& message
    );
    auto function = reinterpret_cast<TalkPrivate>(SingletonFunctions["g_game.talkPrivate"].first);
    g_dispatcher->scheduleEventEx([function, msgMode, receiver, message](){
        function(SingletonFunctions["g_game.talkPrivate"].second, msgMode, receiver, message);
    });
}



void Game::openPrivateChannel(const std::string& receiver) {
    typedef void(gameCall *OpenPrivateChannel)(
        uintptr_t RCX,
        const std::string& receiver
    );
    auto function = reinterpret_cast<OpenPrivateChannel>(SingletonFunctions["g_game.openPrivateChannel"].first);
    return g_dispatcher->scheduleEventEx([function, &receiver]() {
            function(SingletonFunctions["g_game.openPrivateChannel"].second, receiver);
    });
}

void Game::setChaseMode(Otc::ChaseModes mode) {
    typedef void(gameCall *SetChaseMode)(
        uintptr_t RCX,
        Otc::ChaseModes mode
        );
    auto function = reinterpret_cast<SetChaseMode>(SingletonFunctions["g_game.setChaseMode"].first);
    return g_dispatcher->scheduleEventEx([function, mode]() {
            function(SingletonFunctions["g_game.setChaseMode"].second, mode);
    });
}

void Game::setFightMode(Otc::FightModes mode) {
    typedef void(gameCall *SetFightMode)(
        uintptr_t RCX,
        Otc::FightModes mode
        );
    auto function = reinterpret_cast<SetFightMode>(SingletonFunctions["g_game.setFightMode"].first);
    return g_dispatcher->scheduleEventEx([function, mode]() {
            function(SingletonFunctions["g_game.setFightMode"].second, mode);
    });
}

void Game::buyItem(const uintptr_t& item, const uint16_t amount, const bool ignoreCapacity = false, const bool buyWithBackpack = false) {
    typedef void(gameCall *BuyItem)(
        uintptr_t RCX,
        const uintptr_t *item,
        uint16_t amount,
        bool ignoreCapacity,
        bool buyWithBackpack
        );
    auto function = reinterpret_cast<BuyItem>(SingletonFunctions["g_game.buyItem"].first);
    return g_dispatcher->scheduleEventEx([function, item, amount, ignoreCapacity, buyWithBackpack]() {
            function(SingletonFunctions["g_game.buyItem"].second, &item, amount, ignoreCapacity, buyWithBackpack);
    });
}

void Game::sellItem(const uintptr_t& item, const uint16_t amount, const bool ignoreEquipped = true) {
    typedef void(gameCall *SellItem)(
        uintptr_t RCX,
        const uintptr_t *item,
        uint16_t amount,
        bool ignoreEquipped
        );
    auto function = reinterpret_cast<SellItem>(SingletonFunctions["g_game.sellItem"].first);
    return g_dispatcher->scheduleEventEx([function, item, amount, ignoreEquipped]() {
            function(SingletonFunctions["g_game.sellItem"].second, &item, amount, ignoreEquipped);
    });
}

void Game::equipItem(const uintptr_t &item) {
    if (!item) return;
    typedef void(gameCall* EquipItem)(
        uintptr_t RCX,
        const uintptr_t *item
        );
    auto function = reinterpret_cast<EquipItem>(SingletonFunctions["g_game.equipItem"].first);
    return g_dispatcher->scheduleEventEx([function, item]() {
        function(SingletonFunctions["g_game.equipItem"].second, &item);
    });
}

void Game::equipItemId(uint16_t itemId, uint8_t tier) {
        typedef void(gameCall* EquipItemId)(
        uintptr_t RCX,
        uint16_t itemId,
        uint8_t tier
        );
    auto function = reinterpret_cast<EquipItemId>(SingletonFunctions["g_game.equipItemId"].first);
    return g_dispatcher->scheduleEventEx([function, itemId, tier]() {
        function(SingletonFunctions["g_game.equipItemId"].second, itemId, tier);
    });
}

void Game::mount(bool mountStatus) {
    typedef void(gameCall* Mount)(
        uintptr_t RCX,
        bool mountStatus
        );
    auto function = reinterpret_cast<Mount>(SingletonFunctions["g_game.mount"].first);
    return g_dispatcher->scheduleEventEx([function, mountStatus]() {
        function(SingletonFunctions["g_game.mount"].second, mountStatus);
    });
}

void Game::changeMapAwareRange(const uint8_t xrange, const uint8_t yrange) {
    typedef void(gameCall* ChangeMapAwareRange)(
        uintptr_t RCX,
        uint8_t xrange,
        uint8_t yrange
    );
    auto function = reinterpret_cast<ChangeMapAwareRange>(SingletonFunctions["g_game.changeMapAwareRange"].first);
    return g_dispatcher->scheduleEventEx([function, xrange, yrange]() {
        function(SingletonFunctions["g_game.changeMapAwareRange"].second, xrange, yrange);
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

bool Game::isOnline() {
    typedef bool(gameCall* IsOnline)(
       uintptr_t RCX,
       void *RDX
       );
    auto function = reinterpret_cast<IsOnline>(SingletonFunctions["g_game.isOnline"].first);
    return g_dispatcher->scheduleEventEx([function]() {
            void* pMysteryPtr = nullptr;
            auto ret = function(SingletonFunctions["isOnline.isOnline"].second, &pMysteryPtr);
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

bool Game::isFollowing() {
    typedef bool(gameCall* IsFollowing)(
       uintptr_t RCX,
       void *RDX
       );
    auto function = reinterpret_cast<IsFollowing>(SingletonFunctions["g_game.isFollowing"].first);
    return g_dispatcher->scheduleEventEx([function]() {
            void* pMysteryPtr = nullptr;
            auto ret = function(SingletonFunctions["g_game.isFollowing"].second, &pMysteryPtr);
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

uintptr_t Game::getFollowingCreature() {
    typedef uintptr_t*(gameCall* GetFollowingCreature)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetFollowingCreature>(SingletonFunctions["g_game.getFollowingCreature"].first);
    return g_dispatcher->scheduleEventEx([function]() {
            void* pMysteryPtr = nullptr;
            auto ret = function(SingletonFunctions["g_game.getFollowingCreature"].second, &pMysteryPtr);
            return *ret;
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

int Game::getClientVersion() {
    typedef int(gameCall* GetClientVersion)(
        uintptr_t RCX
        );
    auto function = reinterpret_cast<GetClientVersion>(SingletonFunctions["g_game.getClientVersion"].first);
    return g_dispatcher->scheduleEventEx([function]() {
        return function(SingletonFunctions["g_game.getClientVersion"].second);
    });
}

std::string Game::getCharacterName() {
    typedef std::string*(gameCall* GetCharacterName)(
        uintptr_t RCX
        );
    auto function = reinterpret_cast<GetCharacterName>(SingletonFunctions["g_game.getCharacterName"].first);
    return g_dispatcher->scheduleEventEx([function]() {
        auto ret = function(SingletonFunctions["g_game.getCharacterName"].second);
        return *ret;
    });
}





















