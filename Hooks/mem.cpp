#include <list>
#include <map>

#include "hooks.h"

namespace Hooks {

    HANDLE hk_open_process(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId) {
        if(memTools.init(memTools.getProcessList()[dwProcessId - 1].processPath)){
            return (HANDLE)0x69;
        }
        return 0;
    }

    BOOL hk_read(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead) {
        bool b = memTools.readV(lpBuffer, nSize, reinterpret_cast<Addr>(lpBaseAddress)) == nSize;
        *lpNumberOfBytesRead = b ? nSize : 0;
        logDebug("hk_read: %llX size: %d b: %d\n", lpBaseAddress, nSize, b);
        return b;
    }

    bool hk_write(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead) {
        bool b = memTools.writeV(lpBuffer, nSize, reinterpret_cast<Addr>(lpBaseAddress)) == nSize;
        *lpNumberOfBytesRead = b ? nSize : 0;
        logDebug("hk_write: %llX size: %d b: %d\n", lpBaseAddress, nSize, b);
        return b;
    }

    bool VirtualQueryImpl_(Addr addr, MemoryFile *ret) {
        std::vector<MemoryFile> &memoryFiles = memTools.getAllMemory();
        auto it = std::lower_bound(memoryFiles.begin(), memoryFiles.end(), addr,
                                   [](const MemoryFile &memory, Addr addr) {
                                       return memory.endAddress <= addr;
                                   });
        if (it == memoryFiles.end()) return {};
        *ret = *it;
        return true;
    }

    SIZE_T hk_virtual_query(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
        logDebug("hk_virtual_query: %p\n", lpAddress);
        MEMORY_BASIC_INFORMATION meminfo = {};
        MemoryFile memoryFile;
        if (!VirtualQueryImpl_(reinterpret_cast<uintptr_t>(lpAddress), &memoryFile)) {
            logDebug("not found: %p\n", lpAddress);
            return 0;
        }
        ZeroMemory(&meminfo, sizeof(meminfo));
        meminfo.BaseAddress = reinterpret_cast<PVOID>(memoryFile.baseAddress);
        meminfo.AllocationBase = reinterpret_cast<PVOID>(memoryFile.baseAddress);
        meminfo.AllocationProtect = PAGE_EXECUTE_READWRITE;
        meminfo.RegionSize = memoryFile.size;
        meminfo.State = MEM_COMMIT;
        meminfo.Protect = meminfo.AllocationProtect;
        meminfo.Type = MEM_IMAGE;
        meminfo.PartitionId = 0;
        memcpy(lpBuffer, &meminfo, sizeof(meminfo));
        return sizeof(meminfo);
    }
}
