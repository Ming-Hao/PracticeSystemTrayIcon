#include "windowinfohelper.h"
#include <Psapi.h>

QString WindowInfoHelper::getProcessName(HWND hwnd)
{
    QString processName;
    DWORD dwProcId = 0;
    ::GetWindowThreadProcessId(hwnd, &dwProcId);

    HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                  FALSE,
                                  dwProcId);

    if (NULL != hProcess)
    {
        HMODULE hMod;
        DWORD cbNeeded;
        TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

        if (::EnumProcessModules( hProcess, &hMod, sizeof(hMod),
                                  &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,
                               sizeof(szProcessName)/sizeof(TCHAR) );
            processName = QString::fromWCharArray(szProcessName);
        }

    }

    ::CloseHandle(hProcess);

    return processName;
}

BOOL WindowInfoHelper::enumWindowProc(HWND hwnd, LPARAM lParam)
{
    const DWORD TITLE_SIZE = 1024;
    WCHAR windowTitle[TITLE_SIZE];

    ::GetWindowTextW(hwnd, windowTitle, TITLE_SIZE);

    QString title = QString::fromWCharArray(windowTitle);

    if (!::IsWindowVisible(hwnd) || title.isEmpty() || title == "Program Manager") {
        return TRUE;
    }

    QString process = getProcessName(hwnd);
    WindowInfoList& titleList = *reinterpret_cast<WindowInfoList*>(lParam);
    titleList.push_back(std::make_pair(title, process));

    return TRUE;
}

WindowInfoList WindowInfoHelper::getWindowList()
{
    WindowInfoList titleList;
    ::EnumWindows(enumWindowProc, reinterpret_cast<LPARAM>(&titleList));
    return titleList;
}


