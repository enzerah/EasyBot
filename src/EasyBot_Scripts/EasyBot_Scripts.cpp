#include <iostream>

#include "../../proto_functions_client.h"
#include "../../const.h"
//python -m grpc_tools.protoc -IC:\Users\Wojciech\Desktop\Projects\EasyBot_x86 --python_out=. --grpc_python_out=. C:\Users\Wojciech\Desktop\Projects\EasyBot_x86\bot.proto
int main() {
    auto containers = proto->getContainers();
    for (auto container : containers)
    {
        auto items = proto->getItems(container);
        for (auto item : items)
        {
            auto itemId = proto->getItemId(item);
            //std::cout << itemId << std::endl;
        }
    }
    auto item = proto->findItemInContainers(2874, 0, 0);
    std::cout << std::hex << item << std::endl;

    return 0;
}
