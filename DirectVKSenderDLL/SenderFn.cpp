/**
 * �ۼ��� : ������
 * ���� : Direct VK Sender(C# WPF ���α׷�)���� C ����� ����ϴ� ��쿡 ȣ���ϴ� �Լ�
 */

#include "PrecompiledHeader.h"
#include "SenderFn.h"
#include "WinApiHelper.h"
#include "TypedefString.h"
#include "Debug.h"

using namespace std;

VK_SENDER_EXPORT bool VK_CDECL HelloWorld(const TCHAR* msg)
{
	Debug::ShowMessageBox(msg);
	return true;
}


VK_SENDER_EXPORT bool VK_CDECL InjectDLL(DWORD dwWndProcessId)
{
	Debug::ShowMessageBox(_T("_1"));
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwWndProcessId);

	if (hProcess == NULL) {
		Debug::ShowMessageBox(_T("InjectDLL -> OpenProcess Failed"));
		return false;
	}

	Debug::ShowMessageBox(_T("_2"));
	// DirectVKSender
	// DirectVKSenderDLLDebugger
	// �� 2���� ���ϰ� ���� ��ο� ��� DirectVKSenderDLL.dll������ ������.
	// ���� �׳� ���� ��� ���(DirectVKSender.exe�� ���)�� �����ͼ� ���丮�� �����´��� DLL ���ϸ� �ڿ� �߰��ؼ� ����ȴ�.
	VKString strModuleFileName = _T("DirectVKSenderDLL.dll");
	VKString strModuleFullPath = std::filesystem::path(WinApiHelper::GetCurrentModuleFileName())
		.parent_path().append(strModuleFileName);

	Debug::ShowMessageBox(_T("_3"));

	LPVOID pRemoteBuf = VirtualAllocEx(hProcess, NULL, strModuleFullPath.size() * sizeof(TCHAR) + 1, MEM_COMMIT, PAGE_READWRITE);

	if (pRemoteBuf == NULL) {
		Debug::ShowMessageBox(_T("InjectDLL -> VirtualAllocEx Failed"));
		return false;
	}

	SIZE_T ulWrittenBytesSize = 0;
	if (WriteProcessMemory(hProcess, pRemoteBuf, strModuleFullPath.data(), strModuleFullPath.size() * sizeof(TCHAR) + 1, &ulWrittenBytesSize) == 0) {
		Debug::ShowMessageBox(_T("InjectDLL -> WriteProcessMemory Failed"));
		return false;
	}

	HMODULE hKernelDLLModule = GetModuleHandle(_T("kernel32.dll"));

	if (hKernelDLLModule == NULL) {
		Debug::ShowMessageBox(_T("InjectDLL -> GetModuleHandle Failed"));
		return false;
	}

	#ifdef UNICODE
		LPVOID pProc = (LPVOID)GetProcAddress(hKernelDLLModule, "LoadLibraryW");
	#else
		LPVOID pProc = (LPVOID)GetProcAddress(hKernelDLLModule, "LoadLibraryA");
	#endif
	if (pProc == NULL)
	{
		Debug::ShowMessageBox(_T("InjectDLL -> GetProcAddress(\"LoadLibrary\") Failed"));
		return false;
	}

	HANDLE hProcessThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pProc, pRemoteBuf, 0, NULL);

	if (hProcessThread == NULL) {
		Debug::ShowMessageBox(_T("InjectDLL -> CreateRemoteThread Failed"));
		return false;
	}

	WaitForSingleObject(hProcessThread, INFINITE);

	if (!WinApiHelper::GetLoadedModule(dwWndProcessId, strModuleFileName, NULL)) {
		Debug::ShowMessageBox(_T("DLL Injection Failed"));
		return false;
	}
	
	return true;
}

VK_SENDER_EXPORT bool VK_CDECL EjectDLL(DWORD dwWndProcessId)
{

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwWndProcessId);

	if (hProcess == NULL) {
		Debug::ShowMessageBox(_T("EjectDLL -> OpenProcess Failed"));
		return false;
	}

	// DirectVKSender
	// DirectVKSenderDLLDebugger
	// �� 2���� ���ϰ� ���� ��ο� ��� DirectVKSenderDLL.dll������ ������.
	// ���� �׳� ���� ��� ���(DirectVKSender.exe�� ���)�� �����ͼ� ���丮�� �����´��� DLL ���ϸ� �ڿ� �߰��ؼ� ����ȴ�.
	VKString strModuleFileName = _T("DirectVKSenderDLL.dll");
	VKString strModuleFullPath = std::filesystem::path(WinApiHelper::GetCurrentModuleFileName())
		.parent_path().append(strModuleFileName);

	// ���� ��쿡�� �׳� ��ȯ
	MODULEENTRY32 moduleEntry;
	if (!WinApiHelper::GetLoadedModule(dwWndProcessId, strModuleFileName, &moduleEntry)) {
		Debug::ShowMessageBox(_T("EjectDLL -> GetLoadedModule : DirectVKSenderDLL.dll doesn't Exist"));
		return true;
	}

	HMODULE hKernelDLLModule = GetModuleHandle(_T("kernel32.dll"));

	if (hKernelDLLModule == NULL) {
		Debug::ShowMessageBox(_T("EjectDLL -> GetModuleHandle Failed"));
		return false;
	}

	LPVOID pProc = (LPVOID)GetProcAddress(hKernelDLLModule, "FreeLibrary");

	if (pProc == NULL)
	{
		Debug::ShowMessageBox(_T("EjectDLL -> GetProcAddress(\"FreeLibrary\") Failed"));
		return false;
	}

	HANDLE hProcessThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pProc, moduleEntry.modBaseAddr, 0, NULL);

	if (hProcessThread == NULL) {
		Debug::ShowMessageBox(_T("EjectDLL -> CreateRemoteThread Failed"));
		return false;
	}

	WaitForSingleObject(hProcessThread, INFINITE);

	if (WinApiHelper::GetLoadedModule(dwWndProcessId, strModuleFileName)) {
		Debug::ShowMessageBox(_T("EjectDLL -> DLL Ejection Failed"));
		return false;
	}

	return true;
}

