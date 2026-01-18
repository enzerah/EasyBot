#include "hooks.h"
#include "BuildConfig.h"
#include "Creature.h"
#include "CustomFunctions.h"
#include "pattern_scan.h"

void __stdcall hooked_bindSingletonFunction(uintptr_t a1, uintptr_t a2, uintptr_t a3) {
    CONTEXT ctx;
    RtlCaptureContext(&ctx);
    uintptr_t ebp = ctx.Ebp;
    uintptr_t tmp = 0;
    auto global = *reinterpret_cast<std::string*>(a1);
    auto field = *reinterpret_cast<std::string*>(a2);
    //std::cout << global << "." << field << std::endl;
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
            uintptr_t onTextMessage_address = ebp + onTextMessageOffset;
            auto ptr_messageText = g_custom->getMessagePtr(onTextMessage_address);
            auto message_address = reinterpret_cast<std::string*>(ptr_messageText);
            if (message_address->find("You see") != std::string::npos)
            {
                *message_address = "ID: " + std::to_string(itemId) + "\n" + *reinterpret_cast<std::string*>(ptr_messageText);
            }
        } else if (field == "onTalk") {
            auto args = reinterpret_cast<StackArgs*>(ebp + onTalkOffset);
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
    auto result = original_mainLoop(a1);
    return result;
}

typedef uint32_t(gameCall* GetId)(
    uintptr_t RCX,
    void *RDX
    );


void __stdcall hooked_Look(const uintptr_t& thing, const bool isBattleList) {
    look_original(&thing, isBattleList);
    auto function = reinterpret_cast<GetId>(ClassMemberFunctions["Item.getId"]);
    void* pMysteryPtr = nullptr;
    itemId = function(thing, &pMysteryPtr);

}

