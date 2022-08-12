/*
 * 작성자 : 윤정도
 * 이 DLL이 Attached된 윈도기반의 프로세스
 */

#pragma once

#include "PrecompiledHeader.h"

class AttachedProcess
{
public:
	static AttachedProcess& Get();
	static BOOL	CALLBACK	EnumWindowCallback(HWND hWnd, LPARAM lparam);
	

	BOOL Initialize();
	BOOL ExecutePostWndProc(int msgCode, WPARAM wParam, LPARAM lParam);
private:
	HWND m_hWnd = NULL;
	WNDPROC m_fnWndProc;

	inline static AttachedProcess* ms_pProcess;
};


