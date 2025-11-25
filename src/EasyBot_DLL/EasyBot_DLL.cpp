#include "../../proto_functions_server.h"


#include "hooks.h"
#include "Item.h"
#include "MinHook.h"
#include "Container.h"
#include "CustomFunctions.h"
#include "pattern_scan.h"

DWORD WINAPI EasyBot(HMODULE hModule) {
    auto base_module = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
    FILE *f;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);
    MH_Initialize();
    uintptr_t bindSingletonFunction_func = FindPattern(bindSingletonFunction_x86_PATTERN, bindSingletonFunction_x86_MASK);
    uintptr_t callGlobalField_func = FindPattern(callGlobalField_PATTERN, callGlobalField_MASK);
    //uintptr_t callLuaField_func = FindPattern(callLuaField_PATTERN, callLuaField_MASK);
    uintptr_t callLuaField_func = base_module + 0x1BCC00;
    uintptr_t main_loop = FindPattern(realera_x86_PATTERN, realera_x86_MASK);
    MH_CreateHook(reinterpret_cast<LPVOID>(bindSingletonFunction_func), &hooked_bindSingletonFunction, reinterpret_cast<LPVOID*>(&original_bindSingletonFunction));
    MH_CreateHook(reinterpret_cast<LPVOID>(callGlobalField_func), &hooked_callGlobalField, reinterpret_cast<LPVOID*>(&original_callGlobalField));
    MH_CreateHook(reinterpret_cast<LPVOID>(callLuaField_func), &hooked_callLuaField, reinterpret_cast<LPVOID*>(&original_callLuaField));
    MH_CreateHook(reinterpret_cast<LPVOID>(main_loop), &hkMainLoop, reinterpret_cast<LPVOID*>(&mainLoop_original));
    /*
    uintptr_t first_func = base_module + 0x70900;
    uintptr_t second_func = base_module + 0x6FF20;
    uintptr_t main_loop = base_module + 0x5F800;
    MH_CreateHook(reinterpret_cast<LPVOID>(first_func), &hooked_bindSingletonFunctionAltaron, reinterpret_cast<LPVOID*>(&original_bindSingletonFunctionAltaron));
    MH_CreateHook(reinterpret_cast<LPVOID>(second_func), &hooked_bindClassFunction_Altaron, reinterpret_cast<LPVOID*>(&original_bindClassFunction_Altaron));
    MH_CreateHook(reinterpret_cast<LPVOID>(main_loop), &hkMainLoopAltaron, reinterpret_cast<LPVOID*>(&mainLoop_originalAltaron));
    */
    MH_EnableHook(MH_ALL_HOOKS);
    if (bindSingletonFunction_func &&
        callGlobalField_func &&
        callLuaField_func &&
        main_loop) {
        MessageBoxA(
            NULL,
            "Bot is running... :) Enjoy",
            "EasyBot",
            MB_OK | MB_ICONINFORMATION
        );
    }
    system("pause");
    auto messages = g_custom->getMessages(5);
    for (auto message : messages) {
        std::cout << message.name << " " << message.text << std::endl;
    }
    system("pause");
    messages = g_custom->getMessages(1);
    for (auto message : messages) {
        std::cout << message.name << " " << message.text << std::endl;
    }
    RunServer();
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)EasyBot,  NULL, 0, NULL);
            break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
