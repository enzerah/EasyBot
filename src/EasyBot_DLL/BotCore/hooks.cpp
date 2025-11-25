#include "hooks.h"

#include "CustomFunctions.h"


bool has_weird(const std::string& s) {
    return std::any_of(s.begin(), s.end(), [](unsigned char c) { return !isprint(c); });
}

void __stdcall hooked_bindSingletonFunction(uintptr_t a1, uintptr_t a2, uintptr_t a3) {
    auto base_module = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
    CONTEXT ctx;
    RtlCaptureContext(&ctx);
    uintptr_t ebp = ctx.Ebp;
    uintptr_t tmp = 0;
    char msg[512];
    char msg2[512];
    sprintf_s(msg, "%s", reinterpret_cast<const char*>(a1));
    sprintf_s(msg2, "%s", reinterpret_cast<const char*>(a2));
    if (has_weird(msg2)) {
        auto tmp = *reinterpret_cast<uintptr_t*>(a2);
        sprintf_s(msg2, "%s", reinterpret_cast<const char*>(tmp));
    }
    if (msg[1] != '_') {
        //tmp = *reinterpret_cast<uintptr_t*>(ebp + 0x50);
        tmp = *reinterpret_cast<uintptr_t*>(ebp + 0xC);
        g_log << "[Class Member Function] class: "<<  msg << " function: " << msg2 << " function_address: " << std::hex << tmp - base_module << std::endl;
        g_log.flush();
        ClassMemberFunctions[std::string(msg) + "." + std::string(msg2)]  = tmp;
    } else {
        uintptr_t second_tmp = 0;
        tmp = *reinterpret_cast<uintptr_t*>(ebp + 0x10);
        second_tmp = *reinterpret_cast<uintptr_t*>(ebp + 0x14);
        g_log << "[Singleton Function] class: " << msg << " function: " << msg2 <<
            " function_address: " << std::hex << tmp- base_module << " second_param: " << std::hex << second_tmp << std::endl;
        g_log.flush();
        SingletonFunctions[std::string(msg) + "." + std::string(msg2)]  = {tmp, second_tmp};
    }
    original_bindSingletonFunction(a1,a2,a3);
}

void __stdcall hooked_callLuaField(uintptr_t* a1) {
    original_callLuaField(a1);
}


#pragma optimize( "", off )
void __stdcall hooked_callGlobalField(uintptr_t **a1, uintptr_t **a2) {
    CONTEXT ctx;
    RtlCaptureContext(&ctx);
    uintptr_t ebp = ctx.Ebp;
    char msg[512];
    char msg2[512];
    sprintf_s(msg, "%s", reinterpret_cast<const char*>(a1));
    sprintf_s(msg2, "%s", reinterpret_cast<const char*>(a2));
    if (has_weird(msg2)) {
        auto tmp = *reinterpret_cast<uintptr_t*>(a2);
        sprintf_s(msg2, "%s", reinterpret_cast<const char*>(tmp));
    }
    if (strcmp(msg, "g_game") == 0) {
        if (strcmp(msg2, "onTextMessage") == 0) {
            uintptr_t addr_mode = ebp + 0x10;
            uintptr_t addr_message = ebp + 0x14;
            auto ptr_to_mode = *reinterpret_cast<uintptr_t**>(addr_mode);
            auto ptr_to_message = *reinterpret_cast<uintptr_t*>(addr_message);
            if (*ptr_to_mode == 28U) {
                auto message = *reinterpret_cast<std::string*>(ptr_to_message);
                auto message_address = reinterpret_cast<std::string*>(ptr_to_message);
                *message_address = "Welcome to EasyBot. Enjoy";
            }
            if (*ptr_to_mode == Otc::MessageSay) {
                auto message = *reinterpret_cast<std::string*>(ptr_to_message);
                auto message_address = reinterpret_cast<std::string*>(ptr_to_message);
                std::cout << message << std::endl;
            }
        }
        if (strcmp(msg2, "onTalk") == 0) {
            auto args = reinterpret_cast<StackArgs*>(ebp + 0x10);
            g_custom->onTalk(
                *args->name,
                (uint16_t)args->level,
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

int hkMainLoop(int a1) {
    g_dispatcher->executeEvent();
    auto result = mainLoop_original(a1);
    return result;
}



void __stdcall hooked_bindSingletonFunctionAltaron(uintptr_t a1, uintptr_t a2, uintptr_t a3) {
    CONTEXT ctx;
    RtlCaptureContext(&ctx);
    uintptr_t ebp = ctx.Ebp;
    auto result = original_bindSingletonFunctionAltaron(a1,a2,a3);
    char msg[512];
    char msg2[512];
    sprintf_s(msg, "%s", reinterpret_cast<const char*>(a1));
    sprintf_s(msg2, "%s", reinterpret_cast<const char*>(a2));
    if (has_weird(msg)) {
        auto tmp = *reinterpret_cast<uintptr_t*>(a1);
        sprintf_s(msg, "%s", reinterpret_cast<const char*>(tmp));
    }
    while (has_weird(msg2)) {
        auto tmp = *reinterpret_cast<uintptr_t*>(a2);
        sprintf_s(msg2, "%s", reinterpret_cast<const char*>(tmp));
    }
    if (msg[1] == '_') {
        uintptr_t second_tmp = 0;
        uintptr_t tmp = *reinterpret_cast<uintptr_t*>(ebp + 0x10);
        second_tmp = *reinterpret_cast<uintptr_t*>(ebp + 0x18);
        g_log << "[Singleton Function] class: " << msg << " function: " << msg2 <<
            " function_address: " << std::hex << tmp << " second_param: " << std::hex << second_tmp << std::endl;
        g_log.flush();
        SingletonFunctions[std::string(msg) + "." + std::string(msg2)]  = {tmp, second_tmp};
    }
}

void __stdcall hooked_bindClassFunction_Altaron(uintptr_t a1, uintptr_t a2, uintptr_t a3) {
    CONTEXT ctx;
    RtlCaptureContext(&ctx);
    uintptr_t ebp = ctx.Ebp;
    auto result = original_bindClassFunction_Altaron(a1,a2,a3);
    char msg[512];
    char msg2[512];
    sprintf_s(msg, "%s", reinterpret_cast<const char*>(a1));
    sprintf_s(msg2, "%s", reinterpret_cast<const char*>(a2));
    while (has_weird(msg)) {
        auto tmp = *reinterpret_cast<uintptr_t*>(a1);
        sprintf_s(msg, "%s", reinterpret_cast<const char*>(tmp));
    }
    while (has_weird(msg2)) {
        auto tmp = *reinterpret_cast<uintptr_t*>(a2);
        sprintf_s(msg2, "%s", reinterpret_cast<const char*>(tmp));
    }
    uintptr_t tmp = *reinterpret_cast<uintptr_t*>(ebp + 0xC);
    g_log << "[Class Member Function] class: "<<  msg << " function: " << msg2 << " function_address: " << std::hex << tmp << std::endl;
    g_log.flush();
    ClassMemberFunctions[std::string(msg) + "." + std::string(msg2)]  = tmp;
}


int __fastcall hkMainLoopAltaron() {
    g_dispatcher->executeEvent();
    auto result = mainLoop_originalAltaron();
    return result;
}





