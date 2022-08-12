/**
 * 작성자 : 윤정도
 * 설명 : DLL Entry Point
 */

#include "PrecompiledHeader.h"
#include "SenderFn.h"
#include "AttachtedProcess.h"

#include "Network/Winsock.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Winsock::Initialize();

        AttachedProcess::Get().ExecutePostWndProc(WM_KEYDOWN, 0x00000027, 0x014d0001);
        AttachedProcess::Get().ExecutePostWndProc(WM_KEYUP, 0x00000027, 0x014d0001);
        Sleep(100);

        for (int i = 0; i < 30; i++) {
            AttachedProcess::Get().ExecutePostWndProc(WM_KEYUP, 0x00000027, 0x414d0001);
            Sleep(100);
        }

        AttachedProcess::Get().ExecutePostWndProc(WM_KEYUP, 0x00000027, 0x414d0001);
        AttachedProcess::Get().ExecutePostWndProc(WM_KEYUP, 0x00000027, 0xc14d0001);
        Sleep(100);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        Winsock::Finalize();
        break;
    }
    return TRUE;
}

