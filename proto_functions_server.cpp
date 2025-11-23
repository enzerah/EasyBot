#include "proto_functions_server.h"

#include "Container.h"
#include "Creature.h"
#include "Item.h"
#include "Tile.h"

// Functions:
// Game.h
Status BotServiceImpl::Walk(grpc::ServerContext *context, const bot::bot_WalkRequest *request,
    google::protobuf::Empty *response) {
    auto direction = static_cast<Otc::Direction>(request->direction());
    g_game->walk(direction, request->withprewalk());
    return Status::OK;
}

Status BotServiceImpl::Turn(grpc::ServerContext *context, const bot::bot_TurnRequest *request,
    google::protobuf::Empty *response) {
    g_game->turn(static_cast<Otc::Direction>(request->direction()));
    return Status::OK;
}

Status BotServiceImpl::Move(grpc::ServerContext *context, const bot::bot_MoveRequest *request,
    google::protobuf::Empty *response) {
    Position pos;
    pos.x = request->topos().x();
    pos.y = request->topos().y();
    pos.z = request->topos().z();
    g_game->move(request->thing().value(), pos, request->count());
    return Status::OK;
}

Status BotServiceImpl::Use(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::Empty *response) {
    g_game->use(request->value());
    return Status::OK;
}

Status BotServiceImpl::UseWith(grpc::ServerContext *context, const bot::bot_UseWithRequest *request,
    google::protobuf::Empty *response) {
    g_game->useWith(request->item().value(), request->tothing().value());
    return Status::OK;
}

Status BotServiceImpl::UseInventoryItem(grpc::ServerContext *context, const google::protobuf::Int32Value *request,
    google::protobuf::Empty *response) {
    g_game->useInventoryItem(request->value());
    return Status::OK;
}

Status BotServiceImpl::UseInventoryItemWith(grpc::ServerContext *context,
    const bot::bot_UseInventoryItemWithRequest *request, google::protobuf::Empty *response) {
    g_game->useInventoryItemWith(request->itemid().value(), request->tothing().value());
    return Status::OK;
}

Status BotServiceImpl::FindItemInContainers(grpc::ServerContext *context,
                                            const bot::bot_FindItemInContainersRequest *request, google::protobuf::UInt64Value *response) {
    response->set_value(g_game->findItemInContainers(request->itemid(), request->subtype(), request->tier()));
    return Status::OK;
}

Status BotServiceImpl::Open(grpc::ServerContext *context, const bot::bot_OpenRequest *request,
    google::protobuf::Int32Value *response) {
    g_game->open(request->item().value(), request->previouscontainer().value());
    return Status::OK;
}

Status BotServiceImpl::OpenParent(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::Empty *response) {
    g_game->openParent(request->value());
    return Status::OK;
}

Status BotServiceImpl::Close(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::Empty *response) {
    g_game->close(request->value());
    return Status::OK;
}

Status BotServiceImpl::RefreshContainer(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::Empty *response) {
    g_game->refreshContainer(request->value());
    return Status::OK;
}

Status BotServiceImpl::Attack(grpc::ServerContext *context, const bot::bot_AttackRequest *request,
    google::protobuf::Empty *response) {
    g_game->attack(request->creature().value(), request->cancel());
    return Status::OK;
}

Status BotServiceImpl::GetLocalPlayer(grpc::ServerContext *context, const google::protobuf::Empty *request,
    google::protobuf::UInt64Value *response) {
    response->set_value(g_game->getLocalPlayer());
    return Status::OK;
}

Status BotServiceImpl::EquipItem(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::Empty *response) {
    g_game->equipItem(request->value());
    return Status::OK;
}

Status BotServiceImpl::CancelAttack(grpc::ServerContext *context, const google::protobuf::Empty *request,
    google::protobuf::Empty *response) {
    g_game->cancelAttack();
    return Status::OK;
}

Status BotServiceImpl::TalkChannel(grpc::ServerContext *context, const bot::bot_TalkChannelRequest *request,
    google::protobuf::Empty *response) {
    g_game->talkChannel(static_cast<Otc::MessageMode>(request->msgmode()), request->channelid(), request->message());
    return Status::OK;
}

Status BotServiceImpl::TalkPrivate(grpc::ServerContext *context, const bot::bot_TalkPrivateRequest *request,
    google::protobuf::Empty *response) {
    g_game->talkPrivate(static_cast<Otc::MessageMode>(request->msgmode()), request->receiver(), request->message());
    return Status::OK;
}

Status BotServiceImpl::CanPerformGameAction(grpc::ServerContext *context, const google::protobuf::Empty *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_game->canPerformGameAction());
    return Status::OK;
}

