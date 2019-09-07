#ifndef MouseFunction_CPP
#define MouseFunction_CPP

#include "MouseFunctions.hpp"

using namespace std;

void MouseFunctions::setLeftMouseStatus(int status)
{
    leftMouseStatus = status;
    if (status == 1 && isRealTimeRunning)
    {
        osLeftClicksTimeStamps.push_back(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
    }
}

int MouseFunctions::getLeftMouseStatus()
{
    return leftMouseStatus;
}

void MouseFunctions::setRightMouseStatus(int status)
{
    rightMouseStatus = status;
    if (status == 1 && isRealTimeRunning)
    {
        osRightClicksTimeStamps.push_back(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
    }
}

int MouseFunctions::getRightMouseStatus()
{
    return rightMouseStatus;
}

void MouseFunctions::setThumbMouseStatus(int status)
{
    thumbMouseStatus = status;
    if (status == 1 && isRealTimeRunning)
    {
        osThumbClicksTimeStamps.push_back(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
    }
}

int MouseFunctions::getThumbMouseStatus()
{
    return thumbMouseStatus;
}

int MouseFunctions::getLeftMouseStatusAtIndex(int index)
{
    return leftMouseClickVector.at(index);
}

int MouseFunctions::getRightMouseStatusAtIndex(int index)
{
    return rightMouseClickVector.at(index);
}

int MouseFunctions::getThumbMouseStatusAtIndex(int index)
{
    return thumbMouseClickVector.at(index);
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

void startMouseRecording()
{
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        MouseFunctions::Instance().leftMouseClickVector.push_back(MouseFunctions::Instance().getLeftMouseStatus());
        MouseFunctions::Instance().rightMouseClickVector.push_back(MouseFunctions::Instance().getRightMouseStatus());
        MouseFunctions::Instance().thumbMouseClickVector.push_back(MouseFunctions::Instance().getThumbMouseStatus());
        if (MouseFunctions::Instance().leftMouseClickVector.size() > GB_TOTAL_NUMBER_OF_SAMPLES)
        {
            MouseFunctions::Instance().leftMouseClickVector.pop_front();
        }
        if (MouseFunctions::Instance().rightMouseClickVector.size() > GB_TOTAL_NUMBER_OF_SAMPLES)
        {
            MouseFunctions::Instance().rightMouseClickVector.pop_front();
        }
        if (MouseFunctions::Instance().thumbMouseClickVector.size() > GB_TOTAL_NUMBER_OF_SAMPLES)
        {
            MouseFunctions::Instance().thumbMouseClickVector.pop_front();
        }
    }
}

void MouseFunctions::setupMouseMonitoring()
{

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)::MyMouseLogger, NULL, NULL, &dwThread);
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)::startMouseRecording, NULL, NULL, &dwThread);
}

void MouseFunctions::mouseEvent(char mouseButton, char mouseEvent)
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

void MouseFunctions::startRealTimePlay()
{

    osMouseClicksTimeStamps.clear();
    osLeftClicksTimeStamps.clear();
    osRightClicksTimeStamps.clear();
    osThumbClicksTimeStamps.clear();
    isRealTimeRunning = true;
}

std::vector<std::vector<double>> MouseFunctions::stopRealTimePlayAndReturnTimestamps()
{
    isRealTimeRunning = false;
    osMouseClicksTimeStamps.push_back(osLeftClicksTimeStamps);
    osMouseClicksTimeStamps.push_back(osRightClicksTimeStamps);
    osMouseClicksTimeStamps.push_back(osThumbClicksTimeStamps);
    return osMouseClicksTimeStamps;
}

#endif // !MouseFunction_CPP