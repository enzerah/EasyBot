#include <iostream>

#include "../../proto_functions_client.h"
#include "../../const.h"
//python -m grpc_tools.protoc -IC:\Users\Wojciech\Desktop\Projects\EasyBot86 --python_out=. --grpc_python_out=. C:\Users\Wojciech\Desktop\Projects\EasyBot86\bot.proto
int main() {
    /*
    auto localPlayer = proto->getLocalPlayer();
    std::cout << std::hex << localPlayer << std::endl;
    proto->setLightHack(localPlayer, 0xFFFF);
    auto playerPos = proto->getPosition(localPlayer);
    auto spectators = proto->getSpectators(playerPos);
    std::cout << "Number of spectators: " << spectators.size() << std::endl;
    for (auto spectator : spectators) {
        auto creatureName = proto->getCreatureName(spectator);
        std::cout << creatureName << std::endl;
        if (creatureName == "Sheep") {
            proto->attack(spectator, false);
            break;
        }
    }
    std::cout << "Finding Item" << std::endl;
    auto item = proto->findItemInContainers(3582, -1, 0);
    if (item) {
        std::cout << "Eating" << std::endl;
        proto->use(item);
    }
    playerPos.y += 1;
    auto tile = proto->getTile(playerPos);
    if (tile) {
        std::cout << "Found Tile" << std::endl;
        auto topUseItem = proto->getTopUseThing(tile);
        if (topUseItem) {
            std::cout << "Found TopUseThing" << std::endl;
            proto->open(topUseItem, 0);
        }
    }
    */
    auto localPlayer = proto->getLocalPlayer();
    std::cout << localPlayer << std::endl;
    auto equip = proto->hasEquippedItemId(localPlayer, 3357, 0);
    std::cout << "Has equiped: " << equip << std::endl;
    auto health = proto->getHealth(localPlayer);
    std::cout << "Health: " << health << std::endl;
    auto playerPos = proto->getPosition(localPlayer);
    std::cout << playerPos.x << ", " << playerPos.y << std::endl;
    auto spectators = proto->getSpectators(playerPos);
    for (auto spectator : spectators) {
        std::cout << "Spectator: " << spectator << std::endl;
        std::cout << proto->getCreatureName(spectator) << std::endl;
    }
    auto containers = proto->getContainers();
    std::cout << "Size of containers: " << containers.size() << std::endl;
    for (auto container : containers) {
        auto items = proto->getItems(containers[0]);
        std::cout << "Item Size " << items.size() << std::endl;
        for (auto item : items) {
            std::cout << proto->getItemId(item) << std::endl;
        }
    }
    return 0;
}
