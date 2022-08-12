/*
 * �ۼ��� : ������
 * �� DLL�� Attached�� ��������� ���μ���
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


