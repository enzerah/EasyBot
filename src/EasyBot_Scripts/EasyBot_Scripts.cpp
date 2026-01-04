#include <iostream>

#include "../../proto_functions_client.h"
#include "../../const.h"
//python -m grpc_tools.protoc -IC:\Users\Wojciech\Desktop\Projects\EasyBot86 --python_out=. --grpc_python_out=. C:\Users\Wojciech\Desktop\Projects\EasyBot86\bot.proto
int main() {
    auto containers = proto->getContainers();
    for (auto container : containers) {
        auto items = proto->getItems(container);
        for (auto item : items) {
            if (proto->getItemId(item) == 3583) {
                proto->use(item);
                break;
            }
        }
    }
    return 0;
}
