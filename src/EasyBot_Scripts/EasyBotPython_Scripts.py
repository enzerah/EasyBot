#pip install grpcio protobuf grpcio-tools
#python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. bot.proto
import time

from Bot_Functions import *



# 2874 - Mp
# 3155 - Sd
# 3160 - Uh


while True:
    hp = get_health(get_local_player())
    if hp < 200:
        containers = get_containers()
        for container in containers:
            items = get_items(container)
            if items:
                itemId = get_item_id(items[0])
                if itemId == 3160:
                    use_with(items[0], get_local_player())
                    time.sleep(0.3)
                    break
    else:
        if 700 > get_mana(get_local_player()):
            containers = get_containers()
            for container in containers:
                items = get_items(container)
                if items:
                    itemId = get_item_id(items[0])
                    if itemId == 2874:
                        use_with(items[0], get_local_player())
                        time.sleep(0.3)
                        break
        containers = get_containers()
        for container in containers:
            items = get_items(container)
            if items:
                itemId = get_item_id(items[0])
                if itemId == 3155:
                    creature = get_attacking_creature()
                    if creature:
                        tile = get_tile(get_position(creature))
                        thing = get_top_use_thing(tile)
                        use_with(items[0], thing)
                        time.sleep(0.3)
                        break
