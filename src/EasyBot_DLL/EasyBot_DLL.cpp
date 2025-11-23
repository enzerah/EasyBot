#include "../../proto_functions_server.h"
#include "hooks.h"
#include "MinHook.h"
#include "pattern_scan.h"

DWORD WINAPI EasyBot(HMODULE hModule) {
    uintptr_t base_module = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
    /*
    FILE *f;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);
    */
    MH_Initialize();
    uintptr_t first_func = FindPattern(bindSingletonFunction_x86_PATTERN, bindSingletonFunction_x86_MASK);
    uintptr_t main_loop = FindPattern(realera_x86_PATTERN, realera_x86_MASK);
    MH_CreateHook(reinterpret_cast<LPVOID>(first_func), &hooked_bindSingletonFunction, reinterpret_cast<LPVOID*>(&original_bindSingletonFunction));
    MH_CreateHook(reinterpret_cast<LPVOID>(main_loop), &hkMainLoop, reinterpret_cast<LPVOID*>(&mainLoop_original));
    MH_EnableHook(MH_ALL_HOOKS);
    if (first_func && main_loop) {
        MessageBoxA(
            NULL,
            "Bot is running... :) Enjoy",
            "EasyBot",
            MB_OK | MB_ICONINFORMATION
        );
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
