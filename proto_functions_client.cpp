//
// Created by blazz on 05.11.2025.
//

#include "proto_functions_client.h"
BotClient* BotClient::instance{nullptr};
std::mutex BotClient::mutex;


BotClient::BotClient() {
    std::string server_address("localhost:50051");
    std::shared_ptr<Channel> channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    stub = BotService::NewStub(channel);
}

BotClient* BotClient::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new BotClient();
    }
    return instance;
}

// Functions:
// Game
void BotClient::walk(Otc::Direction direction, bool withPreWalk)
{
    bot_WalkRequest request;
    request.set_direction(static_cast<bot_Direction>(direction));
    request.set_withprewalk(withPreWalk);
    Empty response;
    ClientContext context;
    Status status = stub->Walk(&context, request, &response);
}

void BotClient::turn(Otc::Direction direction)
{
    bot_TurnRequest request;
    auto dir = static_cast<bot_Direction>(direction);
    request.set_direction(dir);
    Empty response;
    ClientContext context;
    Status status = stub->Turn(&context, request, &response);
}

void BotClient::move(const uintptr_t& thing, const Position& toPos, int count)
{
    bot_MoveRequest request;
    request.mutable_thing()->set_value(thing);
    bot_Position* position = request.mutable_topos();
    position->set_x(toPos.x);
    position->set_y(toPos.y);
    position->set_z(toPos.z);
    request.set_count(count);
    Empty response;
    ClientContext context;
    Status status = stub->Move(&context, request, &response);
}

void BotClient::use(const uintptr_t& thing)
{
    UInt64Value request;
    request.set_value(thing);
    Empty response;
    ClientContext context;
    Status status = stub->Use(&context, request, &response);
}

void BotClient::useWith(const uintptr_t& item, const uintptr_t& toThing)
{
    bot_UseWithRequest request;
    request.mutable_item()->set_value(item);
    request.mutable_tothing()->set_value(toThing);
    Empty response;
    ClientContext context;
    Status status = stub->UseWith(&context, request, &response);
}

void BotClient::useInventoryItem(const uint16_t itemId) {
    Int32Value request;
    request.set_value(itemId);
    Empty response;
    ClientContext context;
    Status status = stub->UseInventoryItem(&context, request, &response);
}

void BotClient::useInventoryItemWith(const uint16_t itemId, const uintptr_t &toThing) {
    bot_UseInventoryItemWithRequest request;
    request.mutable_itemid()->set_value(itemId);
    request.mutable_tothing()->set_value(toThing);
    Empty response;
    ClientContext context;
    Status status = stub->UseInventoryItemWith(&context, request, &response);
}

