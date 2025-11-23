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

bool has_weird(const std::string& s);
typedef void(__stdcall* bindSingletonFunction_t)(uintptr_t, uintptr_t, uintptr_t);
inline bindSingletonFunction_t original_bindSingletonFunction = nullptr;
void __stdcall hooked_bindSingletonFunction(uintptr_t, uintptr_t, uintptr_t);


typedef int (__cdecl* mainLoop)(int a1);
inline mainLoop mainLoop_original = nullptr;
int __cdecl hkMainLoop(int a1);

#endif //HOOKS_H
