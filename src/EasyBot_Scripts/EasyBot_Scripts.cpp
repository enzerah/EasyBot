#include <iostream>

#include "../../proto_functions_client.h"
#include "../../const.h"
//python -m grpc_tools.protoc -IC:\Users\Wojciech\Desktop\Projects\EasyBot86 --python_out=. --grpc_python_out=. C:\Users\Wojciech\Desktop\Projects\EasyBot86\bot.proto
int main() {
    auto messages = proto->getMessages(5);
    for (auto message : messages) {
        std::cout << message.name << " " << message.text << std::endl;
    }
    return 0;
}
