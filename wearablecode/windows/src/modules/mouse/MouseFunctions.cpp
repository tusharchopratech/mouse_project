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
            if (isNextLeftClickDownIsFromImpulse)
            {
                lastImpulseLeftClickTimeStamp = gb_getCurrentTimeInMillisecondsDouble();
                leftMouseStatus = 0;
            }
            else
            {
                double tmpCurrentTime = gb_getCurrentTimeInMillisecondsDouble();
                lastLeftClickAction = "os_left_down";
                impulseLogs.push_back("OS Left Down Click at " + std::to_string(tmpCurrentTime));

                if (getImpulseLeftClickStatus() == 1)
                {
                    int lead = tmpCurrentTime - lastImpulseLeftClickTimeStamp;
                    impulseLogs.push_back("Lead : " + std::to_string(lead));
                    impulseLogs.push_back("--");
                }
            }
            isNextLeftClickDownIsFromImpulse = false;
        }
    }
    else
    {
        lastLeftUpClickTimeStamp = gb_getCurrentTimeInMillisecondsDouble();
        setImpulseLeftClickStatus(0);
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
        if (isRealTimeRunning)
        {
            if (isNextRightClickDownIsFromImpulse)
            {
                lastImpulseRightClickTimeStamp = gb_getCurrentTimeInMillisecondsDouble();
                rightMouseStatus = 0;
            }
            else
            {
                double tmpCurrentTime = gb_getCurrentTimeInMillisecondsDouble();
                lastRightClickAction = "os_right_down";
                impulseLogs.push_back("OS Right Down Click at " + std::to_string(tmpCurrentTime));

                if (getImpulseRightClickStatus() == 1)
                {
                    int lead = tmpCurrentTime - lastImpulseRightClickTimeStamp;
                    impulseLogs.push_back("Lead : " + std::to_string(lead));
                    impulseLogs.push_back("--");
                }
            }
            isNextRightClickDownIsFromImpulse = false;
        }
    }
    else
    {
        lastRightUpClickTimeStamp = gb_getCurrentTimeInMillisecondsDouble();
        setImpulseRightClickStatus(0);
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

void MouseFunctions::setImpulseLeftClickStatus(int status)
{
    impulseLeftClickStatus = status;
}

int MouseFunctions::getImpulseLeftClickStatus()
{
    return impulseLeftClickStatus;
}

void MouseFunctions::setImpulseRightClickStatus(int status)
{
    impulseRightClickStatus = status;
}
int MouseFunctions::getImpulseRightClickStatus()
{
    return impulseRightClickStatus;
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