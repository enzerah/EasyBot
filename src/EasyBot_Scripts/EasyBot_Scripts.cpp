#include <iostream>

#include "../../proto_functions_client.h"
#include "../../const.h"
//python -m grpc_tools.protoc -IC:\Users\Wojciech\Desktop\Projects\EasyBot_x86 --python_out=. --grpc_python_out=. C:\Users\Wojciech\Desktop\Projects\EasyBot_x86\bot.proto
int main() {
    while (true) {
        auto containers = proto->getContainers();

        for (auto container : containers) {
            auto item = proto->getItem(container, 0);
            auto creature = proto->getAttackingCreature();
            if (creature) {
                auto creaturePos = proto->getPosition(creature);
                auto tile = proto->getTile(creaturePos);
                auto thing = proto->getTopUseThing(tile);
                proto->useWith(item, thing);
                Sleep(1200);
                break;
            }
        }
    }
    return 0;
}
