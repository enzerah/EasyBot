//
// Created by blazz on 30.09.2025.
//

#ifndef MAPVIEW_H
#define MAPVIEW_H
#include "Game.h"
#define g_map Map::getInstance()



class Map : public Game {
private:
    static Map* instance;
    static std::mutex mutex;
protected:
    Map();
    ~Map(){}
public:
    Map(Map const&) = delete;
    void operator=(const Map&) = delete;
    static Map* getInstance();


    uintptr_t getTile(Position tilePos);
    std::vector<uintptr_t> getSpectators(const Position &centerPos, bool multiFloor = false);
    std::vector<Otc::Direction> findPath(const Position &startPos, const Position &goalPos, int maxComplexity, int flags);
    bool isWalkable(const Position& pos, bool ignoreCreatures);
    bool isSightClear(const Position& fromPos, const Position& toPos);
};



#endif //MAPVIEW_H
