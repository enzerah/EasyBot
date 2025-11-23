//
// Created by Wojciech on 04.10.2025.
//

#include "Tile.h"

Tile* Tile::instance{nullptr};
std::mutex Tile::mutex;
Tile::Tile()
{
}

Tile* Tile::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new Tile();
    }
    return instance;
}

uintptr_t Tile::getTopThing(uintptr_t tile) {
    if (!tile) return 0;
    typedef uintptr_t*(gameCall* GetTopThing)(
        uintptr_t RCX,
        void *RDX
        );
    auto function = reinterpret_cast<GetTopThing>(ClassMemberFunctions["Tile.getTopThing"]);
    return g_dispatcher->scheduleEventEx([function, tile]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(tile, &pMysteryPtr);
        return *ret;
    });
}

uintptr_t Tile::getTopUseThing(uintptr_t tile) {
    if (!tile) return 0;
    typedef uintptr_t*(gameCall* GetTopUseThing)(
    uintptr_t RCX,
    void *RDX
    );
    void* pMysteryPtr = nullptr;
    auto function = reinterpret_cast<GetTopUseThing>(ClassMemberFunctions["Tile.getTopUseThing"]);
    return g_dispatcher->scheduleEventEx([function, tile]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(tile, &pMysteryPtr);
        return *ret;
    });
}
