/**
 * 작성자 : 윤정도
 */

#pragma once

#include <WinSock2.h>

class IPCSocket
{
public:
	bool Create();
	bool Bind();
	bool StartListen();
	bool StopListen();
private:
	SOCKET m_Sock;
	SOCKADDR_IN m_Addr;
};