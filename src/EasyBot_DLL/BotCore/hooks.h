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


static std::ofstream g_log("GameAddress.txt",  std::ios::trunc);

inline std::map<std::string, std::pair<uintptr_t, uintptr_t>> SingletonFunctions;
inline std::map<std::string, uintptr_t> ClassMemberFunctions;

bool has_weird(const std::string& s);
typedef void(__stdcall* bindSingletonFunction_t)(uintptr_t, uintptr_t, uintptr_t);
inline bindSingletonFunction_t original_bindSingletonFunction = nullptr;
void __stdcall hooked_bindSingletonFunction(uintptr_t, uintptr_t, uintptr_t);

typedef void(__stdcall* callGlobalField_t)(uintptr_t**, uintptr_t**);
inline callGlobalField_t original_callGlobalField = nullptr;
void __stdcall hooked_callGlobalField(uintptr_t**, uintptr_t**);

typedef void(__stdcall* callLuaField_t)(uintptr_t*);
inline callLuaField_t original_callLuaField = nullptr;
void __stdcall hooked_callLuaField(uintptr_t*);


typedef int (__cdecl* mainLoop)(int a1);
inline mainLoop mainLoop_original = nullptr;
int __cdecl hkMainLoop(int a1);

typedef DWORD(__stdcall* bindSingletonFunction_Altaron)(uintptr_t, uintptr_t, uintptr_t);
inline bindSingletonFunction_Altaron original_bindSingletonFunctionAltaron = nullptr;
void __stdcall hooked_bindSingletonFunctionAltaron(uintptr_t, uintptr_t, uintptr_t);

typedef DWORD(__stdcall* bindClassFunction_Altaron)(uintptr_t, uintptr_t, uintptr_t);
inline bindClassFunction_Altaron original_bindClassFunction_Altaron = nullptr;
void __stdcall hooked_bindClassFunction_Altaron(uintptr_t, uintptr_t, uintptr_t);

typedef int (__fastcall* mainLoopAltaron)();
inline mainLoopAltaron mainLoop_originalAltaron = nullptr;
int __fastcall hkMainLoopAltaron();




#endif //HOOKS_H
