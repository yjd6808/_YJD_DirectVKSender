using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Process = System.Diagnostics.Process;

namespace DirectVKSender
{
    public static class ProcessExtension
    {
        // 현재 프로세스가 실행중인지
        public static bool IsRunning(this Process process)
        {
            foreach (var proc in Process.GetProcesses())
            {
                if (proc.Id == process.Id && proc.ProcessName == process.ProcessName)
                    return true;
            }

            return false;
        }

        public static bool ContainModule(this Process process, string moduleName)
        {
            foreach (ProcessModule module in process.Modules)
            {
                if (module.ModuleName == moduleName)
                    return true;
            }

            return false;
        }


    }
}
