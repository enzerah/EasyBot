//
// Created by Wojciech on 03.10.2025.
//

#ifndef CONTAINER_H
#define CONTAINER_H
#include <deque>
#include <mutex>
#include "Map.h"
#define g_container Container::getInstance()


class Container : public Map{
private:
    static Container* instance;
    static std::mutex mutex;
protected:
    Container();
    ~Container(){}
public:
    Container(Container const&) = delete;
    void operator=(const Container&) = delete;
    static Container* getInstance();
    uintptr_t getItem(uintptr_t container, uint8_t slot);
    std::deque<uintptr_t> getItems(uintptr_t container);
    int getItemsCount(uintptr_t container);
    Position getSlotPosition(uintptr_t container, int slot);
    std::string getName(uintptr_t container);
    uintptr_t getContainerItem(uintptr_t container);
    bool hasParent(uintptr_t container);
    int getFirstIndex(uintptr_t container);

};



#endif //CONTAINER_H
