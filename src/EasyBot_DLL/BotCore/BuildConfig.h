#ifndef BUILDCONFIG_H
#define BUILDCONFIG_H
#include <Windows.h>

// Patterns
static const BYTE* bindSingletonFunction_x86_PATTERN = reinterpret_cast<const BYTE*>("\x55\x8b\xec\x8b\x45\x00\x83\x78\x00\x00\x00\x00\x8b\x00\x50\x68\x00\x00\x00\x00\xff\x35\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x83\xc4");
static LPCSTR bindSingletonFunction_x86_MASK = "xxxxx?xx????xxxx????xx????x????xx";

static const BYTE* mainLoop_x86_PATTERN = reinterpret_cast<const BYTE*>("\x8b\x54\x24\x00\x8b\x00\x24\x00\x53\x56");
static LPCSTR mainLoop_x86_MASK = "xxx?x?x?xx";


// Enum for building
enum {
    Miracle = 1,
    Realera,
    Dbwots,
    Outcast,
    Thirus,
    Exordion,
    Yurevo
};
#define BUILD_MIRACLE 1
#define BUILD_REALERA 2
#define BUILD_DBWOTS  3
#define BUILD_OUTCAST 4
#define BUILD_THIRUS  5
#define BUILD_EXORDION  6
#define BUILD_YUREVO 7


#define BuildOption BUILD_DBWOTS
#if BuildOption == BUILD_MIRACLE
    static const BYTE* callGlobalField_PATTERN = reinterpret_cast<const BYTE*>("\x55\x8b\xec\x8b\x45\x00\x83\x78\x00\x00\x00\x00\x8b\x00\x50\x68\x00\x00\x00\x00\xff\x35\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x6a");
    static LPCSTR callGlobalField_MASK = "xxxxx?xx????xxxx????xx????x????x";
    #define classFunctionOffset 0x50
    #define singletonFunctionOffset 0x10
    #define globalFieldOffset 0x10
#elif BuildOption == BUILD_REALERA
    static const BYTE* callGlobalField_PATTERN = reinterpret_cast<const BYTE*>("\x55\x8b\xec\x8b\x45\x00\x83\x78\x00\x00\x00\x00\x8b\x00\x50\x68\x00\x00\x00\x00\xff\x35\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x6a");
    static LPCSTR callGlobalField_MASK = "xxxxx?xx????xxxx????xx????x????x";
    #define classFunctionOffset 0xC
    #define singletonFunctionOffset 0x10
    #define globalFieldOffset 0x10
#elif BuildOption == BUILD_DBWOTS
    static const BYTE* callGlobalField_PATTERN = reinterpret_cast<const BYTE*>("\x55\x8b\xec\x8b\x45\x00\x83\x78\x00\x00\x76\x00\x8b\x00\x56\x50");
    static LPCSTR callGlobalField_MASK = "xxxxx?xx??x?xxxx";
    #define classFunctionOffset 0xC
    #define singletonFunctionOffset 0x10
    #define globalFieldOffset 0x8
#elif BuildOption == BUILD_OUTCAST
    static const BYTE* callGlobalField_PATTERN = reinterpret_cast<const BYTE*>("\x55\x8b\xec\x8b\x45\x00\x83\x78\x00\x00\x72\x00\x8b\x00\x50\x68\x00\x00\x00\x00\xff\x35\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x6a");
    static LPCSTR callGlobalField_MASK = "xxxxx?xx??x?xxxx????xx????x????x";
    #define classFunctionOffset 0xC
    #define singletonFunctionOffset 0x10
    #define globalFieldOffset 0x10
#elif BuildOption == BUILD_THIRUS
    static const BYTE* callGlobalField_PATTERN = reinterpret_cast<const BYTE*>("\x55\x8b\xec\x8b\x45\x00\x83\x78\x00\x00\x72\x00\x8b\x00\x50\x68\x00\x00\x00\x00\xff\x35\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x6a");
    static LPCSTR callGlobalField_MASK = "xxxxx?xx??x?xxxx????xx????x????x";
    #define classFunctionOffset 0xC
    #define singletonFunctionOffset 0x10
    #define globalFieldOffset 0x10
#elif BuildOption == BUILD_EXORDION
    static const BYTE* callGlobalField_PATTERN = reinterpret_cast<const BYTE*>("\x55\x8b\xec\x8b\x45\x00\x83\x78\x00\x00\x00\x00\x8b\x00\x50\x68\x00\x00\x00\x00\xff\x35\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x6a");
    static LPCSTR callGlobalField_MASK = "xxxxx?xx????xxxx????xx????x????x";
    #define classFunctionOffset 0x58
    #define singletonFunctionOffset 0x10
    #define globalFieldOffset 0x10
#elif BuildOption == BUILD_YUREVO
    static const BYTE* callGlobalField_PATTERN = reinterpret_cast<const BYTE*>("\x55\x8b\xec\x8b\x45\x00\x83\x78\x00\x00\x00\x00\x8b\x00\x50\x68\x00\x00\x00\x00\xff\x35\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x6a");
    static LPCSTR callGlobalField_MASK = "xxxxx?xx????xxxx????xx????x????x";
    #define classFunctionOffset 0x50
    #define singletonFunctionOffset 0x10
    #define globalFieldOffset 0x10
#endif






#endif //BUILDCONFIG_H
