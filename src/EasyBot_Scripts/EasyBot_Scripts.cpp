#include <iostream>

#include "../../proto_functions_client.h"
#include "../../const.h"
//python -m grpc_tools.protoc -IC:\Users\Wojciech\Desktop\Projects\EasyBot_x86 --python_out=. --grpc_python_out=. C:\Users\Wojciech\Desktop\Projects\EasyBot_x86\bot.proto
int main() {
    std::cout << "Starting scripts" << std::endl;
    auto localPlayer = proto->getLocalPlayer();
    proto->talkChannel(Otc::MessageSay, 1, "Pozdro Xanaved");
    std::cout << std::hex << localPlayer << std::endl;
    auto hp = proto->getHealth(localPlayer);
    std::cout << hp << std::endl;
    auto localPlayerPos = proto->getPosition(localPlayer);
    std::cout << localPlayerPos.x  << ", " << localPlayerPos.y << std::endl;
    return 0;
}
