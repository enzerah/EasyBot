//
// Created by blazz on 30.09.2025.
//

#include "Map.h"
Map* Map::instance{nullptr};
std::mutex Map::mutex;
Map::Map()
{
}

Map* Map::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new Map();
    }
    return instance;
}

uintptr_t Map::getTile(Position tilePos) {
    typedef uintptr_t*(gameCall* GetTile)(
        uintptr_t RCX,
        const Position *RDX
        );
    auto function = reinterpret_cast<GetTile>(SingletonFunctions["g_map.getTile"].first);
    return g_dispatcher->scheduleEventEx([function, tilePos]() {
        return *function(SingletonFunctions["g_map.getTile"].second, &tilePos);
    });
}

std::vector<uintptr_t> Map::getSpectators(const Position &centerPos, bool multiFloor) {
    typedef std::vector<uintptr_t>*(gameCall* GetSpectators)(
        uintptr_t RCX,
        void *RDX,
        const Position *R8,
        bool R9
        );
    auto function = reinterpret_cast<GetSpectators>(SingletonFunctions["g_map.getSpectators"].first);
    return g_dispatcher->scheduleEventEx([function, &centerPos, multiFloor]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(SingletonFunctions["g_map.getSpectators"].second, &pMysteryPtr, &centerPos, multiFloor);
        return *ret;
    });
}

std::vector<Otc::Direction> Map::findPath(const Position& startPos, const Position& goalPos, int maxComplexity, int flags) {
    typedef std::tuple<std::vector<Otc::Direction>, Otc::PathFindResult>*(gameCall* FindPath)(
        uintptr_t RCX,
        void *RDX,
        const Position *R8,
        const Position *R9,
        int maxComplexity,
        int flags
        );
    auto function = reinterpret_cast<FindPath>(SingletonFunctions["g_map.findPath"].first);
    return g_dispatcher->scheduleEventEx([function, &startPos, &goalPos, maxComplexity, flags]() {
        void* pMysteryPtr = nullptr;
        auto ret = function(SingletonFunctions["g_map.findPath"].second, &pMysteryPtr, &startPos,  &goalPos, maxComplexity, flags);
        std::vector<Otc::Direction> dirs;
        if (ret) {
            auto result = std::get<1>(*ret);
            if (result == Otc::PathFindResultOk) {
                dirs = std::get<0>(*ret);
                return dirs;
            }
        }
        return dirs;
    });
}

bool Map::isWalkable(const Position& pos, bool ignoreCreatures) {
    typedef bool(gameCall* IsWalkable)(
        uintptr_t RCX,
        void *RDX,
        const Position *fromPos,
        bool ignoreCreatures
        );
    auto function = reinterpret_cast<IsWalkable>(SingletonFunctions["g_map.isWalkable"].first);
    return g_dispatcher->scheduleEventEx([function, pos, ignoreCreatures]() {
        void* pMysteryPtr = nullptr;
        return function(SingletonFunctions["g_map.isWalkable"].second, &pMysteryPtr, &pos, ignoreCreatures);
    });
}

bool Map::isSightClear(const Position& fromPos, const Position& toPos) {
    typedef bool(gameCall* IsSightClear)(
        uintptr_t RCX,
        void *RDX,
        const Position *fromPos,
        const Position *toPos
        );
    auto function = reinterpret_cast<IsSightClear>(SingletonFunctions["g_map.isSightClear"].first);
    return g_dispatcher->scheduleEventEx([function, fromPos, toPos]() {
        void* pMysteryPtr = nullptr;
        return function(SingletonFunctions["g_map.isSightClear"].second, &pMysteryPtr, &fromPos, &toPos);
    });
}






