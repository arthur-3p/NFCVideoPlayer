// dllmain.cpp : Defines the entry point for the DLL application.

#define LLA_TOMCRYPT_EXPORT __declspec(dllimport)

#include "stdafx.h"
#include <logicalaccess/readerproviders/readerprovider.hpp>
#include <logicalaccess/plugins/crypto/tomcrypt.h>

#include <logicalaccess/plugins/llacommon/settings.hpp>
#include <logicalaccess/plugins/llacommon/logs.hpp>

__declspec(dllimport) extern HMODULE __hLibLogicalAccessModule;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID /*lpReserved*/)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        __hLibLogicalAccessModule = hModule;
        DisableThreadLibraryCalls(hModule);

        register_cipher(&des_desc);
        register_cipher(&des3_desc);

        logicalaccess::Settings::getInstance()->Initialize();
        LOG(logicalaccess::LogLevel::INFOS) << "Process attached ! HMODULE: " << hModule;
        break;
    case DLL_PROCESS_DETACH:
        LOG(logicalaccess::LogLevel::INFOS) << "Process detached !";
        logicalaccess::Settings::getInstance()->Uninitialize();

        unregister_cipher(&des3_desc);
        unregister_cipher(&des_desc);
        break;
    case DLL_THREAD_ATTACH: break;
    case DLL_THREAD_DETACH: break;
    default:;
    }
    return TRUE;
}