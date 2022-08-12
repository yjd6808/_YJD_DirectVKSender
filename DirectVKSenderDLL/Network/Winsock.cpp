/**
 * 작성자 : 윤정도
 */

#include <PrecompiledHeader.h>
#include "Winsock.h"

bool Winsock::Initialize()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return false;
	}

	return true;
}

bool Winsock::Finalize()
{
	if (WSACleanup() != 0) {
		return false;
	}

	return true;
}
