#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include <list>
#include <memory>
#include <vector>

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
    T* address;

    SmartPtr() : address(nullptr) {}
    SmartPtr(std::nullptr_t) : address(nullptr) {}
    explicit SmartPtr(uintptr_t addr) : address(reinterpret_cast<T*>(addr)) {}

    template<typename U>
    SmartPtr(const SmartPtr<U>& other) : address(reinterpret_cast<T*>(other.address)) {}

    SmartPtr& operator=(std::nullptr_t) { address = nullptr; return *this; }

    operator uintptr_t() const { return reinterpret_cast<uintptr_t>(address); }
    explicit operator bool() const { return address != nullptr; }
    bool operator!() const { return address == nullptr; }
    bool operator==(const SmartPtr& other) const { return address == other.address; }
    bool operator!=(const SmartPtr& other) const { return address != other.address; }
};

using MapViewPtr = SmartPtr<MapView>;
using LightViewPtr = uintptr_t; // unique_ptr is 8 bytes
using TilePtr = SmartPtr<Tile>;
using ThingPtr = SmartPtr<Thing>;
using ItemPtr = SmartPtr<Item>;
using ContainerPtr = SmartPtr<Container>;
using CreaturePtr = SmartPtr<Creature>;
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