Status BotServiceImpl::IsAttacking(grpc::ServerContext *context, const google::protobuf::Empty *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_game->isAttacking());
    return Status::OK;
}

Status BotServiceImpl::GetContainer(grpc::ServerContext *context, const google::protobuf::Int32Value *request,
    google::protobuf::UInt64Value *response) {
    response->set_value(g_game->getContainer(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetContainers(grpc::ServerContext *context, const google::protobuf::Empty *request,
    bot::bot_Uint64List *response) {
    auto containers = g_game->getContainers();
    for (auto container : containers) {
        response->add_items(container);
    }
    return Status::OK;
}

Status BotServiceImpl::GetAttackingCreature(grpc::ServerContext *context, const google::protobuf::Empty *request,
    google::protobuf::UInt64Value *response) {
    response->set_value(g_game->getAttackingCreature());
    return Status::OK;
}

// Thing.h
Status BotServiceImpl::GetIdThing(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::UInt32Value *response) {
    response->set_value(g_thing->getId(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetPosition(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    bot::bot_Position *response) {
    auto position = g_thing->getPosition(request->value());
    response->set_x(position.x);
    response->set_y(position.y);
    response->set_z(position.z);
    return Status::OK;
}

Status BotServiceImpl::GetParentContainer(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::UInt64Value *response) {
    response->set_value(g_thing->getParentContainer(request->value()));
    return Status::OK;
}

Status BotServiceImpl::IsMonster(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_thing->isMonster(request->value()));
    return Status::OK;
}

Status BotServiceImpl::IsNpc(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_thing->isNpc(request->value()));
    return Status::OK;
}

Status BotServiceImpl::IsPlayer(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_thing->isPlayer(request->value()));
    return Status::OK;
}

Status BotServiceImpl::IsLocalPlayer(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_thing->isLocalPlayer(request->value()));
    return Status::OK;
}

Status BotServiceImpl::IsContainer(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_thing->isContainer(request->value()));
    return Status::OK;
}

Status BotServiceImpl::IsUsable(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_thing->isUsable(request->value()));
    return Status::OK;
}

Status BotServiceImpl::IsLyingCorpse(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_thing->isLyingCorpse(request->value()));
    return Status::OK;
}

