#include <iostream>

#include "../../proto_functions_client.h"
#include "../../const.h"
//python -m grpc_tools.protoc -IC:\Users\Wojciech\Desktop\Projects\EasyBot86 --python_out=. --grpc_python_out=. C:\Users\Wojciech\Desktop\Projects\EasyBot86\bot.proto
int main() {
    auto localPlayer = proto->getLocalPlayer();
    auto playerPos = proto->getPosition(localPlayer);
    auto truePos = proto->getPosition(localPlayer);
    playerPos.x += 1;
    auto tile = proto->getTile(playerPos);
    auto tileItems = proto->getTileItems(tile);
    int i = 0;
    for (auto item : tileItems) {
        auto itemId = proto->getItemId(item);
        std::cout << int(itemId) << std::endl;
        if (itemId == 3277) {
            auto topThing = proto->getTopThing(tile);
            auto topThingId = proto->getItemId(topThing);
            while (topThingId != 3277) {
                auto itemCount = proto->getCount(topThing);
                proto->move(topThing, truePos, itemCount);
                Sleep(5);
                topThing = proto->getTopThing(tile);
                topThingId = proto->getItemId(topThing);
            }
            auto slot = Otc::InventorySlot::InventorySlotLeft;
            Position p;
            p.x = 0xFFFF;
            p.y = slot;
            p.z = 0;
            proto->move(topThing, p, 1);
            break;
        }
        ++i;
    }
    auto messages = proto->getMessages(5);
    for (auto message : messages) {
        std::cout << message.mode << std::endl;
        std::cout << message.name << " " << message.text << std::endl;
    }
    return 0;
}
