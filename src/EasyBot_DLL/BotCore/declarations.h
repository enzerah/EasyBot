#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include <list>
#include <memory>
#include <vector>
#include "BuildConfig.h"
// core
class Map;
class Game;
class MapView;
class LightView;
class Tile;
class Thing;
class Item;
class Container;
class Creature;
class Monster;
class Npc;
class Player;
class LocalPlayer;
class Effect;
class Missile;
class AnimatedText;
class StaticText;
class Animator;
class ThingType;
class ItemType;
class TileBlock;
class AttachedEffect;
class AttachableObject;


template<typename T>
struct SmartPtr {
    uintptr_t address;
    uintptr_t controlBlock;

    SmartPtr() : address(0), controlBlock(0) {}
    SmartPtr(uintptr_t addr) : address(addr), controlBlock(0) {}

    template<typename U>
    SmartPtr(const SmartPtr<U>& other) : address(other.address), controlBlock(other.controlBlock) {}

    operator uintptr_t() const { return address; }
    bool operator!() const { return address == 0; }
    bool operator==(const SmartPtr& other) const { return address == other.address; }
    bool operator!=(const SmartPtr& other) const { return address != other.address; }
};

using MapViewPtr = SmartPtr<MapView>;
using LightViewPtr = uintptr_t; // unique_ptr is 8 bytes
using TilePtr = SmartPtr<Tile>;
using ThingPtr = SmartPtr<Thing>;
using ItemPtr = SmartPtr<Item>;
using ContainerPtr = SmartPtr<Container>;
#if BuildOption == BUILD_EXORDION
    using CreaturePtr = SmartPtr<Creature>;
#else
    using CreaturePtr = uintptr_t;
#endif
using MonsterPtr = SmartPtr<Monster>;
using NpcPtr = SmartPtr<Npc>;
using PlayerPtr = SmartPtr<Player>;
using LocalPlayerPtr = SmartPtr<LocalPlayer>;
using EffectPtr = SmartPtr<Effect>;
using MissilePtr = SmartPtr<Missile>;
using AnimatedTextPtr = SmartPtr<AnimatedText>;
using StaticTextPtr = SmartPtr<StaticText>;
using ThingTypePtr = SmartPtr<ThingType>;
using ItemTypePtr = SmartPtr<ItemType>;
using AttachedEffectPtr = SmartPtr<AttachedEffect>;
using AttachableObjectPtr = SmartPtr<AttachableObject>;


using ThingList = std::vector<ThingPtr>;
using ThingTypeList = std::vector<ThingTypePtr>;
using ItemTypeList = std::vector<ItemTypePtr>;

using TileList = std::list<TilePtr>;
using ItemVector = std::vector<ItemPtr>;



#endif //DECLARATIONS_H
