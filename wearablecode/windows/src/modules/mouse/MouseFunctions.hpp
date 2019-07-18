#ifndef MouseFunction_HPP
#define MouseFunction_HPP

#define _WIN32_WINNT 0x0400
#pragma comment(lib, "user32.lib")

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <vector>
#include "..\edata\Global.cpp"

using namespace std;

class MouseFunctions
{
private:
public:
    HHOOK hMouseHook;
    HANDLE hThread;
    DWORD dwThread;

    int leftMouseStatus = 0;
    int rightMouseStatus = 0;
    int thumbMouseStatus = 0;
    vector<int> leftMouseClickVector, rightMouseClickVector, thumbMouseClickVector;

    //single ton
    static MouseFunctions &Instance()
    {
        static MouseFunctions mf;
        return mf;
    }

    void setLeftMouseStatus(int status);

    int getLeftMouseStatus();

    void setRightMouseStatus(int status);

    int getRightMouseStatus();

    void setThumbMouseStatus(int status);

    int getThumbMouseStatus();

    int getLeftMouseStatusAtIndex(int index);

    int getRightMouseStatusAtIndex(int index);

    int getThumbMouseStatusAtIndex(int index);

    LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);

    DWORD WINAPI MyMouseLogger(LPVOID lpParm);

    void startMouseRecording();

    void setupMouseMonitoring();

    void mouseEvent(char mouseButton, char mouseEvent);
};

#endif // !MouseFunction_HPP