#ifndef MouseFunction_RealTime_Play_CPP
#define MouseFunction_RealTime_Play_CPP

#include "MouseFunctions.hpp"

void MouseFunctions::fireMouseEvent(char mouseButton, char mouseEvent)
{
    if (mouseButton == 'l')
    {
        if (mouseEvent == 'd')
        {
            if (isRealTimeRunning == true && getLeftMouseStatus() == 0 && isLeftClickFiringAvaiable == true && (gb_getCurrentTimeInMillisecondsDouble() - lastLeftUpClickTimeStamp) > refractoryPeriodMs)
            {

                impulseLogs.push_back("--");
                impulseLogs.push_back("IP Left Down Click at " + gb_getCurrentTimeInMilliseconds());
                lastClickAction = "ip_left_down";
                setImpulseLeftClickStatus(1);

                isNextLeftClickDownIsFromImpulse = true;
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

                isLeftClickFiringAvaiable = false;
                std::thread newThread(&MouseFunctions::unblockLeftClickFiring, this);
                newThread.detach();
                std::thread newThread2(&MouseFunctions::checkAndFireLeftUpClick, this);
                newThread2.detach();
            }
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
            if (isRealTimeRunning)
            {
                mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
            }
        }
        else if (mouseEvent == 'u')
        {
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
    }
}

void MouseFunctions::startRealTimePlay()
{
    lastLeftUpClickTimeStamp = 0.0;
    impulseLogs.clear();
    isRealTimeRunning = true;
}

void MouseFunctions::stopRealTimePlay()
{
    isRealTimeRunning = false;
}

void MouseFunctions::unblockLeftClickFiring()
{
    double currentTime = gb_getCurrentTimeInMillisecondsDouble();
    while (gb_getCurrentTimeInMillisecondsDouble() - currentTime < restPeriodMs)
    {
    }
    isLeftClickFiringAvaiable = true;
}

void MouseFunctions::checkAndFireLeftUpClick()
{
    double currentTime = gb_getCurrentTimeInMillisecondsDouble();
    while (gb_getCurrentTimeInMillisecondsDouble() - currentTime < fireUpClickAfterMs)
    {
    }

    int ss = getCurrentLeftMouseStatus();
    if (lastClickAction == "ip_left_down" && getImpulseLeftClickStatus() == 1)
    {
        fireMouseEvent('l', 'u');
        setImpulseLeftClickStatus(0);
        isNextLeftClickDownIsFromImpulse = false;
        impulseLogs.push_back("IP Left UP Click at " + gb_getCurrentTimeInMilliseconds());
        impulseLogs.push_back("--");
    }
}

void MouseFunctions::unblockRightClickFiring()
{
    double currentTime = gb_getCurrentTimeInMillisecondsDouble();
    while (gb_getCurrentTimeInMillisecondsDouble() - currentTime < restPeriodMs)
    {
    }
    isRightClickFiringAvaiable = true;
}

void MouseFunctions::checkAndFireRightUpClick()
{
    double currentTime = gb_getCurrentTimeInMillisecondsDouble();
    while (gb_getCurrentTimeInMillisecondsDouble() - currentTime < fireUpClickAfterMs)
    {
    }
    if (getRightMouseStatus() == 0)
    {
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        cout << "IP Right UP Click at " << gb_getCurrentTimeInMilliseconds() << endl;
    }
}

std::vector<string> MouseFunctions::getImpulseLogs()
{
    std::vector<string> tmp = impulseLogs;
    impulseLogs.clear();
    return tmp;
}

#endif