#include <iostream>

#include "../../proto_functions_client.h"
#include "../../const.h"
//python -m grpc_tools.protoc -IC:\Users\Wojciech\Desktop\Projects\EasyBot86 --python_out=. --grpc_python_out=. C:\Users\Wojciech\Desktop\Projects\EasyBot86\bot.proto
int main() {
    auto localPlayer = proto->getLocalPlayer();
    std::cout << std::hex << localPlayer << std::endl;
    auto hp = proto->getHealth(localPlayer);
    std::cout << hp << std::endl;
    proto->talk("Siema");
    auto pos = proto->getPosition(localPlayer);
    std::cout << pos.x << ", " << pos.y << std::endl;
    return 0;
}
