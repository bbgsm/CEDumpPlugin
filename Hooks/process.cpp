#include <vector>
#include <string>
#include "hooks.h"


std::vector<PProcess> processes;

namespace Hooks {
    DWORD current_process = 0;

    HANDLE hk_create_tool_help_32_snapshot(DWORD dwFlags, DWORD th32ProcessID) {
        return (HANDLE)0x66;
    }

    BOOL hk_process_32_first(HANDLE hSnapshot, LPPROCESSENTRY32 lppe) {
        logDebug("hk_process_32_first\n");
        processes = memTools.getProcessList();
        if (processes.empty()) {
            return false;
        }
        lppe->dwSize = sizeof(PROCESSENTRY32);
        lppe->th32ParentProcessID = processes[current_process].pProcessID;
        lppe->th32ProcessID = processes[current_process].processID;
        strcpy(lppe->szExeFile, processes[current_process].processName);
        logDebug("processName: %s\n", processes[current_process].processName);
        current_process++;
        return true;
    }

    BOOL hk_process_32_next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe) {
        if (current_process >= processes.size()) {
            current_process = 0;
            return false;
        }
        lppe->dwSize = sizeof(PROCESSENTRY32);
        lppe->dwSize = sizeof(PROCESSENTRY32);
        lppe->th32ParentProcessID = processes[current_process].pProcessID;
        lppe->th32ProcessID = processes[current_process].processID;
        strcpy(lppe->szExeFile, processes[current_process].processName);
        current_process++;
        return true;
    }
}
