//
// Created by blazz on 30.09.2025.
//
#ifndef HOOKS_H
#define HOOKS_H
#include <algorithm>
#include <cstdint>
#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include "EventDispatcher.h"
#include "MinHook.h"


//static std::ofstream g_log("GameAddress.txt",  std::ios::trunc);

inline std::map<std::string, std::pair<uintptr_t, uintptr_t>> SingletonFunctions;
inline std::map<std::string, uintptr_t> ClassMemberFunctions;

typedef void(__stdcall* bindSingletonFunction_t)(uintptr_t, uintptr_t, uintptr_t);
inline bindSingletonFunction_t original_bindSingletonFunction = nullptr;
void __stdcall hooked_bindSingletonFunction(uintptr_t, uintptr_t, uintptr_t);

typedef void(__stdcall* callGlobalField_t)(uintptr_t**, uintptr_t**);
inline callGlobalField_t original_callGlobalField = nullptr;
void __stdcall hooked_callGlobalField(uintptr_t**, uintptr_t**);

typedef void(__stdcall* callLuaField_t)(uintptr_t*);
inline callLuaField_t original_callLuaField = nullptr;
void __stdcall hooked_callLuaField(uintptr_t*);

typedef int(__cdecl* mainLoop)(int a1);
inline mainLoop mainLoop_original = nullptr;
int __cdecl hkMainLoop(int a1);

typedef void(__stdcall* look_t)(const uintptr_t *RDX,const bool isBattleList);
inline look_t look_original = nullptr;
void __stdcall hkLook(const uintptr_t& thing, const bool isBattleList);


// Definicja oryginału jako __thiscall
typedef void* (__thiscall* onCreatureDisappear)(void* pList, void* pWhere, void** pData);
inline onCreatureDisappear onCreatureDisappear_original = nullptr;

// Hook zadeklarowany jako __stdcall - to pozwoli nam kontrolować rejestry ręcznie
void* __stdcall hkOnCreatureDisappear(void* pWhere, void** pData);




#endif //HOOKS_H
