/**
 * 작성자 : 윤정도
 * 디버깅용 함수
 */

#pragma once

#include "TypedefString.h"

class Debug
{
public:
	static void ShowMessageBox(const VKString& msg, const VKString& caption = EMPTY_STRING);

	template <typename... T>
	static void ShowMessageBoxFormat(const VKString& fmt, T... fmt_args)
	{
#ifdef _DEBUG
		TCHAR buf[1024];
		_stprintf_s(buf, 1024, fmt.c_str(), fmt_args...);
		ShowMessageBox(buf);
#endif
	}

	template <typename... T>
	static void PrintFormat(const VKString& fmt, T... fmt_args)
	{
#ifdef _DEBUG
		TCHAR buf[1024];
		_stprintf_s(buf, 1024, fmt.c_str(), fmt_args...);
		OutputDebugString(buf);
#endif
	}
};


