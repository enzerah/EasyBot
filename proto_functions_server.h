#ifndef PROTO_FUNCTIONS_H
#define PROTO_FUNCTIONS_H
#include <grpcpp/grpcpp.h>
#include <grpcpp/server_builder.h>
#include "bot.pb.h"
#include "bot.grpc.pb.h"
#include "Thing.h"
#include "Game.h"
#include "LocalPlayer.h"
#include "bot.grpc.pb.h"
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using google::protobuf::Empty;
using bot::BotService;

class BotServiceImpl : public BotService::Service {
    // Functions:
    // Game.h
    Status Walk(grpc::ServerContext *context,const bot::bot_WalkRequest *request,google::protobuf::Empty *response) override;
    Status Turn(grpc::ServerContext *context, const bot::bot_TurnRequest *request, google::protobuf::Empty *response) override;
    Status Move(grpc::ServerContext *context, const bot::bot_MoveRequest *request, google::protobuf::Empty *response) override;
    Status Use(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::Empty *response) override;
    Status UseWith(grpc::ServerContext *context, const bot::bot_UseWithRequest *request, google::protobuf::Empty *response) override;
    Status UseInventoryItem(grpc::ServerContext *context, const google::protobuf::Int32Value *request, google::protobuf::Empty *response) override;
    Status UseInventoryItemWith(grpc::ServerContext *context, const bot::bot_UseInventoryItemWithRequest *request, google::protobuf::Empty *response) override;
    Status FindItemInContainers(grpc::ServerContext *context, const bot::bot_FindItemInContainersRequest *request, google::protobuf::UInt64Value *response) override;
    Status Open(grpc::ServerContext *context, const bot::bot_OpenRequest *request, google::protobuf::Int32Value *response) override;
    Status OpenParent(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::Empty *response) override;
    Status Close(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::Empty *response) override;
    Status RefreshContainer(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::Empty *response) override;
    Status Attack(grpc::ServerContext *context, const bot::bot_AttackRequest *request, google::protobuf::Empty *response) override;
    Status GetLocalPlayer(grpc::ServerContext *context, const google::protobuf::Empty *request, google::protobuf::UInt64Value *response) override;
    Status EquipItem(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::Empty *response) override;
    Status CancelAttack(grpc::ServerContext *context, const google::protobuf::Empty *request, google::protobuf::Empty *response) override;
    Status TalkChannel(grpc::ServerContext *context, const bot::bot_TalkChannelRequest *request, google::protobuf::Empty *response) override;
    Status TalkPrivate(grpc::ServerContext *context, const bot::bot_TalkPrivateRequest *request, google::protobuf::Empty *response) override;
    Status CanPerformGameAction(grpc::ServerContext *context, const google::protobuf::Empty *request, google::protobuf::BoolValue *response) override;
    Status IsAttacking(grpc::ServerContext *context, const google::protobuf::Empty *request, google::protobuf::BoolValue *response) override;
    Status GetContainer(grpc::ServerContext *context, const google::protobuf::Int32Value *request, google::protobuf::UInt64Value *response) override;
    Status GetContainers(grpc::ServerContext *context, const google::protobuf::Empty *request, bot::bot_Uint64List *response) override;
    Status GetAttackingCreature(grpc::ServerContext *context, const google::protobuf::Empty *request, google::protobuf::UInt64Value *response) override;

    // Thing.h
    Status GetIdThing(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::UInt32Value *response) override;
    Status GetPosition(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, bot::bot_Position *response) override;
    Status GetParentContainer(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::UInt64Value *response) override;
    Status IsMonster(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;
    Status IsNpc(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;
    Status IsPlayer(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;
    Status IsLocalPlayer(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;
    Status IsContainer(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;
    Status IsUsable(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;
    Status IsLyingCorpse(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;

    // Tile.h
    Status GetTopThing(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::UInt64Value *response) override;
    Status GetTopUseThing(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::UInt64Value *response) override;

    // Map.h
    Status GetTile(grpc::ServerContext *context, const bot::bot_Position *request, google::protobuf::UInt64Value *response) override;
    Status GetSpectators(grpc::ServerContext *context, const bot::bot_GetSpectatorsRequest *request, bot::bot_Uint64List *response) override;
    Status FindPath(grpc::ServerContext *context, const bot::bot_FindPathRequest *request, bot::bot_DirectionList *response) override;
    Status IsSightClear(grpc::ServerContext* context, const bot::bot_IsSightClearRequest* request, google::protobuf::BoolValue* response) override;

    // LocalPlayer.h
    Status GetStates(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::UInt32Value *response) override;
    Status GetHealth(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::DoubleValue *response) override;
    Status GetMaxHealth(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::DoubleValue *response) override;
    Status GetFreeCapacity(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::DoubleValue *response) override;
    Status GetLevel(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::UInt32Value *response) override;
    Status GetMana(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::DoubleValue *response) override;
    Status GetMaxMana(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::DoubleValue *response) override;
    Status GetSoul(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::UInt32Value *response) override;
    Status GetStamina(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::UInt32Value *response) override;
    Status HasSight(grpc::ServerContext *context, const bot::bot_HasSightRequest *request, google::protobuf::BoolValue *response) override;
    Status IsAutoWalking(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;
    Status StopAutoWalk(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::Empty *response) override;
    Status AutoWalk(grpc::ServerContext *context, const bot::bot_AutoWalkRequest *request, google::protobuf::BoolValue *response) override;

    // Item.h
    Status GetDescription(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::StringValue *response) override;
    Status GetCount(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::Int32Value *response) override;
    Status GetId(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::UInt32Value *response) override;
    Status GetText(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::StringValue *response) override;

    // Creature.h
    Status GetName(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::StringValue *response) override;
    Status GetHealthPercent(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::UInt32Value *response) override;
    Status GetDirection(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, bot::bot_DirectionRequest *response) override;
    Status IsDead(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;
    Status CanBeSeen(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;
    Status IsCovered(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;
    Status CanShoot(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;

    // Container.h
    Status GetItems(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, bot::bot_Uint64List *response) override;
    Status GetItemsCount(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::Int32Value *response) override;
    Status GetSlotPosition(grpc::ServerContext *context, const bot::bot_GetSlotPositionRequest *request, bot::bot_Position *response) override;
    Status GetContainerName(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::StringValue *response) override;
    Status GetItem(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::UInt64Value *response) override;
    Status HasParent(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::BoolValue *response) override;
    Status GetFirstIndex(grpc::ServerContext *context, const google::protobuf::UInt64Value *request, google::protobuf::Int32Value *response) override;



};

void RunServer();

#endif //PROTO_FUNCTIONS_H
