#include <iostream>

#include "../../proto_functions_client.h"
#include "../../const.h"
//python -m grpc_tools.protoc -IC:\Users\Wojciech\Desktop\Projects\EasyBot86 --python_out=. --grpc_python_out=. C:\Users\Wojciech\Desktop\Projects\EasyBot86\bot.proto
int main() {
    auto localPlayer = proto->getLocalPlayer();
    auto playerPos = proto->getPosition(localPlayer);
    auto depoPos = playerPos;
    depoPos.y -= 2;
    auto path = proto->findPath(playerPos, depoPos, 100, 0);
    std::cout << path.size() << std::endl;
    return 0;
}
