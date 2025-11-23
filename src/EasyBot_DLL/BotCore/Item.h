//
// Created by Wojciech on 04.10.2025.
//

#ifndef ITEM_H
#define ITEM_H
#include "Map.h"
#define g_item Item::getInstance()


class Item : public Map {
private:
    static Item* instance;
    static std::mutex mutex;
protected:
    Item();
    ~Item(){}
public:
    Item(Item const&) = delete;
    void operator=(const Item&) = delete;
    static Item* getInstance();
    std::string getName(uintptr_t item);
    std::string getDescription(uintptr_t item);
    int getCount(uintptr_t item);
    int getSubType(uintptr_t item);
    uint32_t getId(uintptr_t item);
    uint8_t getTier(uintptr_t item);
    std::string getText(uintptr_t item);


};



#endif //ITEM_H
