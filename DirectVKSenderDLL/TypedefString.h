/**
 * �ۼ��� : ������
 * ���� : Multi Byte <-> Unicode ȣȯ ���ڿ�
 */

#pragma once

#include <string>
#include <sstream>
#include <filesystem>
#include <tchar.h>

#ifdef UNICODE
	#define EMPTY_STRING			L""

	typedef std::wstring			VKString;
	typedef std::wstringstream		VKStringStream;
#else
	#define EMPTY_STRING			""

	typedef std::string				VKString;
	typedef std::stringstream		VKStringStream;
#endif

