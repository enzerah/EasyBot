#include "../../proto_functions_server.h"
#include "pattern_scan.h"
#include "MinHook.h"
#include "hooks.h"
#include "Game.h"
#include "LocalPlayer.h"
#include "Thing.h"
#include "Container.h"


DWORD WINAPI EasyBot(HMODULE hModule) {
    MH_Initialize();
    uintptr_t bindSingletonFunction_func = FindPattern(bindSingletonFunction_x86_PATTERN, bindSingletonFunction_x86_MASK);
    uintptr_t callGlobalField_func = FindPattern(callGlobalField_PATTERN, callGlobalField_MASK);
    uintptr_t mainLoop_func = FindPattern(mainLoop_x86_PATTERN, mainLoop_x86_MASK);
    MH_CreateHook(reinterpret_cast<LPVOID>(bindSingletonFunction_func), &hooked_bindSingletonFunction, reinterpret_cast<LPVOID*>(&original_bindSingletonFunction));
    MH_CreateHook(reinterpret_cast<LPVOID>(callGlobalField_func), &hooked_callGlobalField, reinterpret_cast<LPVOID*>(&original_callGlobalField));
    MH_CreateHook(reinterpret_cast<LPVOID>(mainLoop_func), &hooked_MainLoop, reinterpret_cast<LPVOID*>(&original_mainLoop));
    /*
    FILE *f;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Singleton " << std::hex <<bindSingletonFunction_func << std::endl;
    std::cout << "Call global " << std::hex <<callGlobalField_func << std::endl;
    std::cout << "Main Loop " << std::hex << mainLoop_func << std::endl;
     */
    MH_EnableHook(MH_ALL_HOOKS);
    while (!SingletonFunctions["g_game.look"].first)
    {
        Sleep(10);
    }
    MH_CreateHook(reinterpret_cast<LPVOID>(SingletonFunctions["g_game.look"].first), &hooked_Look, reinterpret_cast<LPVOID*>(&look_original));
    MH_EnableHook(reinterpret_cast<LPVOID>(SingletonFunctions["g_game.look"].first));
    RunServer();
    return 0;
}


struct BotLoader {
    BotLoader() {
        CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(EasyBot), NULL, 0, NULL);
    }
};
static BotLoader loader;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}