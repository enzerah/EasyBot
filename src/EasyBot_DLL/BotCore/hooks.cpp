#include "hooks.h"


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
        /*
        g_log << "[Class Member Function] class: "<<  msg << " function: " << msg2 << " function_address: " << std::hex << tmp - base_module << std::endl;
        g_log.flush();
        */
        ClassMemberFunctions[std::string(msg) + "." + std::string(msg2)]  = tmp;
    } else {
        uintptr_t second_tmp = 0;
        tmp = *reinterpret_cast<uintptr_t*>(ebp + 0x10);
        second_tmp = *reinterpret_cast<uintptr_t*>(ebp + 0x14);
        /*
        g_log << "[Singleton Function] class: " << msg << " function: " << msg2 <<
            " function_address: " << std::hex << tmp- base_module << " second_param: " << std::hex << second_tmp << std::endl;
        g_log.flush();
        */
        SingletonFunctions[std::string(msg) + "." + std::string(msg2)]  = {tmp, second_tmp};
    }
    original_bindSingletonFunction(a1,a2,a3);
}


int hkMainLoop(int a1) {
    g_dispatcher->executeEvent();
    auto result = mainLoop_original(a1);
    return result;
}





