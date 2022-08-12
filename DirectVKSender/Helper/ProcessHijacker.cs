/**
 * 작성자 : 윤정도
 * 인젝션 이젝션 기능 제공
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DirectVKSender
{
    public static class ProcessHijacker
    {
        [DllImport(
            "DirectVKSenderDLL.dll",
            CharSet = CharSet.Auto,
            CallingConvention = CallingConvention.Cdecl)]
        public static extern bool HelloWorld(string msg);

        [DllImport(
            "DirectVKSenderDLL.dll",
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.Cdecl)]
        public static extern bool InjectDLL(int dwWndProcessId);

        [DllImport(
            "DirectVKSenderDLL.dll",
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.Cdecl)]
        public static extern bool EjectDLL(int dwWndProcessId);
    }
}
