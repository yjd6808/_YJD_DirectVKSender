/**
 * 작성자 : 윤정도
 * 디버깅용 함수
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
	strStream <<	_T("묘듈 : ") << strModuleFileNameOnly << 
					_T("\n프로세스 ID : ") << GetCurrentProcessId() << 
					_T("\n메시지 : ") << msg << _T("\n");
	MessageBox(nullptr, strStream.str().c_str(), EMPTY_STRING, MB_APPLMODAL | MB_OK);
#endif
}

