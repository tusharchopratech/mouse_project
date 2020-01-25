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
    int leftMouseStatus = 0;
    int rightMouseStatus = 0;
    int thumbMouseStatus = 0;

    bool isRealTimeRunning;
    double refractoryPeriodMs = GB_DEFAULT_REFRACTORY_PERIOD_IN_MS;
    double fireUpClickAfterMs = GB_DEFAULT_MAX_LEAD_IN_MS;
    std::vector<string> impulseLogs;

    string lastLeftClickAction = "os_left_down";
    int impulseLeftClickStatus = 0;
    double lastLeftUpClickTimeStamp = 0.0;
    double lastImpulseLeftClickTimeStamp = 0.0;
    bool isNextLeftClickDownIsFromImpulse = false;
    bool isLeftClickFiringAvaiable = true;

    string lastRightClickAction = "os_right_down";
    int impulseRightClickStatus = 0;
    double lastRightUpClickTimeStamp = 0.0;
    double lastImpulseRightClickTimeStamp = 0.0;
    bool isNextRightClickDownIsFromImpulse = false;
    bool isRightClickFiringAvaiable = true;

    // string lastActionPerformed = "os_left_down";
    // double lastIpActionTimeStamp = 0.0;

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

    void setImpulseLeftClickStatus(int status);
    int getImpulseLeftClickStatus();

    void setImpulseRightClickStatus(int status);
    int getImpulseRightClickStatus();

    void setRefractoryAndMaxLead(double refractoryPeriodInMs, double maxLeadInMS);

    LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam);

    DWORD WINAPI MyMouseLogger(LPVOID lpParm);

    void startMouseRecording();
    void setupMouseMonitoring();

    void startRealTimePlay();
    void stopRealTimePlay();

    void fireMouseEvent(char mouseButton, char mouseEvent);

    std::vector<string> getImpulseLogs();
    std::vector<string> getImpulseLeads();

    void unblockLeftClickFiring();
    void unblockRightClickFiring();

    void checkAndFireLeftUpClick();
    void checkAndFireRightUpClick();
};

#endif // !MouseFunction_HPP