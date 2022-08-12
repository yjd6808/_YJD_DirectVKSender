/**
 * 작성자 : 윤정도
 * 설명 : Direct VK Sender(C# WPF 프로그램)에서 C 기능을 사용하는 경우에 호출하는 함수
 */

#pragma once

#include "CallingConvention.h"
#include "Export.h"
#include "TypedefString.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>



// C# 에서는 C++ 네임맹글링된 함수를 호출할 수 없기 떄문에 C로 맹글링 해줘야한다.
extern "C" {
    // 테스트 함수
    VK_SENDER_EXPORT bool VK_CDECL HelloWorld(const TCHAR* msg);


    // 다른 프로세스에게 현재 이 DLL을 인젝션한다.
    VK_SENDER_EXPORT bool VK_CDECL InjectDLL(DWORD dwWndProcessId);

    // 다른 프로세스에게 현재 이 DLL을 이젝션한다.
    VK_SENDER_EXPORT bool VK_CDECL EjectDLL(DWORD dwWndProcessId);
}