#include "../../proto_functions_server.h"
#include "hooks.h"
#include "MinHook.h"
#include "BuildConfig.h"
#include "Creature.h"
#include "Game.h"
#include "pattern_scan.h"
#include "Thing.h"

DWORD WINAPI EasyBot(HMODULE hModule) {
    auto base_module = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
    MH_Initialize();
    uintptr_t bindSingletonFunction_func = FindPattern(bindSingletonFunction_x86_PATTERN, bindSingletonFunction_x86_MASK);
    uintptr_t callGlobalField_func = FindPattern(callGlobalField_PATTERN, callGlobalField_MASK);
    uintptr_t mainLoop_func = FindPattern(mainLoop_x86_PATTERN, mainLoop_x86_MASK);
    uintptr_t onDisappear_func = 0x00C14F10;
    MH_CreateHook(reinterpret_cast<LPVOID>(bindSingletonFunction_func), &hooked_bindSingletonFunction, reinterpret_cast<LPVOID*>(&original_bindSingletonFunction));
    MH_CreateHook(reinterpret_cast<LPVOID>(callGlobalField_func), &hooked_callGlobalField, reinterpret_cast<LPVOID*>(&original_callGlobalField));
    MH_CreateHook(reinterpret_cast<LPVOID>(mainLoop_func), &hooked_MainLoop, reinterpret_cast<LPVOID*>(&mainLoop_original));
    MH_CreateHook(reinterpret_cast<LPVOID>(onDisappear_func), &hooked_onDisappear, reinterpret_cast<LPVOID*>(&onDisappear_original));
    FILE *f;
    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Singleton " << std::hex <<bindSingletonFunction_func << std::endl;
    std::cout << "Call global " << std::hex <<callGlobalField_func << std::endl;
    std::cout << "Main Loop " << std::hex << mainLoop_func << std::endl;
    std::cout << "onDisappear_func " << std::hex << onDisappear_func << std::endl;
    MH_EnableHook(MH_ALL_HOOKS);
    while (!SingletonFunctions["g_game.look"].first)
    {
        Sleep(10);
    }
    MH_CreateHook(reinterpret_cast<LPVOID>(SingletonFunctions["g_game.look"].first), &hooked_Look, reinterpret_cast<LPVOID*>(&look_original));
    MH_EnableHook(reinterpret_cast<LPVOID>(SingletonFunctions["g_game.look"].first));
    if (bindSingletonFunction_func &&
        callGlobalField_func &&
        mainLoop_func) {
        MessageBoxA(
            NULL,
            "Bot is running... :) Enjoy",
            "EasyBot",
            MB_OK | MB_ICONINFORMATION
        );
    }
    typedef void(gameCall *TalkPrivate)(
    uintptr_t RCX,
    Otc::MessageMode RDX,
    const std::string& receiver,
    const std::string& message
    );
    auto function = reinterpret_cast<TalkPrivate>(SingletonFunctions["g_game.talkPrivate"].first);
    system("pause");
    g_dispatcher->scheduleEventEx([function]() {
        auto msgMode = Otc::MessageMode::MessagePrivateTo;
        const std::string& r = "Shopping";
        const std::string& m = "Siema";
        function(SingletonFunctions["g_game.talkPrivate"].second, msgMode, r, m);
    });
    system("pause");
    g_game->talkPrivate(Otc::MessageMode::MessagePrivateTo, "Shopping", "Siema");
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
