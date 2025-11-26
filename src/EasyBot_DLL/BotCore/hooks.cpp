#include "hooks.h"
#include "CustomFunctions.h"
#include "pattern_scan.h"


bool has_weird(const std::string& s) {
    return std::any_of(s.begin(), s.end(), [](unsigned char c) { return !isprint(c); });
}

void __stdcall hooked_bindSingletonFunction(uintptr_t a1, uintptr_t a2, uintptr_t a3) {
    auto base_module = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
    CONTEXT ctx;
    RtlCaptureContext(&ctx);
    uintptr_t ebp = ctx.Ebp;
    uintptr_t tmp = 0;
    auto global = *reinterpret_cast<std::string*>(a1);
    auto field = *reinterpret_cast<std::string*>(a2);
    if (global[1] != '_') {
        //tmp = *reinterpret_cast<uintptr_t*>(ebp + 0x50);
        tmp = *reinterpret_cast<uintptr_t*>(ebp + 0xC);
        /*
        g_log << "[Class Member Function] class: "<<  global << " function: " << field << " function_address: " << std::hex << tmp - base_module << std::endl;
        g_log.flush();
        */
        ClassMemberFunctions[std::string(global) + "." + std::string(field)]  = tmp;
    } else {
        uintptr_t second_tmp = 0;
        tmp = *reinterpret_cast<uintptr_t*>(ebp + 0x10);
        second_tmp = *reinterpret_cast<uintptr_t*>(ebp + 0x14);
        /*
        g_log << "[Singleton Function] class: " << global << " function: " << field <<
            " function_address: " << std::hex << tmp- base_module << " second_param: " << std::hex << second_tmp << std::endl;
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
            uintptr_t addr_mode = ebp + EASY_OFFSET;
            uintptr_t addr_message = ebp + EASY_OFFSET + 0x04;
            auto ptr_to_mode = EASY_PTR reinterpret_cast<EASY_VAR>(addr_mode);
            auto ptr_to_message = *reinterpret_cast<EASY_VAR_MESSAGE>(addr_message);
            if (*ptr_to_mode == Otc::MessageStatus) {
                *ptr_to_mode = Otc::MessageMode::MessageFailure;
                auto message_address = reinterpret_cast<std::string*>(ptr_to_message);
                *message_address = "Welcome to EasyBot. Enjoy. Join our discord https://discord.com/invite/7MTnc2ueyM";
            }
            if (*ptr_to_mode == Otc::MessageLook)
            {
                auto message_address = reinterpret_cast<std::string*>(ptr_to_message);
                std::string tmp = std::to_string(itemId);
                *message_address = "ID: " + std::to_string(itemId) + "\n" + *reinterpret_cast<std::string*>(ptr_to_message);
            }
        }
        if (field == "onTalk") {
            auto args = reinterpret_cast<StackArgs*>(ebp + 0x10);
            g_custom->onTalk(
                *args->name,
                reinterpret_cast<uint16_t>(args->level),
                *args->mode,
                *args->text,
                *args->channelId,
                *args->pos
            );
        }
        if (field == "onOpenChannel") {
            auto channelId = *reinterpret_cast<uintptr_t**>(ebp + EASY_OFFSET);
            auto channelName = *reinterpret_cast<uintptr_t**>(ebp + EASY_OFFSET + 0x04);
            g_custom->onOpenChannel(*reinterpret_cast<uint16_t*>(channelId), *reinterpret_cast<std::string*>(channelName));
        }
        if (field == "onCloseChannel") {
            auto channelId = *reinterpret_cast<uintptr_t**>(ebp + EASY_OFFSET + 0x04);
            g_custom->onCloseChannel(*reinterpret_cast<uint16_t*>(channelId));
        }
    }
    original_callGlobalField(a1, a2);
}

#pragma optimize( "", on )

int hkMainLoop(int a1) {
    g_dispatcher->executeEvent();
    auto result = mainLoop_original(a1);
    return result;
}

typedef uint32_t(__thiscall* GetId)(
    uintptr_t RCX,
    void *RDX
    );

void __stdcall hkLook(const uintptr_t& thing, const bool isBattleList) {
    look_original(&thing, isBattleList);
    auto function = reinterpret_cast<GetId>(ClassMemberFunctions["Item.getId"]);
    void* pMysteryPtr = nullptr;
    itemId = function(thing, &pMysteryPtr);
}





