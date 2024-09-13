#include "hooks.h"


namespace Hooks {
    DWORD current_module = 0;

    BOOL hk_module_32_first(HANDLE hSnapshot, LPMODULEENTRY32 lpme) {
        current_module = 0;
        MModule &module = memTools.getModuleList()[current_module];
        logDebug("module: %s\n",module.moduleName);
        lpme->dwSize = sizeof(MODULEENTRY32);
        lpme->th32ProcessID = 0;
        lpme->hModule = (HMODULE) module.baseAddress;
        lpme->modBaseSize = module.baseSize;
        lpme->modBaseAddr = (BYTE *) module.baseAddress;
        strcpy(lpme->szModule, module.moduleName);
        strcpy(lpme->szExePath, module.moduleName);
        current_module++;

        return true;
    }

    BOOL hk_module_32_next(HANDLE hSnapshot, LPMODULEENTRY32 lpme) {
        if (current_module >= memTools.getModuleList().size()) {
            current_module = 0;
            return false;
        }
        MModule &module = memTools.getModuleList()[current_module];
        logDebug("module: %s\n",module.moduleName);
        lpme->dwSize = sizeof(MODULEENTRY32);
        lpme->th32ProcessID = 0;
        lpme->hModule = (HMODULE) module.baseAddress;
        lpme->modBaseSize = module.baseSize;
        lpme->modBaseAddr = (BYTE *) module.baseAddress;
        strcpy(lpme->szModule, module.moduleName);
        strcpy(lpme->szExePath, module.moduleName);
        current_module++;

        return true;
    }
}
