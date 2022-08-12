/**
 * �ۼ��� : ������
 * ���� : Direct VK Sender(C# WPF ���α׷�)���� C ����� ����ϴ� ��쿡 ȣ���ϴ� �Լ�
 */

#pragma once

#include "CallingConvention.h"
#include "Export.h"
#include "TypedefString.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>



// C# ������ C++ ���Ӹͱ۸��� �Լ��� ȣ���� �� ���� ������ C�� �ͱ۸� ������Ѵ�.
extern "C" {
    // �׽�Ʈ �Լ�
    VK_SENDER_EXPORT bool VK_CDECL HelloWorld(const TCHAR* msg);


    // �ٸ� ���μ������� ���� �� DLL�� �������Ѵ�.
    VK_SENDER_EXPORT bool VK_CDECL InjectDLL(DWORD dwWndProcessId);

    // �ٸ� ���μ������� ���� �� DLL�� �������Ѵ�.
    VK_SENDER_EXPORT bool VK_CDECL EjectDLL(DWORD dwWndProcessId);
}