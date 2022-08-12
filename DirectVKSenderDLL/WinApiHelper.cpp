/**
 * 작성자 : 윤정도
 * 설명 : WinAPI를 쉽게 다룰 수 있도록 도와주는 함수
 */

#include "PrecompiledHeader.h"
#include "WinApiHelper.h"

VKString WinApiHelper::GetCurrentModuleFileName()
{
	TCHAR buf[MAX_PATH + 1];

	if (GetModuleFileName(nullptr, buf, MAX_PATH) != FALSE)
		return buf;

	return _T("");
}

// 프로세스의 모듈 목록 가져오는 법
// https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes
bool WinApiHelper::GetLoadedModule(const DWORD dwProcessId, const VKString& moduleName, PMODULEENTRY32 moduleEntry)
{
    bool bHasModule = false;
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    // Take a snapshot of all modules in the specified process.
    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
        return false;

    // Set the size of the structure before using it.
    me32.dwSize = sizeof(MODULEENTRY32);

    // Retrieve information about the first module,
    // and exit if unsuccessful
    if (!Module32First(hModuleSnap, &me32)) {
        CloseHandle(hModuleSnap);           // clean the snapshot object
        return false;
    }

    // Now walk the module list of the process,
    // and display information about each module
    do
    {
        // _tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
        // _tprintf(TEXT("\n     Executable     = %s"), me32.szExePath);
        // _tprintf(TEXT("\n     Process ID     = 0x%08X"), me32.th32ProcessID);
        // _tprintf(TEXT("\n     Ref count (g)  = 0x%04X"), me32.GlblcntUsage);
        // _tprintf(TEXT("\n     Ref count (p)  = 0x%04X"), me32.ProccntUsage);
        // _tprintf(TEXT("\n     Base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
        // _tprintf(TEXT("\n     Base size      = %d"), me32.modBaseSize);

        if (me32.th32ProcessID == dwProcessId && _tcscmp(me32.szModule, moduleName.data()) == 0) {

            if (moduleEntry) {
                memcpy_s(moduleEntry, sizeof(MODULEENTRY32), &me32, sizeof(MODULEENTRY32));
            }
            
            bHasModule = true;
            break;
        }

    } while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
	return bHasModule;
}

DWORD WinApiHelper::GetProcessIdByTitle(const VKString& name)
{
    HWND hFind = FindWindow(nullptr, name.c_str());
    DWORD dwProcId;
    GetWindowThreadProcessId(hFind, &dwProcId);
    return dwProcId;
}
