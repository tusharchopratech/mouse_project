#ifndef MouseFunction_CPP
#define MouseFunction_CPP

#include "MouseFunctions.hpp"
#include "MouseFunctions_RealTime_Play.cpp"

using namespace std;

void MouseFunctions::setLeftMouseStatus(int status)
{
    leftMouseStatus = status;
    if (status == 1)
    {
        if (isRealTimeRunning)
        {
            double tmpCurrentTime = gb_getCurrentTimeInMillisecondsDouble();
            cout << "OS Left Down Click at " << tmpCurrentTime << endl;
            leftDownClickFlag++;
            if (leftDownClickFlag == 2)
            {
                int lead = tmpCurrentTime - lastLeftClickTimeStamp;
                impulseLogs.push_back("OS Left Down Click at " + std::to_string(tmpCurrentTime));
                impulseLogs.push_back("Lead : " + std::to_string(lead));
                impulseLogs.push_back("--");
                cout << "Lead " << lead << endl;
                cout << endl;
            }
            else
            {
                impulseLogs.push_back("OS Left Down Click at " + std::to_string(tmpCurrentTime));
            }

            lastActionPerformed = "os_left_down";
            lastLeftClickTimeStamp = tmpCurrentTime;
        }
    }
}

int MouseFunctions::getLeftMouseStatus()
{
    return leftMouseStatus;
}

void MouseFunctions::setRightMouseStatus(int status)
{
    rightMouseStatus = status;

    if (status == 1)
    {
        lastRightClickTimeStamp = gb_getCurrentTimeInMillisecondsDouble();
        if (isRealTimeRunning)
        {
            if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT || gb_getCurrentEnvirnoment() == GB_ENV_STAGING)
            {
                // cout << "OS Right Down Click at " << gb_getCurrentTimeInMilliseconds() << endl;
            }
        }
    }
}

int MouseFunctions::getRightMouseStatus()
{
    return rightMouseStatus;
}

void MouseFunctions::setThumbMouseStatus(int status)
{
    thumbMouseStatus = status;
}

int MouseFunctions::getThumbMouseStatus()
{
    return thumbMouseStatus;
}

LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    MOUSEHOOKSTRUCT *pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
    if (pMouseStruct != NULL)
    {

        if (wParam == WM_LBUTTONDOWN)
        {
            MouseFunctions::Instance().setLeftMouseStatus(1);
        }
        else if (wParam == WM_LBUTTONUP)
        {
            MouseFunctions::Instance().setLeftMouseStatus(0);
        }
        else if (wParam == WM_RBUTTONDOWN)
        {
            MouseFunctions::Instance().setRightMouseStatus(1);
        }
        else if (wParam == WM_RBUTTONUP)
        {
            MouseFunctions::Instance().setRightMouseStatus(0);
        }
        else if (wParam == WM_XBUTTONDOWN)
        {
            MouseFunctions::Instance().setThumbMouseStatus(1);
            // PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT)lParam;
            // if (GET_XBUTTON_WPARAM(p->mouseData) == XBUTTON1)
            // {
            //     cout<<"X Button 1 DOWN\n";
            // }
            // else if (GET_XBUTTON_WPARAM(p->mouseData) == XBUTTON2)
            // {
            //     cout<<"X Button 2 DOWN\n";
            // }
        }
        else if (wParam == WM_XBUTTONUP)
        {
            MouseFunctions::Instance().setThumbMouseStatus(0);
            //  PMSLLHOOKSTRUCT p = (PMSLLHOOKSTRUCT)lParam;
            // if (GET_XBUTTON_WPARAM(p->mouseData) == XBUTTON1)
            // {
            //     cout<<"X Button 1 UP\n";
            // }
            // else if (GET_XBUTTON_WPARAM(p->mouseData) == XBUTTON2)
            // {
            //     cout<<"X Button 2 UP\n";
            // }
        }
    }
    return CallNextHookEx(MouseFunctions::Instance().hMouseHook, nCode, wParam, lParam);
}

DWORD WINAPI MyMouseLogger(LPVOID lpParm)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    MouseFunctions::Instance().hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, ::mouseProc, hInstance, NULL);

    MSG message;
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    UnhookWindowsHookEx(MouseFunctions::Instance().hMouseHook);
    return 0;
}

void MouseFunctions::setupMouseMonitoring()
{
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)::MyMouseLogger, NULL, NULL, &dwThread);
}

#endif // !MouseFunction_CPP