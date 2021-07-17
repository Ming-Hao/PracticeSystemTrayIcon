#ifndef WINDOWINFOHELPER_H
#define WINDOWINFOHELPER_H

#include "windowinfodef.h"
#include <Windows.h>

namespace WindowInfoHelper
{
    QString getProcessName(HWND hwnd);
    BOOL CALLBACK enumWindowProc(HWND hwnd, LPARAM lParam);
    WindowInfoList getWindowList();
}

#endif // WINDOWINFOHELPER_H
