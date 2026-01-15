#include <iostream>

#include "../../proto_functions_client.h"
#include "../../const.h"
//python -m grpc_tools.protoc -IC:\Users\Wojciech\Desktop\Projects\EasyBot86 --python_out=. --grpc_python_out=. C:\Users\Wojciech\Desktop\Projects\EasyBot86\bot.proto
int main() {
    while (true) {
        auto localPlayer = proto->getLocalPlayer();
        std::cout << std::hex << localPlayer << std::endl;
        auto playerPos = proto->getPosition(localPlayer);
        std::cout << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << std::endl;
        auto spectators = proto->getSpectators(playerPos);
        std::cout << spectators.size() << std::endl;
        for (auto spectator : spectators) {
            std::cout << std::hex << spectator << std::endl;
            std::cout << proto->getCreatureName(spectator) << std::endl;
        }
    }
    return 0;
}
