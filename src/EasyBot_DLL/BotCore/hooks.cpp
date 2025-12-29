#include "hooks.h"
#include "BuildConfig.h"
#include "Creature.h"
#include "CustomFunctions.h"
#include "Game.h"
#include "pattern_scan.h"
#include "Thing.h"
#include "Tile.h"

void __stdcall hooked_bindSingletonFunction(uintptr_t a1, uintptr_t a2, uintptr_t a3) {
    CONTEXT ctx;
    RtlCaptureContext(&ctx);
    uintptr_t ebp = ctx.Ebp;
    uintptr_t tmp = 0;
    auto global = *reinterpret_cast<std::string*>(a1);
    auto field = *reinterpret_cast<std::string*>(a2);
    if (global[1] != '_') {
        tmp = *reinterpret_cast<uintptr_t*>(ebp + classFunctionOffset);
        /*
        g_log << "[Class Member Function] class: "<<  global << " function: " << field << " function_address: " << std::hex << tmp << std::endl;
        g_log.flush();
        */
        ClassMemberFunctions[std::string(global) + "." + std::string(field)]  = tmp;
    } else {
        uintptr_t second_tmp = 0;
        tmp = *reinterpret_cast<uintptr_t*>(ebp + singletonFunctionOffset);
        second_tmp = *reinterpret_cast<uintptr_t*>(ebp + singletonFunctionOffset + 0x04);
        /*
        g_log << "[Singleton Function] class: " << global << " function: " << field <<
            " function_address: " << std::hex << tmp<< " second_param: " << std::hex << second_tmp << std::endl;
        g_log.flush();
        */
        SingletonFunctions[std::string(global) + "." + std::string(field)]  = {tmp, second_tmp};
    }
    original_bindSingletonFunction(a1,a2,a3);
}

void __stdcall hooked_callLuaField(uintptr_t* a1) {
    original_callLuaField(a1);
}

inline uint32_t itemId;

#pragma optimize( "", off )
void __stdcall hooked_callGlobalField(uintptr_t **a1, uintptr_t **a2) {
    CONTEXT ctx;
    RtlCaptureContext(&ctx);
    uintptr_t ebp = ctx.Ebp;
    auto global = *reinterpret_cast<std::string*>(a1);
    auto field = *reinterpret_cast<std::string*>(a2);
    if (global == "g_game") {
        if (field == "onTextMessage") {
            uintptr_t addr_mode = ebp + globalFieldOffset;
            uintptr_t addr_message = ebp + globalFieldOffset + 0x04;
            auto ptr_messageMode = g_custom->getModePtr(addr_mode);
            auto ptr_messageText = g_custom->getMessagePtr(addr_message);
            std::cout << "Ptr" << std::endl;
            std::cout << *ptr_messageMode << std::endl;
            if (*ptr_messageMode == Otc::MessageLook)
            {
                std::cout << "Szef" << std::endl;
                auto message_address = reinterpret_cast<std::string*>(ptr_messageText);
                std::cout << *message_address << std::endl;
                *message_address = "ID: " + std::to_string(itemId) + "\n" + *reinterpret_cast<std::string*>(ptr_messageText);
            }
        }
        if (field == "onTalk") {
            auto args = reinterpret_cast<StackArgs*>(ebp + globalFieldOffset);
            g_custom->onTalk(
                *args->name,
                reinterpret_cast<uint16_t>(args->level),
                *args->mode,
                *args->text,
                *args->channelId,
                *args->pos
            );
        }
    }
    original_callGlobalField(a1, a2);
}

#pragma optimize( "", on )

int hooked_MainLoop(int a1) {
    g_dispatcher->executeEvent();
    auto result = mainLoop_original(a1);
    return result;
}

typedef uint32_t(__thiscall* GetId)(
    uintptr_t RCX,
    void *RDX
    );


void __stdcall hooked_Look(const uintptr_t& thing, const bool isBattleList) {
    look_original(&thing, isBattleList);
    auto function = reinterpret_cast<GetId>(ClassMemberFunctions["Item.getId"]);
    void* pMysteryPtr = nullptr;
    itemId = function(thing, &pMysteryPtr);

}



#pragma optimize( "", off )
void __fastcall hooked_onDisappear(uintptr_t a1) {
    onDisappear_original(a1);
}
#pragma optimize( "", on )






