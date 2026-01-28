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
    /*  Sell Items
    std::map<int, int> counts{};
    std::vector<int> itemsId = {3318, 3419, 3381, 3850, 3385};
    auto containers = proto->getContainers();
    for (auto container : containers) {
        auto items = proto->getItems(container);
        for (auto item : items) {
            int itemId = proto->getItemId(item);
            if (std::find(itemsId.begin(), itemsId.end(), itemId) != itemsId.end()) {
                counts[itemId]++;
            }
        }
    }
    for (int itemId : itemsId) {
        if (counts[itemId] > 0) {
            auto item = proto->findItemInContainers(itemId, -1, 0);
            proto->sellItem(item, counts[itemId], false);
            Sleep(500);
        }
    }
    */
    auto localPlayer = proto->getLocalPlayer();
    auto aol = proto->getInventoryItem(localPlayer, Otc::InventorySlotNecklace);
    proto->talk(std::to_string(aol));
    /*
    //Buy Items
    std::map<int, int> counts{};
    std::vector<int> itemsId = {3185, 3160}; // mr
    int uhToBuy = 700;
    int mrToBuy = 300;
    auto containers = proto->getContainers();
    for (auto container : containers) {
        auto items = proto->getItems(container);
        for (auto item : items) {
            int itemId = proto->getItemId(item);
            if (std::find(itemsId.begin(), itemsId.end(), itemId) != itemsId.end()) {
                auto count = proto->getCount(item);
                counts[itemId] += count;
            }
        }
    }
    for (int itemId : itemsId) {
        auto item = proto->findItemInContainers(itemId, -1, 0);
        int amount = 0;
        if (itemId == 3185) {
            amount = mrToBuy - counts[itemId];
        } else {
            amount = uhToBuy - counts[itemId];
        }
        std::cout << amount << std::endl;
        if (amount > 0) proto->buyItem(item, 5, false, false);
        Sleep(500);
    }
    */
    /*
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
    */
    return 0;
}