// Tile.h
Status BotServiceImpl::GetTopThing(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::UInt64Value *response) {
    response->set_value(g_tile->getTopThing(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetTopUseThing(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::UInt64Value *response) {
    response->set_value(g_tile->getTopUseThing(request->value()));
    return Status::OK;
}

// Map.h
Status BotServiceImpl::GetTile(grpc::ServerContext *context, const bot::bot_Position *request,
    google::protobuf::UInt64Value *response) {
    Position position{};
    position.x = request->x();
    position.y = request->y();
    position.z = request->z();
    response->set_value(g_map->getTile(position));
    return Status::OK;
}

Status BotServiceImpl::GetSpectators(grpc::ServerContext *context, const bot::bot_GetSpectatorsRequest *request,
    bot::bot_Uint64List *response) {
    Position position{};
    position.x = request->centerpos().x();
    position.y = request->centerpos().y();
    position.z = request->centerpos().z();
    auto spectators = g_map->getSpectators(position, request->multifloor());
    for (auto spectator : spectators) {
        response->add_items(spectator);
    }
    return Status::OK;
}

Status BotServiceImpl::FindPath(grpc::ServerContext *context, const bot::bot_FindPathRequest *request,
    bot::bot_DirectionList *response) {
    Position startPosition{};
    Position goalPosition{};
    startPosition.x = request->startpos().x();
    startPosition.y = request->startpos().y();
    startPosition.z = request->startpos().z();
    goalPosition.x = request->goalpos().x();
    goalPosition.y = request->goalpos().y();
    goalPosition.z = request->goalpos().z();
    auto dirs = g_map->findPath(startPosition, goalPosition, request->maxcomplexity(), request->flags());
    for (auto dir : dirs) {
        response->add_dirs(static_cast<bot::bot_Direction>(dir));
    }
    return Status::OK;
}

Status BotServiceImpl::IsSightClear(grpc::ServerContext* context, const bot::bot_IsSightClearRequest* request,
    google::protobuf::BoolValue* response)
{
    return Service::IsSightClear(context, request, response);
}


// LocalPlayer.h
Status BotServiceImpl::GetStates(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::UInt32Value *response) {
    response->set_value(g_localPlayer->getStates(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetHealth(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::DoubleValue *response) {
    response->set_value(g_localPlayer->getHealth(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetMaxHealth(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::DoubleValue *response) {
    response->set_value(g_localPlayer->getMaxHealth(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetFreeCapacity(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::DoubleValue *response) {
    response->set_value(g_localPlayer->getFreeCapacity(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetLevel(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::UInt32Value *response) {
    response->set_value(g_localPlayer->getLevel(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetMana(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::DoubleValue *response) {
    response->set_value(g_localPlayer->getMana(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetMaxMana(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::DoubleValue *response) {
    response->set_value(g_localPlayer->getMaxMana(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetSoul(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::UInt32Value *response) {
    response->set_value(g_localPlayer->getSoul(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetStamina(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::UInt32Value *response) {
    response->set_value(g_localPlayer->getStamina(request->value()));
    return Status::OK;
}

Status BotServiceImpl::HasSight(grpc::ServerContext *context, const bot::bot_HasSightRequest *request,
    google::protobuf::BoolValue *response) {
    Position position{};
    position.x = request->pos().x();
    position.y = request->pos().y();
    position.z = request->pos().z();
    response->set_value(g_localPlayer->hasSight(request->localplayer().value(), position));
    return Status::OK;
}

Status BotServiceImpl::IsAutoWalking(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_localPlayer->isAutoWalking(request->value()));
    return Status::OK;
}

Status BotServiceImpl::StopAutoWalk(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::Empty *response) {
    g_localPlayer->stopAutoWalk(request->value());
    return Status::OK;
}

Status BotServiceImpl::AutoWalk(grpc::ServerContext *context, const bot::bot_AutoWalkRequest *request,
    google::protobuf::BoolValue *response) {
    Position destination{};
    destination.x = request->destination().x();
    destination.y = request->destination().y();
    destination.z = request->destination().z();
    response->set_value(g_localPlayer->autoWalk(request->localplayer().value(), destination, request->retry()));
    return Status::OK;
}

// Item.h
Status BotServiceImpl::GetDescription(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::StringValue *response) {
    response->set_value(g_item->getDescription(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetCount(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::Int32Value *response) {
    response->set_value(g_item->getCount(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetId(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::UInt32Value *response) {
    response->set_value(g_item->getId(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetText(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::StringValue *response) {
    response->set_value(g_item->getText(request->value()));
    return Status::OK;
}

// Creature.h
Status BotServiceImpl::GetName(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::StringValue *response) {
    response->set_value(g_creature->getName(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetHealthPercent(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::UInt32Value *response) {
    response->set_value(g_creature->getHealthPercent(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetDirection(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    bot::bot_DirectionRequest *response) {
    response->set_dir(static_cast<bot::bot_Direction>(g_creature->getDirection(request->value())));
    return Status::OK;
}

Status BotServiceImpl::IsDead(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_creature->isDead(request->value()));
    return Status::OK;
}

Status BotServiceImpl::CanBeSeen(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_creature->canBeSeen(request->value()));
    return Status::OK;
}

Status BotServiceImpl::IsCovered(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_creature->isCovered(request->value()));
    return Status::OK;
}

Status BotServiceImpl::CanShoot(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_creature->canShoot(request->value()));
    return Status::OK;
}

// Container.h
Status BotServiceImpl::GetItems(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    bot::bot_Uint64List *response) {
    auto items = g_container->getItems(request->value());
    for (auto item : items) {
        response->add_items(item);
    }
    return Status::OK;
}

Status BotServiceImpl::GetItemsCount(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::Int32Value *response) {
    response->set_value(g_container->getItemsCount(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetSlotPosition(grpc::ServerContext *context, const bot::bot_GetSlotPositionRequest *request,
    bot::bot_Position *response) {
    auto slotPos = g_container->getSlotPosition(request->container().value(), request->slot());
    response->set_x(slotPos.x);
    response->set_y(slotPos.y);
    response->set_z(slotPos.z);
    return Status::OK;
}

Status BotServiceImpl::GetContainerName(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::StringValue *response) {
    response->set_value(g_container->getName(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetItem(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::UInt64Value *response) {
    response->set_value(g_container->getContainerItem(request->value()));
    return Status::OK;
}

Status BotServiceImpl::HasParent(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::BoolValue *response) {
    response->set_value(g_container->hasParent(request->value()));
    return Status::OK;
}

Status BotServiceImpl::GetFirstIndex(grpc::ServerContext *context, const google::protobuf::UInt64Value *request,
    google::protobuf::Int32Value *response) {
    response->set_value(g_container->getFirstIndex(request->value()));
    return Status::OK;
}

// End of Functions


void RunServer() {
    std::string server_address("0.0.0.0:50051");
    BotServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    server->Wait();
}



