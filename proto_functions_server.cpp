#include "proto_functions_server.h"

#include "Container.h"
#include "Game.h"
#include "Tile.h"
#include "Map.h"
#include "Thing.h"
#include "LocalPlayer.h"
#include "Creature.h"
#include "Item.h"

// Functions:
// ================= Container.h =================
Status BotServiceImpl::GetItem(ServerContext* context, const bot::bot_GetItemRequest* request, google::protobuf::UInt64Value* response) {
    auto result = g_container->getItem(request->container(), request->slot());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetItems(ServerContext* context, const google::protobuf::UInt64Value* request, bot::bot_Uint64List* response) {
    auto result = g_container->getItems(request->value());
    for(const auto& val : result) {
        response->add_items(val);
    }
    return Status::OK;
}

Status BotServiceImpl::GetItemsCount(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Int32Value* response) {
    auto result = g_container->getItemsCount(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetSlotPosition(ServerContext* context, const bot::bot_GetSlotPositionRequest* request, bot::bot_Position* response) {
    auto result = g_container->getSlotPosition(request->container(), request->slot());
    response->set_x(result.x);
    response->set_y(result.y);
    response->set_z(result.z);
    return Status::OK;
}

Status BotServiceImpl::GetContainerName(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::StringValue* response) {
    auto result = g_container->getName(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetContainerId(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Int32Value* response) {
    auto result = g_container->getId(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetContainerItem(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt64Value* response) {
    auto result = g_container->getContainerItem(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::HasParent(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_container->hasParent(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetSize(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Int32Value* response) {
    auto result = g_container->getSize(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetFirstIndex(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Int32Value* response) {
    auto result = g_container->getFirstIndex(request->value());
    response->set_value(result);
    return Status::OK;
}

// ================= Creature.h =================
Status BotServiceImpl::GetCreatureName(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::StringValue* response) {
    auto result = g_creature->getName(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetHealthPercent(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt32Value* response) {
    auto result = g_creature->getHealthPercent(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetDirection(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Int32Value* response) {
    auto result = g_creature->getDirection(request->value());
    response->set_value(static_cast<int32_t>(result));
    return Status::OK;
}

Status BotServiceImpl::IsDead(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_creature->isDead(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::CanBeSeen(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_creature->canBeSeen(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsCovered(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_creature->isCovered(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::CanShoot(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_creature->canShoot(request->value());
    response->set_value(result);
    return Status::OK;
}

// ================= Game.h =================
Status BotServiceImpl::Walk(ServerContext* context, const google::protobuf::Int32Value* request, google::protobuf::Empty* response) {
    auto direction_val = static_cast<Otc::Direction>(request->value());
    g_game->walk(direction_val);
    return Status::OK;
}

Status BotServiceImpl::AutoWalkGame(ServerContext* context, const bot::bot_AutoWalkGameRequest* request, google::protobuf::Empty* response) {
    const auto& repeated_dirs = request->direction().dirs();
    std::vector<Otc::Direction> dirs;
    dirs.reserve(repeated_dirs.size());
    for (auto item : repeated_dirs) {
        dirs.push_back(static_cast<Otc::Direction>(item));
    }

    Position startPos_val;
    startPos_val.x = request->startpos().x();
    startPos_val.y = request->startpos().y();
    startPos_val.z = request->startpos().z();

    g_game->autoWalk(dirs, startPos_val);
    return Status::OK;
}

Status BotServiceImpl::Turn(ServerContext* context, const google::protobuf::Int32Value* request, google::protobuf::Empty* response) {
    auto direction_val = static_cast<Otc::Direction>(request->value());
    g_game->turn(direction_val);
    return Status::OK;
}

Status BotServiceImpl::Stop(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::Empty* response) {
    g_game->stop();
    return Status::OK;
}

Status BotServiceImpl::Move(ServerContext* context, const bot::bot_MoveRequest* request, google::protobuf::Empty* response) {
    Position toPos_val;
    toPos_val.x = request->topos().x();
    toPos_val.y = request->topos().y();
    toPos_val.z = request->topos().z();
    g_game->move(request->thing(), toPos_val, request->count());
    return Status::OK;
}

Status BotServiceImpl::MoveToParentContainer(ServerContext* context, const bot::bot_MoveToParentContainerRequest* request, google::protobuf::Empty* response) {
    g_game->moveToParentContainer(request->thing(), request->count());
    return Status::OK;
}

Status BotServiceImpl::Use(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Empty* response) {
    g_game->use(request->value());
    return Status::OK;
}

Status BotServiceImpl::UseWith(ServerContext* context, const bot::bot_UseWithRequest* request, google::protobuf::Empty* response) {
    g_game->useWith(request->item(), request->tothing());
    return Status::OK;
}

Status BotServiceImpl::UseInventoryItem(ServerContext* context, const google::protobuf::UInt32Value* request, google::protobuf::Empty* response) {
    g_game->useInventoryItem(request->value());
    return Status::OK;
}

Status BotServiceImpl::UseInventoryItemWith(ServerContext* context, const bot::bot_UseInventoryItemWithRequest* request, google::protobuf::Empty* response) {
    g_game->useInventoryItemWith(request->itemid(), request->tothing());
    return Status::OK;
}

Status BotServiceImpl::FindItemInContainers(ServerContext* context, const bot::bot_FindItemInContainersRequest* request, google::protobuf::UInt64Value* response) {
    auto result = g_game->findItemInContainers(request->itemid(), request->subtype(), request->tier());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::Open(ServerContext* context, const bot::bot_OpenRequest* request, google::protobuf::Int32Value* response) {
    auto result = g_game->open(request->item(), request->previouscontainer());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::OpenParent(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Empty* response) {
    g_game->openParent(request->value());
    return Status::OK;
}

Status BotServiceImpl::Close(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Empty* response) {
    g_game->close(request->value());
    return Status::OK;
}

Status BotServiceImpl::RefreshContainer(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Empty* response) {
    g_game->refreshContainer(request->value());
    return Status::OK;
}

Status BotServiceImpl::Attack(ServerContext* context, const bot::bot_AttackRequest* request, google::protobuf::Empty* response) {
    g_game->attack(request->creature(), request->cancel());
    return Status::OK;
}

Status BotServiceImpl::CancelAttack(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::Empty* response) {
    g_game->cancelAttack();
    return Status::OK;
}

Status BotServiceImpl::Follow(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Empty* response) {
    g_game->follow(request->value());
    return Status::OK;
}

Status BotServiceImpl::CancelAttackAndFollow(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::Empty* response) {
    g_game->cancelAttackAndFollow();
    return Status::OK;
}

Status BotServiceImpl::Talk(ServerContext* context, const google::protobuf::StringValue* request, google::protobuf::Empty* response) {
    g_game->talk(request->value());
    return Status::OK;
}

Status BotServiceImpl::TalkChannel(ServerContext* context, const bot::bot_TalkChannelRequest* request, google::protobuf::Empty* response) {
    auto mode_val = static_cast<Otc::MessageMode>(request->mode());
    g_game->talkChannel(mode_val, request->channelid(), request->message());
    return Status::OK;
}

Status BotServiceImpl::TalkPrivate(ServerContext* context, const bot::bot_TalkPrivateRequest* request, google::protobuf::Empty* response) {
    auto msgMode_val = static_cast<Otc::MessageMode>(request->msgmode());
    g_game->talkPrivate(msgMode_val, request->receiver(), request->message());
    return Status::OK;
}

Status BotServiceImpl::OpenPrivateChannel(ServerContext* context, const google::protobuf::StringValue* request, google::protobuf::Empty* response) {
    g_game->openPrivateChannel(request->value());
    return Status::OK;
}

Status BotServiceImpl::SetChaseMode(ServerContext* context, const google::protobuf::Int32Value* request, google::protobuf::Empty* response) {
    auto mode_val = static_cast<Otc::ChaseModes>(request->value());
    g_game->setChaseMode(mode_val);
    return Status::OK;
}

Status BotServiceImpl::SetFightMode(ServerContext* context, const google::protobuf::Int32Value* request, google::protobuf::Empty* response) {
    auto mode_val = static_cast<Otc::FightModes>(request->value());
    g_game->setFightMode(mode_val);
    return Status::OK;
}

Status BotServiceImpl::BuyItem(ServerContext* context, const bot::bot_BuyItemRequest* request, google::protobuf::Empty* response) {
    g_game->buyItem(request->item(), request->amount(), request->ignorecapacity(), request->buywithbackpack());
    return Status::OK;
}

Status BotServiceImpl::SellItem(ServerContext* context, const bot::bot_SellItemRequest* request, google::protobuf::Empty* response) {
    g_game->sellItem(request->item(), request->amount(), request->ignoreequipped());
    return Status::OK;
}

Status BotServiceImpl::EquipItem(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Empty* response) {
    g_game->equipItem(request->value());
    return Status::OK;
}

Status BotServiceImpl::EquipItemId(ServerContext* context, const bot::bot_EquipItemIdRequest* request, google::protobuf::Empty* response) {
    g_game->equipItemId(request->itemid(), request->tier());
    return Status::OK;
}

Status BotServiceImpl::Mount(ServerContext* context, const google::protobuf::BoolValue* request, google::protobuf::Empty* response) {
    g_game->mount(request->value());
    return Status::OK;
}

Status BotServiceImpl::ChangeMapAwareRange(ServerContext* context, const bot::bot_ChangeMapAwareRangeRequest* request, google::protobuf::Empty* response) {
    g_game->changeMapAwareRange(request->xrange(), request->yrange());
    return Status::OK;
}

Status BotServiceImpl::CanPerformGameAction(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::BoolValue* response) {
    auto result = g_game->canPerformGameAction();
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsOnline(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::BoolValue* response) {
    auto result = g_game->isOnline();
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsAttacking(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::BoolValue* response) {
    auto result = g_game->isAttacking();
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsFollowing(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::BoolValue* response) {
    auto result = g_game->isFollowing();
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetContainer(ServerContext* context, const google::protobuf::Int32Value* request, google::protobuf::UInt64Value* response) {
    auto result = g_game->getContainer(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetContainers(ServerContext* context, const google::protobuf::Empty* request, bot::bot_Uint64List* response) {
    auto containers = g_game->getContainers();
    for (auto container : containers) {
        response->add_items(container);
    }
    return Status::OK;
}

Status BotServiceImpl::GetAttackingCreature(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::UInt64Value* response) {
    auto result = g_game->getAttackingCreature();
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetFollowingCreature(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::UInt64Value* response) {
    auto result = g_game->getFollowingCreature();
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetLocalPlayer(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::UInt64Value* response) {
    auto result = g_game->getLocalPlayer();
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetClientVersion(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::Int32Value* response) {
    auto result = g_game->getClientVersion();
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetCharacterName(ServerContext* context, const google::protobuf::Empty* request, google::protobuf::StringValue* response) {
    auto result = g_game->getCharacterName();
    response->set_value(result);
    return Status::OK;
}

// ================= Item.h =================
Status BotServiceImpl::GetCount(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Int32Value* response) {
    auto result = g_item->getCount(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetSubType(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Int32Value* response) {
    auto result = g_item->getSubType(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetItemId(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt32Value* response) {
    auto result = g_item->getId(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetTooltip(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::StringValue* response) {
    auto result = g_item->getTooltip(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetDurationTime(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt32Value* response) {
    auto result = g_item->getDurationTime(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetItemName(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::StringValue* response) {
    auto result = g_item->getName(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetDescription(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::StringValue* response) {
    auto result = g_item->getDescription(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetTier(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt32Value* response) {
    auto result = g_item->getTier(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetText(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::StringValue* response) {
    auto result = g_item->getText(request->value());
    response->set_value(result);
    return Status::OK;
}

// ================= LocalPlayer.h =================
Status BotServiceImpl::IsWalkLocked(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_localPlayer->isWalkLocked(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetStates(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt32Value* response) {
    auto result = g_localPlayer->getStates(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetHealth(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::DoubleValue* response) {
    auto result = g_localPlayer->getHealth(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetMaxHealth(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::DoubleValue* response) {
    auto result = g_localPlayer->getMaxHealth(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetFreeCapacity(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::DoubleValue* response) {
    auto result = g_localPlayer->getFreeCapacity(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetLevel(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt32Value* response) {
    auto result = g_localPlayer->getLevel(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetMana(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::DoubleValue* response) {
    auto result = g_localPlayer->getMana(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetMaxMana(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::DoubleValue* response) {
    auto result = g_localPlayer->getMaxMana(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetManaShield(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt32Value* response) {
    auto result = g_localPlayer->getManaShield(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetSoul(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt32Value* response) {
    auto result = g_localPlayer->getSoul(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetStamina(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt32Value* response) {
    auto result = g_localPlayer->getStamina(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetInventoryItem(ServerContext* context, const bot::bot_GetInventoryItemRequest* request, google::protobuf::UInt64Value* response) {
    auto inventorySlot_val = static_cast<Otc::InventorySlot>(request->inventoryslot());
    auto result = g_localPlayer->getInventoryItem(request->localplayer(), inventorySlot_val);
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::HasEquippedItemId(ServerContext* context, const bot::bot_HasEquippedItemIdRequest* request, google::protobuf::BoolValue* response) {
    auto result = g_localPlayer->hasEquippedItemId(request->localplayer(), request->itemid(), request->tier());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetInventoryCount(ServerContext* context, const bot::bot_GetInventoryCountRequest* request, google::protobuf::UInt32Value* response) {
    auto result = g_localPlayer->getInventoryCount(request->localplayer(), request->itemid(), request->tier());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::HasSight(ServerContext* context, const bot::bot_HasSightRequest* request, google::protobuf::BoolValue* response) {
    Position pos_val;
    pos_val.x = request->pos().x();
    pos_val.y = request->pos().y();
    pos_val.z = request->pos().z();
    auto result = g_localPlayer->hasSight(request->localplayer(), pos_val);
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsAutoWalking(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_localPlayer->isAutoWalking(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::StopAutoWalk(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::Empty* response) {
    g_localPlayer->stopAutoWalk(request->value());
    return Status::OK;
}

Status BotServiceImpl::AutoWalk(ServerContext* context, const bot::bot_AutoWalkRequest* request, google::protobuf::BoolValue* response) {
    Position destination_val;
    destination_val.x = request->destination().x();
    destination_val.y = request->destination().y();
    destination_val.z = request->destination().z();
    auto result = g_localPlayer->autoWalk(request->localplayer(), destination_val, request->retry());
    response->set_value(result);
    return Status::OK;
}

// ================= Map.h =================
Status BotServiceImpl::GetTile(ServerContext* context, const bot::bot_Position* request, google::protobuf::UInt64Value* response) {
    Position tilePos_val;
    tilePos_val.x = request->x();
    tilePos_val.y = request->y();
    tilePos_val.z = request->z();
    auto result = g_map->getTile(tilePos_val);
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetSpectators(ServerContext* context, const bot::bot_GetSpectatorsRequest* request, bot::bot_Uint64List* response) {
    Position centerPos_val;
    centerPos_val.x = request->centerpos().x();
    centerPos_val.y = request->centerpos().y();
    centerPos_val.z = request->centerpos().z();
    auto spectators = g_map->getSpectators(centerPos_val, request->multifloor());
    for(auto spectator : spectators) {
        response->add_items(spectator);
    }
    return Status::OK;
}

Status BotServiceImpl::FindPath(ServerContext* context, const bot::bot_FindPathRequest* request, bot::bot_DirectionList* response) {
    Position startPos_val;
    startPos_val.x = request->startpos().x();
    startPos_val.y = request->startpos().y();
    startPos_val.z = request->startpos().z();
    Position goalPos_val;
    goalPos_val.x = request->goalpos().x();
    goalPos_val.y = request->goalpos().y();
    goalPos_val.z = request->goalpos().z();
    auto path = g_map->findPath(startPos_val, goalPos_val, request->maxcomplexity(), request->flags());
    for(auto dir : path) {
        response->add_dirs(static_cast<bot::bot_Direction>(dir));
    }
    return Status::OK;
}

Status BotServiceImpl::IsWalkable(ServerContext* context, const bot::bot_IsWalkableRequest* request, google::protobuf::BoolValue* response) {
    Position pos_val;
    pos_val.x = request->pos().x();
    pos_val.y = request->pos().y();
    pos_val.z = request->pos().z();
    auto result = g_map->isWalkable(pos_val, request->ignorecreatures());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsSightClear(ServerContext* context, const bot::bot_IsSightClearRequest* request, google::protobuf::BoolValue* response) {
    Position fromPos_val;
    fromPos_val.x = request->frompos().x();
    fromPos_val.y = request->frompos().y();
    fromPos_val.z = request->frompos().z();
    Position toPos_val;
    toPos_val.x = request->topos().x();
    toPos_val.y = request->topos().y();
    toPos_val.z = request->topos().z();
    auto result = g_map->isSightClear(fromPos_val, toPos_val);
    response->set_value(result);
    return Status::OK;
}

// ================= Thing.h =================
Status BotServiceImpl::GetId(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt32Value* response) {
    auto result = g_thing->getId(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetPosition(ServerContext* context, const google::protobuf::UInt64Value* request, bot::bot_Position* response) {
    auto result = g_thing->getPosition(request->value());
    response->set_x(result.x);
    response->set_y(result.y);
    response->set_z(result.z);
    return Status::OK;
}

Status BotServiceImpl::GetParentContainer(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt64Value* response) {
    auto result = g_thing->getParentContainer(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsItem(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_thing->isItem(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsMonster(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_thing->isMonster(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsNpc(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_thing->isNpc(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsCreature(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_thing->isCreature(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsPlayer(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_thing->isPlayer(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsLocalPlayer(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_thing->isLocalPlayer(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsContainer(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_thing->isContainer(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsUsable(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_thing->isUsable(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::IsLyingCorpse(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::BoolValue* response) {
    auto result = g_thing->isLyingCorpse(request->value());
    response->set_value(result);
    return Status::OK;
}

// ================= Tile.h =================
Status BotServiceImpl::GetTopThing(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt64Value* response) {
    auto result = g_tile->getTopThing(request->value());
    response->set_value(result);
    return Status::OK;
}

Status BotServiceImpl::GetTopUseThing(ServerContext* context, const google::protobuf::UInt64Value* request, google::protobuf::UInt64Value* response) {
    auto result = g_tile->getTopUseThing(request->value());
    response->set_value(result);
    return Status::OK;
}


// End of Functions


void RunServer() {
    std::string server_address("0.0.0.0:50051");
    BotServiceImpl service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();
}



