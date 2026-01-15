#include "Map.h"

Map* Map::instance{nullptr};
std::mutex Map::mutex;


Map* Map::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new Map();
    }
    return instance;
}

TilePtr Map::getTile(Position tilePos) {
    typedef void*(gameCall* GetTile)(
        uintptr_t RCX,
        TilePtr* result,
        const Position *RDX
        );
    auto function = reinterpret_cast<GetTile>(SingletonFunctions["g_map.getTile"].first);
    return g_dispatcher->scheduleEventEx([function, tilePos]() {
        TilePtr result;
        function(SingletonFunctions["g_map.getTile"].second, &result, &tilePos);
        return result;
    });
}

std::vector<CreaturePtr> Map::getSpectators(const Position centerPos, bool multiFloor) {
    typedef std::vector<CreaturePtr>*(gameCall* GetSpectators)(
        uintptr_t RCX,
        std::vector<CreaturePtr>* result,
        const Position *R8,
        bool R9
        );
    auto function = reinterpret_cast<GetSpectators>(SingletonFunctions["g_map.getSpectators"].first);
    return g_dispatcher->scheduleEventEx([function, centerPos, multiFloor]() {
        std::vector<CreaturePtr> result;
        function(SingletonFunctions["g_map.getSpectators"].second, &result, &centerPos, multiFloor);
        return result;
    });
}

std::vector<Otc::Direction> Map::findPath(const Position startPos, const Position goalPos, int maxComplexity, int flags) {
    typedef void*(gameCall* FindPath)(
        uintptr_t RCX,
        std::tuple<std::vector<Otc::Direction>, Otc::PathFindResult> *result,
        const Position *R8,
        const Position *R9,
        int maxComplexity,
        int flags
        );
    auto function = reinterpret_cast<FindPath>(SingletonFunctions["g_map.findPath"].first);
    return g_dispatcher->scheduleEventEx([function, startPos, goalPos, maxComplexity, flags]() {
        std::tuple<std::vector<Otc::Direction>, Otc::PathFindResult> result;
        function(SingletonFunctions["g_map.findPath"].second, &result, &startPos,  &goalPos, maxComplexity, flags);
        if (std::get<1>(result) == Otc::PathFindResultOk)
            return std::get<0>(result);
        return std::vector<Otc::Direction> {};
    });
}

bool Map::isWalkable(const Position& pos, bool ignoreCreatures) {
    typedef bool(gameCall* IsWalkable)(
        uintptr_t RCX,
        const Position *fromPos,
        bool ignoreCreatures
        );
    auto function = reinterpret_cast<IsWalkable>(SingletonFunctions["g_map.isWalkable"].first);
    return g_dispatcher->scheduleEventEx([function, pos, ignoreCreatures]() {
        return function(SingletonFunctions["g_map.isWalkable"].second, &pos, ignoreCreatures);
    });
}

bool Map::isSightClear(const Position& fromPos, const Position& toPos) {
    typedef bool(gameCall* IsSightClear)(
        uintptr_t RCX,
        const Position *fromPos,
        const Position *toPos
        );
    auto function = reinterpret_cast<IsSightClear>(SingletonFunctions["g_map.isSightClear"].first);
    return g_dispatcher->scheduleEventEx([function, fromPos, toPos]() {
        return function(SingletonFunctions["g_map.isSightClear"].second, &fromPos, &toPos);
    });
}






