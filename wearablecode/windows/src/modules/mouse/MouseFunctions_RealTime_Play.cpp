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
                lastLeftClickAction = "ip_left_down";
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

            if (isRealTimeRunning == true && getRightMouseStatus() == 0 && isRightClickFiringAvaiable == true && (gb_getCurrentTimeInMillisecondsDouble() - lastRightUpClickTimeStamp) > refractoryPeriodMs)
            {

                impulseLogs.push_back("--");
                impulseLogs.push_back("IP Right Down Click at " + gb_getCurrentTimeInMilliseconds());
                lastRightClickAction = "ip_right_down";
                setImpulseRightClickStatus(1);

                isNextRightClickDownIsFromImpulse = true;
                mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);

                isRightClickFiringAvaiable = false;
                std::thread newThread3(&MouseFunctions::unblockRightClickFiring, this);
                newThread3.detach();
                std::thread newThread4(&MouseFunctions::checkAndFireRightUpClick, this);
                newThread4.detach();
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

    int ss = getLeftMouseStatus();
    if (lastLeftClickAction == "ip_left_down" && getImpulseLeftClickStatus() == 1)
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

    int ss = getRightMouseStatus();
    if (lastRightClickAction == "ip_right_down" && getImpulseRightClickStatus() == 1)
    {
        fireMouseEvent('r', 'u');
        setImpulseRightClickStatus(0);
        isNextRightClickDownIsFromImpulse = false;
        impulseLogs.push_back("IP Right UP Click at " + gb_getCurrentTimeInMilliseconds());
        impulseLogs.push_back("--");
    }
}

std::vector<string> MouseFunctions::getImpulseLogs()
{
    std::vector<string> tmp = impulseLogs;
    impulseLogs.clear();
    return tmp;
}

#endif