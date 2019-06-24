#define _WIN32_WINNT 0x0400
#pragma comment(lib, "user32.lib")

#include <windows.h>
#include <stdio.h>
#include <thread>
#include <vector>


using namespace std;

HHOOK hMouseHook;
HANDLE hThread;
DWORD dwThread;

int leftMouseStatus = 0;
int rightMouseStatus = 0;
int totalNumberOfSamples;
vector<int> leftMouseClickVector, rightMouseClickVector;



void setLeftMouseStatus(int status)
{
    leftMouseStatus = status;
}

int getLeftMouseStatus()
{
    return leftMouseStatus;
}

void setRightMouseStatus(int status)
{
    rightMouseStatus = status;
}

int getRightMouseStatus()
{
    return rightMouseStatus;
}

int getLeftMouseStatusAtIndex(int index){
    return leftMouseClickVector[index];
}

int getRightMouseStatusAtIndex(int index){
    return rightMouseClickVector[index];
}



LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    MOUSEHOOKSTRUCT *pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
    if (pMouseStruct != NULL)
    {
        if (wParam == WM_LBUTTONDOWN)
        {
            setLeftMouseStatus(1);
        }
        else if (wParam == WM_LBUTTONUP)
        {
            setLeftMouseStatus(0);
        }
        else if (wParam == WM_RBUTTONDOWN)
        {
            setRightMouseStatus(1);
        }
        else if (wParam == WM_RBUTTONUP)
        {
            setRightMouseStatus(0);
        }
    }
    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

DWORD WINAPI MyMouseLogger(LPVOID lpParm)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    // here I put WH_MOUSE instead of WH_MOUSE_LL
    hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, hInstance, NULL);

    MSG message;
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    UnhookWindowsHookEx(hMouseHook);
    return 0;
}

void startMouseRecording()
{

    while (1)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        leftMouseClickVector.insert(leftMouseClickVector.end(), getLeftMouseStatus());
        rightMouseClickVector.insert(rightMouseClickVector.end(), getRightMouseStatus());
        if (leftMouseClickVector.size() > totalNumberOfSamples)
        {
             leftMouseClickVector.erase(leftMouseClickVector.begin());
        }
        if (rightMouseClickVector.size() > totalNumberOfSamples)
        {
            rightMouseClickVector.erase(rightMouseClickVector.begin());
        }
    }
}

void setupMouseMonitoring(int totalSamples)
{
    totalNumberOfSamples = totalSamples;
    hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MyMouseLogger, NULL, NULL, &dwThread);
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)startMouseRecording, NULL, NULL, NULL);
}



void mouseEvent(char mouseButton, char mouseEvent)
{
    if (mouseButton == 'l')
    {
        if (mouseEvent == 'd')
        {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        }
        else if (mouseEvent == 'u')
        {
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
    }
    else if (mouseButton == 'r')
    {
        if (mouseEvent == 'd')
        {
            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        }
        else if (mouseEvent == 'u')
        {
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
    }
}
