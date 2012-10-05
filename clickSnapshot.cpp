#include "stdafx.h"
#include <iostream>
#define _WIN32_WINNT    0x0501        //xp
#include <windows.h>
using namespace std;

int main()
{ 
    RECT rc;
    HWND hwnd = FindWindow(TEXT("Notepad"), NULL);    //the window can't be min
    if (hwnd == NULL)
    {
        cout << "it can't find any 'note' window" << endl;
        return 0;
    }
    GetClientRect(hwnd, &rc);

    //create
    HDC hScreenDC  = GetDC(NULL);
    HDC hMemDC  = CreateCompatibleDC(hScreenDC );
    HBITMAP hbmp = CreateCompatibleBitmap(hScreenDC , 
        rc.right - rc.left, rc.bottom - rc.top);
    SelectObject(hMemDC , hbmp);

    //Print to memory hMemDC 
    PrintWindow(hwnd, hMemDC , PW_CLIENTONLY);

    //copy to clipboard
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hbmp);
    CloseClipboard();

    //release
    DeleteDC(hMemDC );
    DeleteObject(hbmp);
    ReleaseDC(NULL, hScreenDC );

    cout << "success copy to clipboard, please paste it to the 'mspaint'" << endl;

    return 0;
}


