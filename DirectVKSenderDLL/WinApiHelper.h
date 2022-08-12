/**
 * �ۼ��� : ������
 * ���� : WinAPI�� ���� �ٷ� �� �ֵ��� �����ִ� �Լ�
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


