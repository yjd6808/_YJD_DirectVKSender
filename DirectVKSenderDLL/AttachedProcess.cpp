/*
 * �ۼ��� : ������
 * �� DLL�� Attached�� ��������� ���μ���
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
			Debug::ShowMessageBox(_T("������ �ڵ� �ʱ�ȭ ����"));
		}
	}

	return *ms_pProcess;
}

// ������ ���μ����� ��ȸ�ϸ鼭 ��ġ�ϴ� �Ķ���ͷ� ���޹��� ID�� ��ġ�ϴ� ���μ����� ã��
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

	Debug::ShowMessageBox(_T("�޽��� ���ۿϷ�"));
	return PostMessage(m_hWnd, msgCode, wParam, lParam);
}