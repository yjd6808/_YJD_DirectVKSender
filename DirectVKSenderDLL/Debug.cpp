/**
 * �ۼ��� : ������
 * ������ �Լ�
 */

#include "PrecompiledHeader.h"
#include "Debug.h"
#include "TypedefString.h"
#include "WinApiHelper.h"

#include <filesystem>


void Debug::ShowMessageBox(const VKString& msg, const VKString& caption)
{
#ifdef _DEBUG
	const VKString strModuleFilePath = WinApiHelper::GetCurrentModuleFileName();
	const VKString strModuleFileNameOnly = std::filesystem::path(strModuleFilePath).filename();

	VKStringStream strStream;
	strStream <<	_T("���� : ") << strModuleFileNameOnly << 
					_T("\n���μ��� ID : ") << GetCurrentProcessId() << 
					_T("\n�޽��� : ") << msg << _T("\n");
	MessageBox(nullptr, strStream.str().c_str(), EMPTY_STRING, MB_APPLMODAL | MB_OK);
#endif
}

