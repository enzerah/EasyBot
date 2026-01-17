#include <iostream>

#include "../../proto_functions_client.h"
#include "../../const.h"
//python -m grpc_tools.protoc -IC:\Users\Wojciech\Desktop\Projects\EasyBot86 --python_out=. --grpc_python_out=. C:\Users\Wojciech\Desktop\Projects\EasyBot86\bot.proto
int main() {
    auto localPlayer = proto->getLocalPlayer();
    std::cout << std::hex << localPlayer << std::endl;
    auto playerPos = proto->getPosition(localPlayer);
    auto spectators = proto->getSpectators(playerPos);
    std::cout << "Number of spectators: " << spectators.size() << std::endl;
    for (auto spectator : spectators) {
        auto creatureName = proto->getCreatureName(spectator);
        std::cout << creatureName << std::endl;
        if (creatureName == "Rotworm") {
            proto->attack(spectator, false);
            break;
        }
    }
    std::cout << "Finding Item" << std::endl;
    auto item = proto->findItemInContainers(3577, -1, 0);
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
    return 0;
}
