#ifndef MouseFunction_RealTime_Play_CPP
#define MouseFunction_RealTime_Play_CPP

#include "MouseFunctions.hpp"

void MouseFunctions::fireMouseEvent(char mouseButton, char mouseEvent)
{
    if (mouseButton == 'l')
    {
        if (mouseEvent == 'd')
        {
            if (isRealTimeRunning == true && getLeftMouseStatus() == 0 && isLeftClickFiringAvaiable == true && (gb_getCurrentTimeInMillisecondsDouble() - lastLeftClickTimeStamp) > refractoryPeriodMs)
            {
                cout << endl;
                 cout << "IP Left Down Click at " << gb_getCurrentTimeInMilliseconds() << endl;
                impulseLogs.push_back("--");
                impulseLogs.push_back("IP Left Down Click at " + gb_getCurrentTimeInMilliseconds());

                leftDownClickFlag = 0;
                lastActionPerformed = "ip_left_down";
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                
                isLeftClickFiringAvaiable = false;
                leftDownClickFlag = 1;
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
                if (getRightMouseStatus() == 0 && isRightClickFiringAvaiable == true && (gb_getCurrentTimeInMillisecondsDouble() - lastRightClickTimeStamp) > refractoryPeriodMs)
                {

                    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT || gb_getCurrentEnvirnoment() == GB_ENV_STAGING)
                    {
                        cout << "IP Right Down Click at " << gb_getCurrentTimeInMilliseconds() << endl;
                    }
                    else
                    {
                        // mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                    }
                    isRightClickFiringAvaiable = false;
                    std::thread newThread(&MouseFunctions::unblockRightClickFiring, this);
                    newThread.detach();
                    // std::thread newThread2(&MouseFunctions::checkAndFireRightUpClick, this);
                    // newThread2.detach();
                }
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
    impulseLogs.clear();
    lastLeftClickTimeStamp = 0.0;
    lastRightClickTimeStamp = 0.0;
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
    if (leftDownClickFlag == 1)
    {
        fireMouseEvent('l', 'u');
        leftDownClickFlag = 5;

        if (lastActionPerformed == "ip_left_down")
        {
            impulseLogs.push_back("Impulse click!");
        }

        lastActionPerformed = "ip_left_up";
        // lastIpActionTimeStamp = gb_getCurrentTimeInMillisecondsDouble();

        impulseLogs.push_back("IP Left UP Click at " + gb_getCurrentTimeInMilliseconds());
        impulseLogs.push_back("--");
        cout << "IP Left UP Click at " << gb_getCurrentTimeInMilliseconds() << endl;
        cout << endl;
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