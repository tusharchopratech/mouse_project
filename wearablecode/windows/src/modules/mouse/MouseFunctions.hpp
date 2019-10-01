#ifndef MouseFunction_HPP
#define MouseFunction_HPP
// #define _WIN32_WINNT 0x0400
#pragma comment(lib, "user32.lib")

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <queue>
using namespace std::chrono;
#include "..\edata\Global.cpp"

using namespace std;

class MouseFunctions
{
private:
    //First Left, then Right, then Thumb.
    std::vector<double> osLeftClicksTimeStamps, osRightClicksTimeStamps;
    std::vector<double> impulseLeftClicksTimeStamps, impulseRightClicksTimeStamps;

    double lastLeftClickTimeStamp = 0.0, lastRightClickTimeStamp = 0.0;

    int leftMouseStatus = 0;
    int rightMouseStatus = 0;
    int thumbMouseStatus = 0;

    bool isRealTimeRunning;

    double refractoryPeriodMs = 100.0;
    double restPeriodMs = 200.0;

    bool isLeftClickFiringAvaiable = true, isRightClickFiringAvaiable = true;

public:
    HHOOK hMouseHook;
    HANDLE hThread;
    DWORD dwThread;
    deque<int> leftMouseClickVector, rightMouseClickVector, thumbMouseClickVector;

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

    LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);

    DWORD WINAPI MyMouseLogger(LPVOID lpParm);

    void startMouseRecording();

    void setupMouseMonitoring();

    void startRealTimePlay();

    void stopRealTimePlay();

    void fireMouseEvent(char mouseButton, char mouseEvent);

    void unblockLeftClickFiring();
    void unblockRightClickFiring();
};

#endif // !MouseFunction_HPP