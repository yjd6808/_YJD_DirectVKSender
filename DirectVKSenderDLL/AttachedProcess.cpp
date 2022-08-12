/*
 * 작성자 : 윤정도
 * 이 DLL이 Attached된 윈도기반의 프로세스
 */

#include "PrecompiledHeader.h"
#include "AttachtedProcess.h"
#include "Debug.h"
#include "Error.h"


AttachedProcess& AttachedProcess::Get()
{
	if (ms_pProcess == nullptr) {
		ms_pProcess = new AttachedProcess();

		if (ms_pProcess->Initialize() == false) {
			Debug::ShowMessageBox(_T("윈도우 핸들 초기화 실패"));
		}
	}

	return *ms_pProcess;
}

// 윈도우 프로세스들 순회하면서 일치하는 파라미터로 전달받은 ID와 일치하는 프로세스를 찾음
BOOL CALLBACK AttachedProcess::EnumWindowCallback(HWND hWnd, LPARAM lparam) {
    DWORD dwProcessId;
    GetWindowThreadProcessId(hWnd, &dwProcessId);

	if (dwProcessId == lparam) {
		ms_pProcess->m_hWnd = hWnd;
		return FALSE;
	}
    
    return TRUE;
}


BOOL AttachedProcess::Initialize() {
	if (EnumWindows(EnumWindowCallback, GetCurrentProcessId()) == FALSE)
		return TRUE;

	m_fnWndProc = (WNDPROC)GetWindowLong(m_hWnd, GWLP_WNDPROC);

	return FALSE;
}

BOOL AttachedProcess::ExecutePostWndProc(int msgCode, WPARAM wParam, LPARAM lParam) {
	if (m_hWnd == NULL)
		return FALSE;

	Debug::ShowMessageBox(_T("메시지 전송완료"));
	return PostMessage(m_hWnd, msgCode, wParam, lParam);
}