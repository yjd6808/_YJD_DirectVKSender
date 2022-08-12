/**
 * 작성자 : 윤정도
 * 설명 : WinAPI를 쉽게 다룰 수 있도록 도와주는 함수
 */

#pragma once

#include "TypedefString.h"
#include "Export.h"

#include <tlhelp32.h>

class VK_SENDER_EXPORT WinApiHelper
{
public:
	static VKString GetCurrentModuleFileName();
	static bool		GetLoadedModule(const DWORD dwProcessId, const VKString& moduleName, PMODULEENTRY32 moduleEntry = NULL);
	static DWORD	GetProcessIdByTitle(const VKString& name);
};


