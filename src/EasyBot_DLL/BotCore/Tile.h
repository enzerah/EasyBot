//
// Created by Wojciech on 04.10.2025.
//

#ifndef TILE_H
#define TILE_H
#include "Map.h"
#define g_tile Tile::getInstance()


class Tile : public Map{
    static Tile* instance;
    static std::mutex mutex;
protected:
    Tile();
    ~Tile(){}
public:
    Tile(Tile const&) = delete;
    void operator=(const Tile&) = delete;
    static Tile* getInstance();

    uintptr_t getTopThing(uintptr_t tile);
    uintptr_t getTopUseThing(uintptr_t tile);
    std::vector<uintptr_t> getItems(uintptr_t tile);
};



#endif //TILE_H