uintptr_t BotClient::findItemInContainers(const uint32_t itemId, const int subType, const uint8_t tier)
{
    bot_FindItemInContainersRequest request;
    request.set_itemid(itemId);
    request.set_subtype(subType);
    request.set_tier(tier);
    UInt64Value response;
    ClientContext context;
    Status status = stub->FindItemInContainers(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0;
}

int BotClient::open(const uintptr_t& item, const uintptr_t& previousContainer)
{
    bot_OpenRequest request;
    request.mutable_item()->set_value(item);
    request.mutable_previouscontainer()->set_value(previousContainer);

    google::protobuf::Int32Value response;
    ClientContext context;
    Status status = stub->Open(&context, request, &response);

    if (status.ok()) {
        return response.value();
    }
    return 0;
}

void BotClient::openParent(const uintptr_t& container)
{
    UInt64Value request;
    request.set_value(container);
    Empty response;
    ClientContext context;
    Status status = stub->OpenParent(&context, request, &response);
}

void BotClient::close(const uintptr_t& container)
{
    UInt64Value request;
    request.set_value(container);
    Empty response;
    ClientContext context;
    Status status = stub->Close(&context, request, &response);
}

void BotClient::refreshContainer(const uintptr_t& container)
{
    UInt64Value request;
    request.set_value(container);
    Empty response;
    ClientContext context;
    Status status = stub->RefreshContainer(&context, request, &response);
}

void BotClient::attack(uintptr_t creature, bool cancel)
{
    bot_AttackRequest request;
    request.mutable_creature()->set_value(creature);
    request.set_cancel(cancel);

    Empty response;
    ClientContext context;
    Status status = stub->Attack(&context, request, &response);
}

uintptr_t BotClient::getLocalPlayer()
{
    Empty request;
    UInt64Value response;
    ClientContext context;
    Status status = stub->GetLocalPlayer(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0;
}

void BotClient::equipItem(const uintptr_t& item)
{
    UInt64Value request;
    request.set_value(item);
    Empty response;
    ClientContext context;
    Status status = stub->EquipItem(&context, request, &response);
}

void BotClient::cancelAttack()
{
    Empty request;
    Empty response;
    ClientContext context;
    Status status = stub->CancelAttack(&context, request, &response);
}

void BotClient::talkChannel(Otc::MessageMode msgMode, int channelId, const std::string& message)
{
    bot_TalkChannelRequest request;
    request.set_msgmode(static_cast<bot_MessageMode>(msgMode));
    request.set_channelid(channelId);
    request.set_message(message);

    Empty response;
    ClientContext context;
    Status status = stub->TalkChannel(&context, request, &response);
}

void BotClient::talkPrivate(const Otc::MessageMode msgMode, const std::string& receiver, const std::string& message)
{
    bot_TalkPrivateRequest request;
    request.set_msgmode(static_cast<bot_MessageMode>(msgMode));
    request.set_receiver(receiver);
    request.set_message(message);

    Empty response;
    ClientContext context;
    Status status = stub->TalkPrivate(&context, request, &response);
}

bool BotClient::canPerformGameAction()
{
    Empty request;
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->CanPerformGameAction(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

bool BotClient::isAttacking()
{
    Empty request;
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->IsAttacking(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

uintptr_t BotClient::getContainer(int index)
{
    google::protobuf::Int32Value request;
    request.set_value(index);
    UInt64Value response;
    ClientContext context;
    Status status = stub->GetContainer(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0;
}

std::vector<uintptr_t> BotClient::getContainers()
{
    Empty request;
    bot_Uint64List response;
    ClientContext context;
    Status status = stub->GetContainers(&context, request, &response);
    std::vector<uintptr_t> containers;
    if (status.ok()) {
        for (const auto& item : response.items()) {
            containers.push_back(item);
        }
    }
    return containers;
}

uintptr_t BotClient::getAttackingCreature()
{
    Empty request;
    UInt64Value response;
    ClientContext context;
    Status status = stub->GetAttackingCreature(&context, request, &response);

    if (status.ok()) {
        return response.value();
    }
    return 0;
}

// Container
std::deque<uintptr_t> BotClient::getItems(uintptr_t container)
{
    UInt64Value request;
    request.set_value(container);
    bot_Uint64List response;
    ClientContext context;
    Status status = stub->GetItems(&context, request, &response);
    std::deque<uintptr_t> items;
    if (status.ok()) {
        for (const auto& item : response.items()) {
            items.push_back(item);
        }
    }
    return items;
}

int BotClient::getItemsCount(uintptr_t container)
{
    UInt64Value request;
    request.set_value(container);
    google::protobuf::Int32Value response;
    ClientContext context;
    Status status = stub->GetItemsCount(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return -1;
}

Position BotClient::getSlotPosition(uintptr_t container, int slot)
{
    bot_GetSlotPositionRequest request;
    request.mutable_container()->set_value(container);
    request.set_slot(slot);
    bot_Position response;
    ClientContext context;
    Status status = stub->GetSlotPosition(&context, request, &response);
    if (status.ok()) {
        Position position{};
        position.x = response.x();
        position.y = response.y();
        position.z = response.z();
        return position;
    }
    return {};
}

std::string BotClient::getName(uintptr_t container)
{
    UInt64Value request;
    request.set_value(container);
    google::protobuf::StringValue response;
    ClientContext context;
    Status status = stub->GetContainerName(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return "";
}

uintptr_t BotClient::getContainerItem(uintptr_t container)
{
    UInt64Value request;
    request.set_value(container);
    UInt64Value response;
    ClientContext context;
    Status status = stub->GetItem(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0;
}

bool BotClient::hasParent(uintptr_t container)
{
    UInt64Value request;
    request.set_value(container);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->HasParent(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

int BotClient::getFirstIndex(uintptr_t container)
{
    UInt64Value request;
    request.set_value(container);
    google::protobuf::Int32Value response;
    ClientContext context;
    Status status = stub->GetFirstIndex(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return -1;
}

// Creature
std::string BotClient::getCreatureName(uintptr_t creature)
{
    UInt64Value request;
    request.set_value(creature);
    google::protobuf::StringValue response;
    ClientContext context;
    Status status = stub->GetName(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return "";
}

uint8_t BotClient::getHealthPercent(uintptr_t creature)
{
    UInt64Value request;
    request.set_value(creature);
    google::protobuf::UInt32Value response;
    ClientContext context;
    Status status = stub->GetHealthPercent(&context, request, &response);
    if (status.ok()) {
        return static_cast<uint8_t>(response.value());
    }
    return 0;
}

Otc::Direction BotClient::getDirection(uintptr_t creature)
{
    UInt64Value request;
    request.set_value(creature);
    bot_DirectionRequest response;
    ClientContext context;
    Status status = stub->GetDirection(&context, request, &response);

    if (status.ok()) {
        return static_cast<Otc::Direction>(response.dir());
    }
    return Otc::Direction::InvalidDirection;
}

bool BotClient::isDead(uintptr_t creature)
{
    UInt64Value request;
    request.set_value(creature);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->IsDead(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return true;
}

bool BotClient::canBeSeen(uintptr_t creature)
{
    UInt64Value request;
    request.set_value(creature);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->CanBeSeen(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

bool BotClient::isCovered(uintptr_t creature)
{
    UInt64Value request;
    request.set_value(creature);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->IsCovered(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return true;
}

bool BotClient::canShoot(uintptr_t creature)
{
    UInt64Value request;
    request.set_value(creature);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->CanShoot(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

// Item
int BotClient::getCount(uintptr_t item)
{
    UInt64Value request;
    request.set_value(item);
    google::protobuf::Int32Value response;
    ClientContext context;
    Status status = stub->GetCount(&context, request, &response);
    if(status.ok()) {
        return response.value();
    }
    return 0;
}

uint32_t BotClient::getItemId(uintptr_t item)
{
    UInt64Value request;
    request.set_value(item);
    google::protobuf::UInt32Value response;
    ClientContext context;
    Status status = stub->GetId(&context, request, &response);
    if(status.ok()) {
        return response.value();
    }
    return 0;
}

// LocalPlayer
uint32_t BotClient::getStates(uintptr_t localPlayer)
{
    UInt64Value request;
    request.set_value(localPlayer);
    google::protobuf::UInt32Value response;
    ClientContext context;
    Status status = stub->GetStates(&context, request, &response);

    if (status.ok()) {
        return response.value();
    }
    return 0;
}

double BotClient::getHealth(uintptr_t localPlayer)
{
    UInt64Value request;
    request.set_value(localPlayer);
    google::protobuf::DoubleValue response;
    ClientContext context;
    Status status = stub->GetHealth(&context, request, &response);

    if (status.ok()) {
        return response.value();
    }
    return 0.0;
}

double BotClient::getMaxHealth(uintptr_t localPlayer)
{
    UInt64Value request;
    request.set_value(localPlayer);
    google::protobuf::DoubleValue response;
    ClientContext context;
    Status status = stub->GetMaxHealth(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0.0;
}

double BotClient::getFreeCapacity(uintptr_t localPlayer)
{
    UInt64Value request;
    request.set_value(localPlayer);
    google::protobuf::DoubleValue response;
    ClientContext context;
    Status status = stub->GetFreeCapacity(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0.0;
}

uint16_t BotClient::getLevel(uintptr_t localPlayer)
{
    UInt64Value request;
    request.set_value(localPlayer);
    google::protobuf::UInt32Value response;
    ClientContext context;
    Status status = stub->GetLevel(&context, request, &response);
    if (status.ok()) {
        return static_cast<uint16_t>(response.value());
    }
    return 0;
}

double BotClient::getMana(uintptr_t localPlayer)
{
    UInt64Value request;
    request.set_value(localPlayer);
    google::protobuf::DoubleValue response;
    ClientContext context;
    Status status = stub->GetMana(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0.0;
}

double BotClient::getMaxMana(uintptr_t localPlayer)
{
    UInt64Value request;
    request.set_value(localPlayer);
    google::protobuf::DoubleValue response;
    ClientContext context;
    Status status = stub->GetMaxMana(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0.0;
}

uint8_t BotClient::getSoul(uintptr_t localPlayer)
{
    UInt64Value request;
    request.set_value(localPlayer);
    google::protobuf::UInt32Value response;
    ClientContext context;
    Status status = stub->GetSoul(&context, request, &response);
    if (status.ok()) {
        return static_cast<uint8_t>(response.value());
    }
    return 0;
}

uint16_t BotClient::getStamina(uintptr_t localPlayer)
{
    UInt64Value request;
    request.set_value(localPlayer);
    google::protobuf::UInt32Value response;
    ClientContext context;
    Status status = stub->GetStamina(&context, request, &response);
    if (status.ok()) {
        return static_cast<uint16_t>(response.value());
    }
    return 0;
}

bool BotClient::hasSight(uintptr_t localPlayer, const Position& pos)
{
    bot_HasSightRequest request;
    request.mutable_localplayer()->set_value(localPlayer);
    request.mutable_pos()->set_x(pos.x);
    request.mutable_pos()->set_y(pos.y);
    request.mutable_pos()->set_z(pos.z);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->HasSight(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

bool BotClient::isAutoWalking(uintptr_t localPlayer)
{
    UInt64Value request;
    request.set_value(localPlayer);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->IsAutoWalking(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

void BotClient::stopAutoWalk(uintptr_t localPlayer)
{
    UInt64Value request;
    request.set_value(localPlayer);
    Empty response;
    ClientContext context;
    Status status = stub->StopAutoWalk(&context, request, &response);
}

bool BotClient::autoWalk(uintptr_t localPlayer, const Position& destination, bool retry)
{
    bot_AutoWalkRequest request;
    request.mutable_localplayer()->set_value(localPlayer);
    request.mutable_destination()->set_x(destination.x);
    request.mutable_destination()->set_y(destination.y);
    request.mutable_destination()->set_z(destination.z);
    request.set_retry(retry);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->AutoWalk(&context, request, &response);

    if (status.ok()) {
        return response.value();
    }
    return false;
}

// Map
uintptr_t BotClient::getTile(const Position& tilePos)
{
    bot_Position request;
    request.set_x(tilePos.x);
    request.set_y(tilePos.y);
    request.set_z(tilePos.z);
    UInt64Value response;
    ClientContext context;
    Status status = stub->GetTile(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0;
}

std::vector<uintptr_t> BotClient::getSpectators(const Position& centerPos, bool multiFloor)
{
    bot_GetSpectatorsRequest request;
    request.mutable_centerpos()->set_x(centerPos.x);
    request.mutable_centerpos()->set_y(centerPos.y);
    request.mutable_centerpos()->set_z(centerPos.z);
    request.set_multifloor(multiFloor);
    bot_Uint64List response;
    ClientContext context;
    Status status = stub->GetSpectators(&context, request, &response);
    std::vector<uintptr_t> spectators;
    if (status.ok()) {
        spectators.reserve(response.items_size());
        for (const auto& item : response.items()) {
            spectators.push_back(item);
        }
    }
    return spectators;
}

std::vector<Otc::Direction> BotClient::findPath(const Position& startPos, const Position& goalPos, int maxComplexity, int flags)
{
    bot_FindPathRequest request;
    request.mutable_startpos()->set_x(startPos.x);
    request.mutable_startpos()->set_y(startPos.y);
    request.mutable_startpos()->set_z(startPos.z);
    request.mutable_goalpos()->set_x(goalPos.x);
    request.mutable_goalpos()->set_y(goalPos.y);
    request.mutable_goalpos()->set_z(goalPos.z);
    request.set_maxcomplexity(maxComplexity);
    request.set_flags(flags);
    bot_DirectionList response;
    ClientContext context;
    Status status = stub->FindPath(&context, request, &response);
    std::vector<Otc::Direction> directions;
    if (status.ok()) {
        directions.reserve(response.dirs_size());
        for (const auto& dir : response.dirs()) {
            directions.push_back(static_cast<Otc::Direction>(dir));
        }
    }
    return directions;
}

bool BotClient::isSightClear(const Position& fromPos, const Position& toPos)
{
    return false;
}


// Thing
uintptr_t BotClient::getParentContainer(uintptr_t thing)
{
    UInt64Value request;
    request.set_value(thing);
    UInt64Value response;
    ClientContext context;
    Status status = stub->GetParentContainer(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0;
}

bool BotClient::isMonster(uintptr_t thing)
{
    UInt64Value request;
    request.set_value(thing);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->IsMonster(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

bool BotClient::isNpc(uintptr_t thing)
{
    UInt64Value request;
    request.set_value(thing);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->IsNpc(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

bool BotClient::isPlayer(uintptr_t thing)
{
    UInt64Value request;
    request.set_value(thing);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->IsPlayer(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

bool BotClient::isLocalPlayer(uintptr_t thing)
{
    UInt64Value request;
    request.set_value(thing);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->IsLocalPlayer(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

bool BotClient::isContainer(uintptr_t thing)
{
    UInt64Value request;
    request.set_value(thing);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->IsContainer(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

bool BotClient::isUsable(uintptr_t thing)
{
    UInt64Value request;
    request.set_value(thing);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->IsUsable(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}

bool BotClient::isLyingCorpse(uintptr_t thing)
{
    UInt64Value request;
    request.set_value(thing);
    google::protobuf::BoolValue response;
    ClientContext context;
    Status status = stub->IsLyingCorpse(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return false;
}
uint32_t BotClient::getId(uintptr_t thing)
{
    UInt64Value request;
    request.set_value(thing);
    google::protobuf::UInt32Value response;
    ClientContext context;
    Status status = stub->GetIdThing(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0;
}

Position BotClient::getPosition(uintptr_t thing)
{
    UInt64Value request;
    request.set_value(thing);
    bot_Position response;
    ClientContext context;
    Status status = stub->GetPosition(&context, request, &response);
    if (status.ok()) {
        Position position{};
        position.x = response.x();
        position.y = response.y();
        position.z = response.z();
        return position;
    }
    return {};
}


// Tile
uintptr_t BotClient::getTopThing(uintptr_t tile)
{
    UInt64Value request;
    request.set_value(tile);
    UInt64Value response;
    ClientContext context;
    Status status = stub->GetTopThing(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0;
}

uintptr_t BotClient::getTopUseThing(uintptr_t tile)
{
    UInt64Value request;
    request.set_value(tile);
    UInt64Value response;
    ClientContext context;
    Status status = stub->GetTopUseThing(&context, request, &response);
    if (status.ok()) {
        return response.value();
    }
    return 0;
}
