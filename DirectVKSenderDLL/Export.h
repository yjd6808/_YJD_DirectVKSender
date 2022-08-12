/**
 * 작성자 : 윤정도
 */

#pragma once


#ifdef DirectVKSenderDLL_Export
	#define VK_SENDER_EXPORT __declspec(dllexport)
#else
	#define VK_SENDER_EXPORT __declspec(dllimport)
#endif